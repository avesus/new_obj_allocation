#ifndef _SUPER_SLAB_H_
#define _SUPER_SLAB_H_

#include <misc/cpp_attributes.h>
#include <optimized/bits.h>
#include <system/sys_info.h>

#include <allocator/rseq/rseq_base.h>

#include <allocator/common/internal_returns.h>
#include <allocator/common/safe_atomics.h>

#include <allocator/slab_layout/obj_slab.h>


//////////////////////////////////////////////////////////////////////


template<typename T, uint32_t nvec = 1, typename inner_slab_t = slab<T>>
struct super_slab {
    static constexpr const uint64_t capacity =
        64 * nvec * inner_slab_t::capacity;

    uint64_t available_slabs[nvec] ALIGN_ATTR(CACHE_LINE_SIZE);

    // off core freed_slabs (expensive to touch and REALLY expensive to set)
    uint64_t freed_slabs[nvec] ALIGN_ATTR(CACHE_LINE_SIZE);

    inner_slab_t inner_slabs[64 * nvec] ALIGN_ATTR(CACHE_LINE_SIZE);
    ;

    super_slab() = default;


    uint32_t
    _free(void * const parent_addr, T * const addr) {
        IMPOSSIBLE_VALUES(((uint64_t)addr) < ((uint64_t)(&inner_slabs[0])));

        const uint64_t pos_idx =
            (((uint64_t)addr) - ((uint64_t)(&inner_slabs[0]))) /
            sizeof(inner_slab_t);

        IMPOSSIBLE_VALUES(pos_idx >= nvec * 64);

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
        for (uint32_t i = 0; i < nvec; ++i) {
            while (1) {
                while (available_slabs[i] != FULL_ALLOC_VEC) {
                    uint32_t idx;

                    // really not sure if this is worth it
                    if constexpr (0 &&
                                  std::is_same<inner_slab_t, slab<T>>::value) {
                        uint64_t lavailable_slabs = available_slabs[i];
                        lavailable_slabs =
                            (lavailable_slabs >> _tlv_rand) |
                            (lavailable_slabs << (64 - _tlv_rand));

                        idx = (bits::tzcnt<uint64_t>(~lavailable_slabs) +
                               _tlv_rand) &
                              63;
                    }
                    else {
                        idx = bits::tzcnt<uint64_t>(~available_slabs[i]);
                    }

                    // fast path of successful allocation
                    if (BRANCH_LIKELY(idx < 64)) {
                        const uint64_t ret =
                            (inner_slabs + 64 * i + idx)->_allocate(start_cpu);
                        // fast path complete
                        if (BRANCH_LIKELY(successful(ret))) {
                            return ret;
                        }
                        // branch full try to mark bit as full
                        else if (ret == FAILED_FULL) {
                            if (BRANCH_UNLIKELY(
                                    restarting_set_bit(available_slabs + i,
                                                       idx,
                                                       start_cpu) ==
                                    _RSEQ_MIGRATED)) {
                                return FAILED_RSEQ;
                            }
                            continue;
                        }


                        else if (ret & SLAB_READY) {
                            if (BRANCH_UNLIKELY(
                                    restarting_unset_bit(available_slabs + i,
                                                         idx,
                                                         start_cpu) ==
                                    _RSEQ_MIGRATED)) {
                                // this avoid a memory leak if we migrated (but
                                // is pretty unlikely)
                                atomic_xor(freed_slabs + i, ((1UL) << idx));
                            }
                            return ret;
                        }
                        /*
                        else if (ret == SLAB_READY) {
                            if (BRANCH_UNLIKELY(
                                    restarting_unset_bit(available_slabs + i,
                                                         idx,
                                                         start_cpu) ==
                                    _RSEQ_MIGRATED)) {
                                // this avoid a memory leak if we migrated (but
                                // is pretty unlikely)
                                atomic_xor(freed_slabs + i, ((1UL) << idx));
                                return FAILED_RSEQ;
                            }
                            continue;
                        }
                        */
                        // inner alloc ret == failed rseq
                        else {
                            return FAILED_RSEQ;
                        }
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
                        // continue in while(1)
                        continue;
                    }
                    return FAILED_RSEQ;
                }
                if (available_slabs[i] == FULL_ALLOC_VEC) {
                    break;
                }
            }
        }
        return FAILED_FULL;
    }
};


#endif
