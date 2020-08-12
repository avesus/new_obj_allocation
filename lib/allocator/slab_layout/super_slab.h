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
// returns whether a an inner_slab_t of base class super_slab or regular slab
template<typename, typename>
constexpr bool is_same_template{ false };

template<template<typename, uint32_t, typename>
         typename T,  // typename T in C++17
         typename generic_T1,
         uint32_t generic_V1,
         typename generic_S1,
         typename generic_T2,
         uint32_t generic_V2,
         typename generic_S2>
constexpr bool is_same_template<T<generic_T1, generic_V1, generic_S1>,
                                T<generic_T2, generic_V2, generic_S2>>{ true };
//////////////////////////////////////////////////////////////////////

enum reclaim_policy {
    PERCPU = 0,  // This will result in faster freeing but slower reclaiming
    SHARED = 1   // this will result in slower freeing but faster reclaiming
};


template<typename T,
         uint32_t nvec         = 8,
         typename inner_slab_t = slab<T>,
         reclaim_policy rp     = reclaim_policy::SHARED>
struct super_slab {
    static constexpr const uint32_t free_idx =
        rp == reclaim_policy::SHARED ? nvec : 8 * NPROCS;
    uint64_t     available_slabs[nvec] ALIGN_ATTR(CACHE_LINE_SIZE);
    uint64_t     freed_slabs[free_idx] ALIGN_ATTR(CACHE_LINE_SIZE);
    inner_slab_t inner_slabs[64 * nvec] ALIGN_ATTR(CACHE_LINE_SIZE);
    ;

    super_slab() = default;

    void
    _optimistic_free(T * const addr, const uint32_t start_cpu) {
        IMPOSSIBLE_VALUES(((uint64_t)addr) < ((uint64_t)(&inner_slabs[0])));

        const uint64_t pos_idx =
            (((uint64_t)addr) - ((uint64_t)(&inner_slabs[0]))) /
            sizeof(inner_slab_t);

        IMPOSSIBLE_VALUES(pos_idx >= nvec * 64);

        (inner_slabs + pos_idx)->_free(addr);
        if (BRANCH_UNLIKELY(rseq_and(available_slabs + (pos_idx / 64),
                                     ~((1UL) << (pos_idx % 64)),
                                     start_cpu))) {
            if constexpr (rp == reclaim_policy::SHARED) {
                if (!(freed_slabs[(pos_idx / 64)] &
                      ((1UL) << (pos_idx % 64)))) {
                    atomic_or(freed_slabs + (pos_idx / 64),
                              ((1UL) << (pos_idx % 64)));
                }
            }
            else {
                while (BRANCH_UNLIKELY(
                    rseq_any_cpu_or(freed_slabs, (1UL) << (pos_idx % 64))))
                    ;
            }
        }
    }

    void
    _free(T * const addr) {
        IMPOSSIBLE_VALUES(((uint64_t)addr) < ((uint64_t)(&inner_slabs[0])));


        const uint64_t pos_idx =
            (((uint64_t)addr) - ((uint64_t)(&inner_slabs[0]))) /
            sizeof(inner_slab_t);

        IMPOSSIBLE_VALUES(pos_idx >= nvec * 64);


        (inner_slabs + pos_idx)->_free(addr);

        if constexpr (rp == reclaim_policy::SHARED) {
            if (!(freed_slabs[(pos_idx / 64)] & ((1UL) << (pos_idx % 64)))) {
                atomic_or(freed_slabs + (pos_idx / 64),
                          ((1UL) << (pos_idx % 64)));
            }
        }
        else {
            while (BRANCH_UNLIKELY(
                rseq_any_cpu_or(freed_slabs, (1UL) << (pos_idx % 64))))
                ;
        }
    }

    uint64_t
    _allocate(const uint32_t start_cpu) {

        for (uint32_t i = 0; i < nvec; ++i) {
            uint32_t _i            = 0;
            uint64_t try_next_skip = ~(0UL);
            while (1) {
                while (BRANCH_LIKELY((available_slabs[i] & try_next_skip) !=
                                     FULL_ALLOC_VEC)) {

                    const uint32_t idx = bits::find_first_zero<uint64_t>(
                        available_slabs[i] & try_next_skip);
                    const uint64_t ret =
                        (inner_slabs + 64 * i + idx)->_allocate(start_cpu);

                    if (BRANCH_LIKELY(successful(
                            ret))) {  // fast path of successful allocation
                        return ret;
                    }
                    else if (ret) {  // full

                        if (ret == FAILED_TRY_NEXT) {
                            try_next_skip = ~((1UL) << idx);
                        }
                        else if (or_if_unset(available_slabs + i,
                                             ((1UL) << idx),
                                             start_cpu)) {
                            return FAILED_RSEQ;
                        }

                        continue;
                    }
                    return FAILED_RSEQ;
                }
                try_next_skip = ~(0UL);
                if constexpr (rp == reclaim_policy::SHARED) {
                    if (freed_slabs[i] != EMPTY_FREE_VEC) {
                        const uint64_t reclaimed_slabs =
                            try_reclaim_all_free_slots(available_slabs + i,
                                                       freed_slabs + i,
                                                       start_cpu);
                        if (BRANCH_LIKELY(reclaimed_slabs)) {
                            atomic_xor(freed_slabs + i, reclaimed_slabs);
                            continue;
                        }
                        return FAILED_RSEQ;
                    }
                    // continues will reset, if we ever faill through to here we
                    // want to stop
                    break;
                }
                else {
                    if (_i) {
                        break;
                    }
                    for (; _i < 8 * NPROCS; _i += 8) {
                        if (freed_slabs[_i + i] != EMPTY_FREE_VEC) {
                            const uint64_t reclaimed_slabs =
                                try_reclaim_all_free_slots(available_slabs + i,
                                                           freed_slabs + _i + i,
                                                           start_cpu);

                            if (BRANCH_LIKELY(reclaimed_slabs)) {
                                atomic_xor(freed_slabs + _i + i,
                                           reclaimed_slabs);
                                continue;
                            }
                            return FAILED_RSEQ;
                        }
                    }
                }
            }
        }
        return FAILED_VEC_FULL;
    }

    uint64_t
    _allocate2(const uint32_t start_cpu) {

        uint32_t       _i            = 0;
        const uint64_t try_next_skip = ~(0UL);
        uint32_t       i             = 0;
        while (1) {
            for (; i < nvec; ++i) {
                while (BRANCH_LIKELY((available_slabs[i] & try_next_skip) !=
                                     FULL_ALLOC_VEC)) {

                    const uint32_t idx = bits::find_first_zero<uint64_t>(
                        available_slabs[i] & try_next_skip);
                    const uint64_t ret =
                        (inner_slabs + 64 * i + idx)->_allocate(start_cpu);

                    if (BRANCH_LIKELY(successful(
                            ret))) {  // fast path of successful allocation
                        return ret;
                    }
                    else if (ret) {  // full
                                     //      try_next_skip = ~(0UL);
                        //                        if(ret == FAILED_TRY_NEXT) {
                        //                            try_next_skip = ~((1UL) <<
                        //                            idx);
                        //                        }
                        //                        else
                        if (or_if_unset(available_slabs + i,
                                        ((1UL) << idx),
                                        start_cpu)) {
                            return FAILED_RSEQ;
                        }

                        continue;
                    }
                    return FAILED_RSEQ;
                }
            }
            for (i = 0; i < nvec; ++i) {
                if constexpr (rp == reclaim_policy::SHARED) {
                    if (freed_slabs[i] != EMPTY_FREE_VEC) {
                        const uint64_t reclaimed_slabs =
                            try_reclaim_all_free_slots(available_slabs + i,
                                                       freed_slabs + i,
                                                       start_cpu);
                        if (BRANCH_LIKELY(reclaimed_slabs)) {
                            atomic_xor(freed_slabs + i, reclaimed_slabs);
                            break;
                        }
                        return FAILED_RSEQ;
                    }
                    // continues will reset, if we ever faill through to here we
                    // want to stop
                }
                else {
                    uint32_t reclaimed_any = 0;
                    for (; _i < 8 * NPROCS; _i += 8) {
                        if (freed_slabs[_i + i] != EMPTY_FREE_VEC) {
                            const uint64_t reclaimed_slabs =
                                try_reclaim_all_free_slots(available_slabs + i,
                                                           freed_slabs + _i + i,
                                                           start_cpu);

                            if (BRANCH_LIKELY(reclaimed_slabs)) {
                                reclaimed_any = 1;
                                atomic_xor(freed_slabs + _i + i,
                                           reclaimed_slabs);
                                continue;
                            }
                            return FAILED_RSEQ;
                        }
                    }
                    if (reclaimed_any) {
                        break;
                    }
                }
            }
            if (i == nvec) {
                break;
            }
        }
        return FAILED_VEC_FULL;
    }
};


#endif
