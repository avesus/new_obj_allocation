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


template<typename T, uint32_t nvec = 7, typename inner_slab_t = slab<T>>
struct super_slab {
    uint64_t     available_slabs[nvec] ALIGN_ATTR(CACHE_LINE_SIZE);
    uint64_t     freed_slabs_lock;
    uint64_t     freed_slabs[nvec] ALIGN_ATTR(CACHE_LINE_SIZE);
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
            if (!(freed_slabs[(pos_idx / 64)] & ((1UL) << (pos_idx % 64)))) {
                atomic_or(freed_slabs + (pos_idx / 64),
                          ((1UL) << (pos_idx % 64)));
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

        if (!(freed_slabs[(pos_idx / 64)] & ((1UL) << (pos_idx % 64)))) {
            atomic_or(freed_slabs + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
        }
    }

    template<typename _T            = T,
             uint32_t _nvec         = nvec,
             typename _inner_slab_t = inner_slab_t>
    typename std::enable_if<(is_same_template<slab<_T>, _inner_slab_t>),
                            uint64_t>::type


    _allocate(const uint32_t start_cpu) {
        for (uint32_t i = 0; i < nvec; ++i) {
            uint64_t skip_next = ~(0UL);
            while (1) {
                while (BRANCH_LIKELY((available_slabs[i] & skip_next) != FULL_ALLOC_VEC)) {

                    const uint32_t idx =
                        bits::find_first_zero<uint64_t>(available_slabs[i] & skip_next);
                    const uint64_t ret =
                        (inner_slabs + 64 * i + idx)->_allocate(start_cpu);

                    if (BRANCH_LIKELY(successful(
                            ret))) {  // fast path of successful allocation
                        return ret;
                    }
                    else if (ret) {  // full
                        if(ret == FAILED_TRY_NEXT) {
                            skip_next = ~((1UL) << idx);
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
                if (freed_slabs[i] != EMPTY_FREE_VEC) {
                    skip_next = ~(0UL);
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
        }
        return FAILED_VEC_FULL;
    }

    template<typename _T            = T,
             uint32_t _nvec         = nvec,
             typename _inner_slab_t = inner_slab_t>
    typename std::enable_if<!(is_same_template<slab<_T>, _inner_slab_t>),
                            uint64_t>::type
    _allocate(const uint32_t start_cpu) {
        for (uint32_t i = 0; i < nvec; ++i) {
            while (1) {
                while (BRANCH_LIKELY((available_slabs[i]) != FULL_ALLOC_VEC)) {

                    const uint32_t idx =
                        bits::find_first_zero<uint64_t>(available_slabs[i]);
                    const uint64_t ret =
                        (inner_slabs + 64 * i + idx)->_allocate(start_cpu);

                    if (BRANCH_LIKELY(successful(
                            ret))) {  // fast path of successful allocation
                        return ret;
                    }
                    else if (ret) {  // full
                        if (or_if_unset(available_slabs + i,
                                        ((1UL) << idx),
                                        start_cpu)) {
                            return FAILED_RSEQ;
                        }
                        continue;
                    }
                    return FAILED_RSEQ;
                }
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
        }
        return FAILED_VEC_FULL;
    }
};


#endif
