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

struct empty {};
template<typename T, uint32_t nvec = 7, typename _T = empty>
struct slab {
    static constexpr const uint64_t capacity = 64 * nvec;
    
    uint64_t available_slots[nvec] ALIGN_ATTR(CACHE_LINE_SIZE);
    // the freed_slots_lock is necesary to prevent a race condition where thread
    // A see available_slots == vec::FULL, get preempted by thread B (on same
    // core), thread B sees the same. Thread A is brough back into context (on
    // the same core) and successfully store freed_slots -> available_slots,
    // gets preempted by thread C who allocates the newly freed slot. then
    // thread B is brought back into context (on the same core) and successfully
    // stores freed_slots -> available_slots, then thread A/B in any order unset
    // freed_slots. The next allocation would return the same ptr as was
    // returned by thread C's allocation.
    uint64_t freed_slots_lock;

    uint64_t freed_slots[nvec] ALIGN_ATTR(CACHE_LINE_SIZE);
    T        obj_arr[64 * nvec] ALIGN_ATTR(CACHE_LINE_SIZE);


    slab() = default;

    void
    _optimistic_free(T * const addr, const uint32_t start_cpu) {
        IMPOSSIBLE_VALUES(((uint64_t)addr) < ((uint64_t)(&obj_arr[0])));
        const uint64_t pos_idx =
            (((uint64_t)addr) - ((uint64_t)(&obj_arr[0]))) / sizeof(T);

        IMPOSSIBLE_VALUES(pos_idx >= nvec * 64);

        if (BRANCH_UNLIKELY(rseq_xor(available_slots + (pos_idx / 64),
                                     ((1UL) << (pos_idx % 64)),
                                     start_cpu))) {
            atomic_or(freed_slots + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
        }
    }


    void
    _free(T * const addr) {
        IMPOSSIBLE_VALUES(((uint64_t)addr) < ((uint64_t)(&obj_arr[0])));

        const uint64_t pos_idx =
            (((uint64_t)addr) - ((uint64_t)(&obj_arr[0]))) / sizeof(T);

        IMPOSSIBLE_VALUES(pos_idx >= nvec * 64);
        atomic_or(freed_slots + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
    }

    uint64_t
    _allocate(const uint32_t start_cpu) {
        for (uint32_t i = 0; i < nvec; ++i) {
            // try allocate
            if (BRANCH_LIKELY(available_slots[i] != FULL_ALLOC_VEC)) {
                const uint32_t idx =
                    bits::find_first_zero<uint64_t>(available_slots[i]);
                if(BRANCH_UNLIKELY(idx == 64)) {
                    continue;
                }
                if (BRANCH_UNLIKELY(or_if_unset(available_slots + i,
                                                ((1UL) << idx),
                                                start_cpu))) {
                    return FAILED_RSEQ;
                }
                return ((uint64_t)&obj_arr[64 * i + idx]);
            }
        }
        if (BRANCH_UNLIKELY(acquire_lock(&freed_slots_lock, start_cpu))) {
            return FAILED_RSEQ;
        }

        for (uint32_t i = 0; i < nvec; ++i) {
            if (BRANCH_UNLIKELY(available_slots[i] != FULL_ALLOC_VEC)) {
                const uint32_t idx =
                    bits::find_first_zero<uint64_t>(available_slots[i]);
                if (BRANCH_UNLIKELY(or_if_unset(available_slots + i,
                                                ((1UL) << idx),
                                                start_cpu))) {
                    freed_slots_lock = 0;
                    return FAILED_RSEQ;
                }
                freed_slots_lock = 0;
                return ((uint64_t)&obj_arr[64 * i + idx]);
            }
            if (freed_slots[i] != EMPTY_FREE_VEC) {
                const uint64_t reclaimed_slots = freed_slots[i];
                atomic_xor(freed_slots + i, reclaimed_slots);
                available_slots[i] ^= (reclaimed_slots & (reclaimed_slots - 1));
                freed_slots_lock = 0;
                return ((uint64_t)(
                    &obj_arr[64 * i +
                             bits::find_first_one<uint64_t>(reclaimed_slots)]));
            }
        }
        freed_slots_lock = 0;
        return FAILED_VEC_FULL;
    }
};

#endif
