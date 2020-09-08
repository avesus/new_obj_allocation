#ifndef _SUPER_SLAB_H_
#define _SUPER_SLAB_H_

#include <misc/cpp_attributes.h>
#include <optimized/bits.h>
#include <system/sys_info.h>

#include <allocator/rseq/rseq_base.h>

#include <allocator/common/internal_returns.h>
#include <allocator/common/safe_atomics.h>

#include <allocator/slab_layout/obj_slab.h>
#include <allocator/slab_layout/thread_cache.h>

#include <allocator/common/vec_ops.h>


//////////////////////////////////////////////////////////////////////


template<typename T, typename inner_slab_t, uint32_t nvec = 1>
struct super_slab {
    static constexpr const uint32_t log_nvec =
        cmath::ulog2<uint32_t>(64 * nvec);
    static constexpr const uint64_t capacity =
        64 * nvec * inner_slab_t::capacity;

    uint64_t available_slabs[nvec] CACHE_ALIGN;

    // off core freed_slabs (expensive to touch and REALLY expensive to set)
    uint64_t freed_slabs[nvec] CACHE_ALIGN;

    inner_slab_t inner_slabs[64 * nvec] CACHE_ALIGN;

    super_slab() = default;

    template<uint32_t shift_offset, typename _inner_slab_t = inner_slab_t>
    constexpr static __m256i ALWAYS_INLINE CONST_ATTR
    get_idx_v(__m256i ptrs_v) {
        /*        uint32_t print_ptrs[8] ALIGN_ATTR(32);
        uint32_t print_base[8] ALIGN_ATTR(32);
        uint32_t print_adj_ptrs[8] ALIGN_ATTR(32);
        uint32_t print_nidx_v[8] ALIGN_ATTR(32);*/

        __m256i idx_v  = vmath::vdiv<uint32_t, sizeof(inner_slab_t)>(ptrs_v);
        __m256i base_v = vmath::vmult<uint32_t, sizeof(inner_slab_t)>(idx_v);

        //        fprintf(stderr, "SS(%d)\n", shift_offset);

        if constexpr (shift_offset) {
            __m256i adjusted_idx_v     = _mm256_slli_epi32(idx_v, shift_offset);
            __m256i adjusted_ptrs_v_t0 = _mm256_sub_epi32(ptrs_v, base_v);
            __m256i adjusted_ptrs_v    = _mm256_sub_epi32(
                adjusted_ptrs_v_t0,
                _mm256_set1_epi32(offsetof(_inner_slab_t, obj_arr)));
            __m256i next_idx_v =
                _inner_slab_t::template get_idx_v<shift_offset + log_nvec>(
                    adjusted_ptrs_v);
            return _mm256_or_si256(adjusted_idx_v, next_idx_v);
        }
        else {
            __m256i adjusted_ptrs_v_t0 = _mm256_sub_epi32(ptrs_v, base_v);
            __m256i adjusted_ptrs_v    = _mm256_sub_epi32(
                adjusted_ptrs_v_t0,
                _mm256_set1_epi32(offsetof(_inner_slab_t, inner_slabs)));
            __m256i next_idx_v =
                _inner_slab_t::template get_idx_v<shift_offset + log_nvec>(
                    adjusted_ptrs_v);
            return _mm256_or_si256(idx_v, next_idx_v);
        }
    }

    template<uint32_t p_offset>
    uint32_t
    _tc_free_slow(void * const parent_addr, uint32_t idx_mask) {

        uint64_t freed_mask = 0;
        uint32_t ret        = 0;

        uint64_t lfreed_mask =
            create_full_mask((const uint32_t * const)(tc.ptrs), idx_mask);

        IMPOSSIBLE_COND(lfreed_mask == 0);
        freed_mask |= lfreed_mask;

        do {
            uint32_t next_t_idx = bits::tzcnt<uint64_t>(lfreed_mask);
            uint32_t next_idx_mask =
                create_idx_mask((const uint32_t * const)(tc.ptrs),
                                next_t_idx << p_offset,
                                ((64 * nvec) - 1) << p_offset,
                                idx_mask);

            lfreed_mask ^= ((1UL) << next_t_idx);
            ret |= (inner_slabs + next_t_idx)
                       ->template _tc_free_slow<p_offset + log_nvec>(
                           (void * const)freed_slabs,
                           next_idx_mask);
            idx_mask ^= next_idx_mask;
        } while (lfreed_mask);

        if (ret) {
            if (freed_slabs[0] == 0) {
                PREFETCH_W(parent_addr);
                atomic_or(freed_slabs, freed_mask);
                return 1;
            }
            else {
                atomic_or(freed_slabs, freed_mask);
            }
        }
        return 0;
    }


    void
    _tc_first_free_slow(uint32_t idx_mask) {

        uint64_t freed_mask = 0;
        uint32_t ret        = 0;
        uint64_t lfreed_mask =
            create_full_mask((const uint32_t * const)(tc.ptrs), idx_mask);

        IMPOSSIBLE_COND(lfreed_mask == 0);
        freed_mask |= lfreed_mask;

        do {
            uint32_t next_t_idx = bits::tzcnt<uint64_t>(lfreed_mask);
            uint32_t next_idx_mask =
                create_idx_mask((const uint32_t * const)(tc.ptrs),
                                next_t_idx,
                                ((64 * nvec) - 1),
                                idx_mask);

            lfreed_mask ^= ((1UL) << next_t_idx);
            ret |= (inner_slabs + next_t_idx)
                       ->template _tc_free_slow<log_nvec>(
                           (void * const)freed_slabs,
                           next_idx_mask);
        } while (lfreed_mask);

        if (ret) {
            atomic_or(freed_slabs, freed_mask);
        }
    }


    template<uint32_t p_offset>
    uint32_t
    _tc_free_fast(void * const parent_addr,
                  __m256i      idx_v1,
                  __m256i      idx_v2,
                  __m256i      idx_v3,
                  __m256i      idx_v4) {

        __m256i lidx_v1 =
            _mm256_and_si256(idx_v1, _mm256_set1_epi32((64 * nvec) - 1));
        __m256i lidx_v2 =
            _mm256_and_si256(idx_v2, _mm256_set1_epi32((64 * nvec) - 1));
        __m256i lidx_v3 =
            _mm256_and_si256(idx_v3, _mm256_set1_epi32((64 * nvec) - 1));
        __m256i lidx_v4 =
            _mm256_and_si256(idx_v4, _mm256_set1_epi32((64 * nvec) - 1));

        __m256i freed_mask_v1 = create_partial_mask_v(lidx_v1);
        __m256i freed_mask_v2 = create_partial_mask_v(lidx_v2);
        __m256i freed_mask_v3 = create_partial_mask_v(lidx_v3);
        __m256i freed_mask_v4 = create_partial_mask_v(lidx_v4);

        __m256i freed_mask_v12 =
            merge_partial_masks_v(freed_mask_v1, freed_mask_v2);
        __m256i freed_mask_v34 =
            merge_partial_masks_v(freed_mask_v3, freed_mask_v4);

        __m256i freed_mask_v =
            merge_partial_masks_v(freed_mask_v12, freed_mask_v34);

        uint64_t freed_mask = reduce_mask_v(freed_mask_v);

        IMPOSSIBLE_COND(freed_mask == 0);

        uint32_t _idx = bits::tzcnt<uint64_t>(freed_mask);
        IMPOSSIBLE_COND(_idx >= 64);


        if (((1UL) << _idx) == freed_mask) {
            if constexpr (std::is_same<inner_slab_t, slab<T>>::value) {
                if ((inner_slabs + _idx)
                        ->template _tc_free_fast<p_offset + log_nvec>(
                            (void * const)freed_slabs,
                            _mm256_srli_epi32(idx_v1, log_nvec + 6),
                            _mm256_srli_epi32(idx_v2, log_nvec + 6),
                            _mm256_srli_epi32(idx_v3, log_nvec + 6),
                            _mm256_srli_epi32(idx_v4, log_nvec + 6))) {
                    if (freed_slabs[0] == 0) {
                        PREFETCH_W(parent_addr);
                        atomic_or(freed_slabs, freed_mask);
                        return 1;
                    }
                    atomic_or(freed_slabs, freed_mask);
                }
            }
            else {
                if ((inner_slabs + _idx)
                        ->_tc_free_fast<p_offset + log_nvec>(
                            (void * const)freed_slabs,
                            _mm256_srli_epi32(idx_v1, log_nvec),
                            _mm256_srli_epi32(idx_v2, log_nvec),
                            _mm256_srli_epi32(idx_v3, log_nvec),
                            _mm256_srli_epi32(idx_v4, log_nvec))) {
                    if (freed_slabs[0] == 0) {
                        PREFETCH_W(parent_addr);
                        atomic_or(freed_slabs, freed_mask);
                        return 1;
                    }
                    atomic_or(freed_slabs, freed_mask);
                }
            }
        }
        else {
            __m256i idx_list_v12 = create_packed_idx_vec_v(lidx_v1, lidx_v2);
            __m256i idx_list_v34 = create_packed_idx_vec_v(lidx_v3, lidx_v4);
            __m256i idx_list_v =
                create_packed_idx_vec_v(idx_list_v12, idx_list_v34);

            uint8_t idx_list[32] ALIGN_ATTR(32);
            _mm256_store_si256((__m256i *)idx_list, idx_list_v);

            uint32_t aggregate_mask = ~0;
            uint32_t idx            = 0;
            uint32_t ret            = 0;
            while (1) {
                uint32_t t_idx    = idx_list[idx];
                uint32_t idx_mask = _mm256_movemask_epi8(
                    _mm256_cmpeq_epi8(idx_list_v, _mm256_set1_epi8(t_idx)));
                assert(freed_mask & ((1UL) << t_idx));

                IMPOSSIBLE_COND(t_idx >= 64);
                IMPOSSIBLE_COND(idx_mask == 0);
                IMPOSSIBLE_COND((idx_mask & aggregate_mask) != idx_mask);

                aggregate_mask ^= idx_mask;
                ret |= (inner_slabs + t_idx)
                           ->template _tc_free_slow<p_offset + log_nvec>(
                               (void * const)freed_slabs,
                               idx_mask);


                if (aggregate_mask) {
                    idx = bits::tzcnt<uint32_t>(aggregate_mask);
                    IMPOSSIBLE_COND(idx >= 32);
                    continue;
                }
                break;
            }
            if (ret) {
                if (freed_slabs[0] == 0) {
                    PREFETCH_W(parent_addr);
                    atomic_or(freed_slabs, freed_mask);
                    return 1;
                }
                atomic_or(freed_slabs, freed_mask);
            }
        }
        return 0;
    }

    void
    _tc_first_free_fast(__m256i idx_v1,
                        __m256i idx_v2,
                        __m256i idx_v3,
                        __m256i idx_v4) {

        __m256i lidx_v1 =
            _mm256_and_si256(idx_v1, _mm256_set1_epi32((64 * nvec) - 1));
        __m256i lidx_v2 =
            _mm256_and_si256(idx_v2, _mm256_set1_epi32((64 * nvec) - 1));
        __m256i lidx_v3 =
            _mm256_and_si256(idx_v3, _mm256_set1_epi32((64 * nvec) - 1));
        __m256i lidx_v4 =
            _mm256_and_si256(idx_v4, _mm256_set1_epi32((64 * nvec) - 1));

        __m256i freed_mask_v1 = create_partial_mask_v(lidx_v1);
        __m256i freed_mask_v2 = create_partial_mask_v(lidx_v2);
        __m256i freed_mask_v3 = create_partial_mask_v(lidx_v3);
        __m256i freed_mask_v4 = create_partial_mask_v(lidx_v4);

        __m256i freed_mask_v12 =
            merge_partial_masks_v(freed_mask_v1, freed_mask_v2);
        __m256i freed_mask_v34 =
            merge_partial_masks_v(freed_mask_v3, freed_mask_v4);

        __m256i freed_mask_v =
            merge_partial_masks_v(freed_mask_v12, freed_mask_v34);

        uint64_t freed_mask = reduce_mask_v(freed_mask_v);

        IMPOSSIBLE_COND(freed_mask == 0);


        uint32_t _idx = bits::tzcnt<uint64_t>(freed_mask);
        IMPOSSIBLE_COND(_idx >= 64);


        if (((1UL) << _idx) == freed_mask) {
            if constexpr (std::is_same<inner_slab_t, slab<T>>::value) {
                if ((inner_slabs + _idx)
                        ->template _tc_free_fast<log_nvec>(
                            (void * const)freed_slabs,
                            _mm256_srli_epi32(idx_v1, log_nvec + 6),
                            _mm256_srli_epi32(idx_v2, log_nvec + 6),
                            _mm256_srli_epi32(idx_v3, log_nvec + 6),
                            _mm256_srli_epi32(idx_v4, log_nvec + 6))) {
                    atomic_or(freed_slabs, freed_mask);
                }

            }
            else {
                if ((inner_slabs + _idx)
                        ->template _tc_free_fast<log_nvec>(
                            (void * const)freed_slabs,
                            _mm256_srli_epi32(idx_v1, log_nvec),
                            _mm256_srli_epi32(idx_v2, log_nvec),
                            _mm256_srli_epi32(idx_v3, log_nvec),
                            _mm256_srli_epi32(idx_v4, log_nvec))) {
                    atomic_or(freed_slabs, freed_mask);
                }

            }
        }
        else {

            __m256i idx_list_v12 = create_packed_idx_vec_v(lidx_v1, lidx_v2);
            __m256i idx_list_v34 = create_packed_idx_vec_v(lidx_v3, lidx_v4);
            __m256i idx_list_v =
                create_packed_idx_vec_v(idx_list_v12, idx_list_v34);

            uint8_t idx_list[32] ALIGN_ATTR(32);
            _mm256_store_si256((__m256i *)idx_list, idx_list_v);

            uint32_t aggregate_mask = ~0;
            uint32_t idx            = 0;
            uint32_t ret            = 0;
            while (1) {
                uint32_t t_idx    = idx_list[idx];
                uint32_t idx_mask = _mm256_movemask_epi8(
                    _mm256_cmpeq_epi8(idx_list_v, _mm256_set1_epi8(t_idx)));

                IMPOSSIBLE_COND(idx_mask == 0);
                IMPOSSIBLE_COND((idx_mask & aggregate_mask) != idx_mask);

                aggregate_mask ^= idx_mask;
                ret |= (inner_slabs + idx)
                           ->template _tc_free_slow<log_nvec>(
                               (void * const)freed_slabs,
                               idx_mask);


                if (aggregate_mask) {
                    idx = bits::tzcnt<uint32_t>(aggregate_mask);
                    IMPOSSIBLE_COND(idx >= 32);
                    continue;
                }
                break;
            }
            if (ret) {
                atomic_or(freed_slabs, freed_mask);
            }
        }
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
                    volatile uint64_t tmp = (uint64_t)(freed_slabs);
                    const uint64_t    reclaimed_slabs =
                        restarting_reclaim_free_slabs(available_slabs + i,
                                                      freed_slabs + i,
                                                      start_cpu);
                    volatile uint64_t _tmp = (uint64_t)(freed_slabs);
                    assert(tmp == _tmp);
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
} CACHE_ALIGN;


#endif
