#ifndef _SUPER_SLAB_H_
#define _SUPER_SLAB_H_

#include <misc/cpp_attributes.h>
#include <optimized/bits.h>
#include <system/sys_info.h>

#include <allocator/rseq/rseq_base.h>

#include <allocator/common/internal_returns.h>
#include <allocator/common/safe_atomics.h>

#include <allocator/slab_layout/obj_slab.h>

#include <allocator/slab_layout/core_cache.h>


//////////////////////////////////////////////////////////////////////


template<typename T, typename inner_slab_t, uint32_t nvec = 1>
struct super_slab {
    static constexpr const uint64_t capacity =
        64 * nvec * inner_slab_t::capacity;

    uint64_t      available_slabs[nvec] L2_LOAD_ALIGN;
    core_cache<8> cc;

    // off core freed_slabs (expensive to touch and REALLY expensive to set)
    uint64_t freed_slabs[nvec] L2_LOAD_ALIGN;

    inner_slab_t inner_slabs[64 * nvec] L2_LOAD_ALIGN;

    super_slab() = default;

    void
    _first_free_on_core(T * addr, const uint32_t start_cpu) {
        uint32_t ret = cc.push((uint64_t)addr, start_cpu);
        if (ret == 0) {
            return;
        }
        const uint64_t pos_idx =
            (((uint64_t)addr) - ((uint64_t)(&inner_slabs[0]))) /
            sizeof(inner_slab_t);

        IMPOSSIBLE_COND(pos_idx >= nvec * 64);


        // final layer prefetch for child (child will prefetch for parent)
        if constexpr (std::is_same<inner_slab_t, slab<T>>::value) {
            PREFETCH_W(&(inner_slabs[pos_idx].freed_slots));
            if (!(inner_slabs + pos_idx)
                     ->_free((void * const)freed_slabs, addr)) {
                return;
            }
        }
        else {
            if (!(inner_slabs + pos_idx)
                     ->_free_on_core((void * const)freed_slabs,
                                     addr,
                                     start_cpu)) {
                return;
            }
        }


        atomic_or(freed_slabs + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
    }

    uint32_t
    _free_on_core(void * const   parent_addr,
                  T *            addr,
                  const uint32_t start_cpu) {
        uint32_t ret = cc.push((uint64_t)addr, start_cpu);
        if (ret == 0) {
            return 0;
        }
        const uint64_t pos_idx =
            (((uint64_t)addr) - ((uint64_t)(&inner_slabs[0]))) /
            sizeof(inner_slab_t);

        IMPOSSIBLE_COND(pos_idx >= nvec * 64);


        // final layer prefetch for child (child will prefetch for parent)
        if constexpr (std::is_same<inner_slab_t, slab<T>>::value) {
            PREFETCH_W(&(inner_slabs[pos_idx].freed_slots));
            // if we don't need to set just return (and tell parent as much)
            if (!(inner_slabs + pos_idx)
                     ->_free((void * const)freed_slabs, addr)) {
                return 0;
            }
        }
        else {
            if (!(inner_slabs + pos_idx)
                     ->_free_on_core((void * const)freed_slabs,
                                     addr,
                                     start_cpu)) {
                return 0;
            }
        }


        // otherwise check if we need to set and if so tell parent they will
        // need to as well. There is a race condition here in that multiple
        // children might tell there parent to set but that is only a
        // performance issue, not a correctness issue (and dealing with that
        // race condition costs more performance than it gains)
        // if (!(freed_slabs[(pos_idx / 64)] & ((1UL) << (pos_idx % 64)))) {
        if (freed_slabs[pos_idx / 64] == 0) {
            PREFETCH_W(parent_addr);
            atomic_or(freed_slabs + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
            return 1;
        }
        atomic_or(freed_slabs + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
        return 0;
    }

    void
    _first_free(T * const addr) {
        IMPOSSIBLE_COND(((uint64_t)addr) < ((uint64_t)(&inner_slabs[0])));

        const uint64_t pos_idx =
            (((uint64_t)addr) - ((uint64_t)(&inner_slabs[0]))) /
            sizeof(inner_slab_t);

        IMPOSSIBLE_COND(pos_idx >= nvec * 64);


        // final layer prefetch for child (child will prefetch for parent)
        if constexpr (std::is_same<inner_slab_t, slab<T>>::value) {
            PREFETCH_W(&(inner_slabs[pos_idx].freed_slots));
        }

        if (!(inner_slabs + pos_idx)->_free((void * const)freed_slabs, addr)) {
            return;
        }

        atomic_or(freed_slabs + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
    }

    uint32_t
    _free(void * const parent_addr, T * const addr) {
        IMPOSSIBLE_COND(((uint64_t)addr) < ((uint64_t)(&inner_slabs[0])));

        const uint64_t pos_idx =
            (((uint64_t)addr) - ((uint64_t)(&inner_slabs[0]))) /
            sizeof(inner_slab_t);

        IMPOSSIBLE_COND(pos_idx >= nvec * 64);

        // final layer prefetch for child (child will prefetch for parent)
        if constexpr (std::is_same<inner_slab_t, slab<T>>::value) {
            PREFETCH_W(&(inner_slabs[pos_idx].freed_slots));
        }

        // if we don't need to set just return (and tell parent as much)
        if (!(inner_slabs + pos_idx)->_free((void * const)freed_slabs, addr)) {
            return 0;
        }

        // otherwise check if we need to set and if so tell parent they will
        // need to as well. There is a race condition here in that multiple
        // children might tell there parent to set but that is only a
        // performance issue, not a correctness issue (and dealing with that
        // race condition costs more performance than it gains)
        // if (!(freed_slabs[(pos_idx / 64)] & ((1UL) << (pos_idx % 64)))) {
        if (freed_slabs[pos_idx / 64] == 0) {
            PREFETCH_W(parent_addr);
            atomic_or(freed_slabs + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
            return 1;
        }
        atomic_or(freed_slabs + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
        return 0;
    }

    uint64_t
    _allocate(const uint32_t start_cpu) {
        uint64_t optimistic_ret = cc.pop(start_cpu);
        if(optimistic_ret > core_cache<8>::migrated) {
            return optimistic_ret;
        }

        for (uint32_t i = 0; i < nvec; ++i) {
            while (1) {
                uint64_t _available_slabs = available_slabs[i];
                while (_available_slabs != FULL_ALLOC_VEC) {
                    const uint32_t idx =
                        bits::tzcnt<uint64_t>(~_available_slabs);

                    // fast path of successful allocation
                    const uint64_t ret =
                        (inner_slabs + 64 * i + idx)->_allocate(start_cpu);
                    // fast path complete
                    if (BRANCH_LIKELY(successful(ret))) {
                        return ret;
                    }
                    // branch full try to mark bit as full
                    else if (ret == FAILED_FULL) {
                        if (BRANCH_UNLIKELY(restarting_set_bit(
                                                available_slabs + i,
                                                idx,
                                                start_cpu) == _RSEQ_MIGRATED)) {
                            return FAILED_RSEQ;
                        }
                    }

#ifdef RETURN_WITH_SLAB_READY
                    else if (ret & SLAB_READY) {
                        if (BRANCH_UNLIKELY(restarting_unset_bit(
                                                available_slabs + i,
                                                idx,
                                                start_cpu) == _RSEQ_MIGRATED)) {
                            // this avoid a memory leak if we migrated (but
                            // is pretty unlikely)
                            atomic_or(freed_slabs + i, ((1UL) << idx));
                        }
                        return ret;
                    }
#else
                    else if (ret == SLAB_READY) {
                        if (BRANCH_UNLIKELY(restarting_unset_bit(
                                                available_slabs + i,
                                                idx,
                                                start_cpu) == _RSEQ_MIGRATED)) {
                            // this avoid a memory leak if we migrated (but
                            // is pretty unlikely)
                            atomic_or(freed_slabs + i, ((1UL) << idx));
                        }
                        return SLAB_READY;
                    }
#endif

                    // inner alloc ret == failed rseq
                    else {
                        return FAILED_RSEQ;
                    }
                    break;
                }

                // available_slabs[i] is full
                if (freed_slabs[i] != EMPTY_FREE_VEC) {
                    const uint64_t reclaimed_slabs =
                        restarting_reclaim_free_slabs(available_slabs + i,
                                                      freed_slabs + i,
                                                      start_cpu);
                    // this failing can mean either migration or preemption. we
                    // are continuing assuming likely case of preemption either
                    // way. Worst case scenario is read on available slabs.
                    // While it will be slow for migrated thread it should not
                    // interfere with other allocators
                    if (BRANCH_LIKELY(reclaimed_slabs)) {
                        atomic_unset(freed_slabs + i, reclaimed_slabs);
                        continue;
                    }
                }
                if (available_slabs[i] == FULL_ALLOC_VEC) {
                    break;
                }
            }
        }
        return FAILED_FULL;
    }
} L2_LOAD_ALIGN;


#endif
