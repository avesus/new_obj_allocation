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
    static constexpr const uint64_t capacity =
        64 * nvec * inner_slab_t::capacity;

    uint64_t     available_slabs[nvec] ALIGN_ATTR(CACHE_LINE_SIZE);
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

        (inner_slabs + pos_idx)->_optimistic_free(addr, start_cpu);
        if (BRANCH_UNLIKELY(restarting_unset_bit_hard(
                available_slabs + (pos_idx / 64),
                // do not need to mod pos_idx.
                // btr instruction does automatically
                // https://www.felixcloutier.com/x86/bts
                pos_idx,
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


    uint64_t
    _allocate(const uint32_t start_cpu) {
        for (uint32_t i = 0; i < nvec; ++i) {
            while (1) {
                while (available_slabs[i] != FULL_ALLOC_VEC) {
                    uint32_t idx;
                    if constexpr (is_same_template<inner_slab_t, slab<T>>) {
                        uint64_t lavailable_slabs = available_slabs[i];
                        lavailable_slabs          = ~lavailable_slabs;
                        lavailable_slabs =
                            (lavailable_slabs >> _tlv_rand) |
                            (lavailable_slabs << (64 - _tlv_rand));

                        idx = (bits::tzcnt<uint64_t>(lavailable_slabs) +
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
                        else if (ret == FAILED_VEC_FULL) {
                            if (BRANCH_UNLIKELY(
                                    restarting_set_bit_hard(available_slabs + i,
                                                            idx,
                                                            start_cpu) ==
                                    _RSEQ_MIGRATED)) {
                                return FAILED_RSEQ;
                            }
                        }
                        // inner alloc ret == failed rseq
                        else {
                            return FAILED_RSEQ;
                        }
                    }
                }

                // available_slabs[i] == full
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
                        atomic_xor(freed_slabs + i, reclaimed_slabs);
                    }
                    // continue in while(1)
                    continue;
                }
                // this handles the case where available_slabs[i] was seen,
                // full, but another thread reclaimed free list before the check
                if (available_slabs[i] == FULL_ALLOC_VEC) {
                    break;
                }
            }
        }
        return FAILED_VEC_FULL;
    }
};


#endif
