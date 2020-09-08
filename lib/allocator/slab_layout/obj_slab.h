#ifndef _OBJ_SLAB_H_
#define _OBJ_SLAB_H_

#include <misc/cpp_attributes.h>
#include <optimized/bits.h>
#include <system/sys_info.h>

#include <allocator/rseq/rseq_base.h>

#include <allocator/common/internal_returns.h>
#include <allocator/common/safe_atomics.h>

#include <allocator/slab_layout/obj_slab.h>

#include <stdint.h>

#include <allocator/common/vec_ops.h>
#include <allocator/slab_layout/thread_cache.h>

template<typename T>
struct slab {
    static constexpr const uint64_t capacity = 64 * 64;

    uint64_t outer_avail_vec CACHE_ALIGN;
    uint64_t                 available_slots[64];

    // the freed_slots_lock is necesary to prevent a race condition
    // where thread A see available_slots == FULL_ALLOC_VEC, get
    // preempted by thread B (on same core), thread B sees the
    // same. Thread A is brough back into context (on the same core)
    // and successfully store freed_slots -> available_slots, gets
    // preempted by thread C who allocates the newly freed slot. then
    // thread B is brought back into context (on the same core) and
    // successfully stores freed_slots -> available_slots, then thread
    // A/B in any order unset freed_slots. The next allocation would
    // return the same ptr as was returned by thread C's allocation.
    uint64_t freed_slots_lock;


    uint64_t outer_freed_vec CACHE_ALIGN;
    uint64_t                 freed_slots[64];

    T obj_arr[64 * 64] CACHE_ALIGN;

    ~slab() = default;
    slab()  = default;

    template<uint32_t shift_offset>
    constexpr static __m256i ALWAYS_INLINE CONST_ATTR
    get_idx_v(__m256i ptrs_v) {
        __m256i idx_v = vmath::vdiv<uint32_t, sizeof(T)>(ptrs_v);
        return _mm256_slli_epi32(idx_v, shift_offset);
    }

    template<uint32_t p_offset>
    uint32_t
    _tc_free_slow(void * const parent_addr, uint32_t idx_mask) {

        uint64_t freed_mask = 0;
        while (idx_mask) {
            uint32_t idx = bits::tzcnt<uint32_t>(idx_mask);
            idx_mask ^= (1 << idx);
            uint32_t tc_ptr    = tc.ptrs[idx];
            uint32_t outer_idx = tc_ptr >> (p_offset + 6);
            IMPOSSIBLE_COND(outer_idx >= 64);

            freed_mask |= ((1UL) << outer_idx);

            uint32_t inner_idx = (tc_ptr >> (p_offset)) & 63;
            IMPOSSIBLE_COND(inner_idx >= 64);

            atomic_or(freed_slots + outer_idx, (1UL) << inner_idx);
        }

        PREFETCH_W(parent_addr);
        if(outer_freed_vec == 0) {
            PREFETCH_W(parent_addr);
            atomic_or(&outer_freed_vec, freed_mask);
            return 1;
        }
        atomic_or(&outer_freed_vec, freed_mask);
        return 0;

    }

    template<uint32_t p_offset>
    uint32_t
    _tc_free_fast(void * const parent_addr,
                  __m256i      idx_v1,
                  __m256i      idx_v2,
                  __m256i      idx_v3,
                  __m256i      idx_v4) {
        __m256i outer_lidx_v1 = _mm256_and_si256(idx_v1, _mm256_set1_epi32(63));
        __m256i outer_lidx_v2 = _mm256_and_si256(idx_v2, _mm256_set1_epi32(63));
        __m256i outer_lidx_v3 = _mm256_and_si256(idx_v3, _mm256_set1_epi32(63));
        __m256i outer_lidx_v4 = _mm256_and_si256(idx_v4, _mm256_set1_epi32(63));

        __m256i outer_freed_mask_v1 = create_partial_mask_v(outer_lidx_v1);
        __m256i outer_freed_mask_v2 = create_partial_mask_v(outer_lidx_v2);
        __m256i outer_freed_mask_v3 = create_partial_mask_v(outer_lidx_v3);
        __m256i outer_freed_mask_v4 = create_partial_mask_v(outer_lidx_v4);

        __m256i outer_freed_mask_v12 =
            merge_partial_masks_v(outer_freed_mask_v1, outer_freed_mask_v2);
        __m256i outer_freed_mask_v34 =
            merge_partial_masks_v(outer_freed_mask_v3, outer_freed_mask_v4);

        __m256i outer_freed_mask_v =
            merge_partial_masks_v(outer_freed_mask_v12, outer_freed_mask_v34);

        uint64_t outer_freed_mask = reduce_mask_v(outer_freed_mask_v);

        __m256i idx_list_v12 =
            create_packed_idx_vec_v(outer_lidx_v1, outer_lidx_v2);
        __m256i idx_list_v34 =
            create_packed_idx_vec_v(outer_lidx_v3, outer_lidx_v4);
        __m256i idx_list_v =
            create_packed_idx_vec_v(idx_list_v12, idx_list_v34);

        uint8_t idx_list[32] ALIGN_ATTR(32);
        _mm256_store_si256((__m256i *)idx_list, idx_list_v);

        uint32_t aggregate_mask = ~0;
        uint32_t idx            = 0;
        uint32_t ret            = 0;
        while (1) {

            uint32_t _idx = idx_list[idx];
            IMPOSSIBLE_COND(idx >= 64);
            IMPOSSIBLE_COND(_idx >= 64);
            
            uint32_t idx_mask = _mm256_movemask_epi8(
                _mm256_cmpeq_epi8(idx_list_v, _mm256_set1_epi8(_idx)));


            IMPOSSIBLE_COND(idx_mask == 0);
            IMPOSSIBLE_COND((idx_mask & aggregate_mask) != idx_mask);

            aggregate_mask ^= idx_mask;
            uint64_t idx_free_mask = 0;
            while (idx_mask) {
                uint32_t inner_idx = bits::tzcnt<uint32_t>(idx_mask);
                idx_mask ^= ((1UL) << inner_idx);
                idx_free_mask |=
                    ((1UL) << ((tc.ptrs[inner_idx] >> p_offset) & 63));
            }

            if (!ret && freed_slots[_idx] == 0) {
                ret = 1;
            }
            atomic_or(freed_slots + _idx, idx_free_mask);

            if (aggregate_mask) {
                idx = bits::tzcnt<uint32_t>(aggregate_mask);
                IMPOSSIBLE_COND(idx >= 32);
                continue;
            }
            break;
        }
        if (ret) {
            PREFETCH_W(parent_addr);
            atomic_or(&outer_freed_vec, outer_freed_mask);
            return 1;
        }
        return 0;
    }

    uint32_t
    _free(void * const parent_addr, T * const addr) {
        IMPOSSIBLE_COND(((uint64_t)addr) < ((uint64_t)(&obj_arr[0])));

        const uint64_t pos_idx =
            (((uint64_t)addr) - ((uint64_t)(&obj_arr[0]))) / sizeof(T);

        IMPOSSIBLE_COND(pos_idx >= 64 * 64);

        if (freed_slots[pos_idx / 64] == 0) {
            assert(!(freed_slots[pos_idx / 64] & ((1UL) << (pos_idx % 64))));
            atomic_or(freed_slots + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
            if (outer_freed_vec == 0) {
                PREFETCH_W(parent_addr);
                atomic_or(&outer_freed_vec, ((1UL) << ((pos_idx / 64) % 64)));
                return 1;
            }
            else {
                atomic_or(&outer_freed_vec, ((1UL) << ((pos_idx / 64) % 64)));
                return 0;
            }
        }
        else {
            atomic_or(freed_slots + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
        }

        return 0;
    }

    uint64_t
    _allocate(const uint32_t start_cpu) {
        // try allocate

        if (BRANCH_LIKELY(outer_avail_vec != FULL_ALLOC_VEC)) {

            const uint32_t idx =
                restarting_set_idx(&outer_avail_vec, start_cpu);
            if (BRANCH_LIKELY(idx < _RSEQ_SET_IDX_MIGRATED)) {
                __builtin_prefetch(&obj_arr[idx]);
                return ((uint64_t)&obj_arr[idx]);
            }
            else if (idx == _RSEQ_SET_IDX_MIGRATED) {
                return FAILED_RSEQ;
            }
        }


        if (freed_slots_lock) {
            // this will be corrected by first free
            return FAILED_FULL;
        }

        // at this point chances are high we are using outer_free_vec
        PREFETCH_W(&outer_freed_vec);

        const uint32_t acq_lock_ret =
            restarting_acquire_lock(&freed_slots_lock, start_cpu);
        if (BRANCH_UNLIKELY(acq_lock_ret == _RSEQ_MIGRATED)) {
            return FAILED_RSEQ;
        }
        else if (BRANCH_UNLIKELY(acq_lock_ret == _RSEQ_OTHER_FAILURE)) {
            return FAILED_FULL;
        }

        const uint64_t _to_reclaim_indexes = outer_freed_vec;

        // i know this is a race condition. It doesn't affect correctness.
        atomic_unset(&outer_freed_vec, _to_reclaim_indexes);
        uint64_t to_reclaim_indexes = _to_reclaim_indexes;

#ifdef RETURN_WITH_SLAB_READY
        if (to_reclaim_indexes) {
            uint64_t ret = SLAB_READY;

            uint32_t idx;
            uint64_t to_reclaim;

            // this needs to be in a loop and we need case for find
            // none because there is a race condition in that unset
            // outer_free_vec -> free (set outer free vec by
            // definition) -> reclaim the inner freed_vec. Outer free
            // vec will incorrectly state there is a valid free
            // vector. This won't break anything as long as we check
            // for that
            do {
                idx = _tzcnt_u64(to_reclaim_indexes);
                to_reclaim_indexes ^= ((1UL) << idx);

                to_reclaim = freed_slots[idx];
            } while (to_reclaim_indexes && (!to_reclaim));

            if (!to_reclaim) {
                freed_slots_lock = 0;
                return FAILED_FULL;
            }

            atomic_unset(freed_slots + idx, to_reclaim);

            // take first bit from first reclaimed slot for return
            // value
            available_slots[idx] = ~(to_reclaim & (to_reclaim - 1));

            // create return value (grab it now because we need to
            // fully unwind the _allocate call stacks to indicate that
            // this vector is available again (otherwise you can have
            // a memory leak in that super_slab<super_slab<slab>>,
            // slab fills up causing inner super_slab to fill
            // up. While SLAB_READY will indicate to inner super that
            // that there is free position outer super slab needs to
            // be informed.
            ret |= (uint64_t)(
                &obj_arr[64 * idx + bits::tzcnt<uint64_t>(to_reclaim)]);

// simply reclaim of the rest.

// depending on how full to_reclaim_indexes is tzcnt
// iteration vs ++ iteration is better
#ifdef STD_ITER
            for (++idx; idx < 64; ++idx) {
                if (BRANCH_UNLIKELY(!(to_reclaim_indexes & ((1UL) << idx)))) {
                    continue;
                }
#else
            while (to_reclaim_indexes) {
                idx = _tzcnt_u64(to_reclaim_indexes);
                to_reclaim_indexes ^= ((1UL) << idx);
#endif

                to_reclaim = freed_slots[idx];
                atomic_unset(freed_slots + idx, to_reclaim);

                available_slots[idx] = ~to_reclaim;
            }

            outer_avail_vec  = ~_to_reclaim_indexes;
            freed_slots_lock = 0;
            return ret;
        }
#endif
#ifndef RETURN_WITH_SLAB_READY

        if (to_reclaim_indexes) {
            do {
                const uint32_t idx = _tzcnt_u64(to_reclaim_indexes);
                to_reclaim_indexes ^= ((1UL) << idx);
                const uint64_t to_reclaim = freed_slots[idx];
                atomic_unset(freed_slots + idx, to_reclaim);
                available_slots[idx] = ~to_reclaim;
            } while (to_reclaim_indexes);

            outer_avail_vec  = ~_to_reclaim_indexes;
            freed_slots_lock = 0;
            return SLAB_READY;
        }
#endif

        freed_slots_lock = 0;
        return FAILED_FULL;
    }
} CACHE_ALIGN;


#endif
