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


    uint32_t
    _free(void * const parent_addr, T * const addr) {
        IMPOSSIBLE_VALUES(((uint64_t)addr) < ((uint64_t)(&obj_arr[0])));

        const uint64_t pos_idx =
            (((uint64_t)addr) - ((uint64_t)(&obj_arr[0]))) / sizeof(T);

        IMPOSSIBLE_VALUES(pos_idx >= nvec * 64);

        // if 0 going into this tell others to set bit
        if (freed_slots[pos_idx / 64] == 0) {

            // prefetch parent (the lock instruction should take enough time
            // that this will actually hide some latency)
            PREFETCH_W(parent_addr);
            atomic_or(freed_slots + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
            return 1;
        }

        // otherwise set bit and tell others not to set there own
        atomic_or(freed_slots + (pos_idx / 64), ((1UL) << (pos_idx % 64)));
        return 0;
    }

    uint64_t
    _allocate(const uint32_t start_cpu) {
        for (uint32_t i = 0; i < nvec; ++i) {
            // try allocate
            if (BRANCH_LIKELY(available_slots[i] != FULL_ALLOC_VEC)) {
                const uint32_t idx =
                    restarting_set_idx(available_slots + i, start_cpu);
                if (BRANCH_LIKELY(idx < 64)) {
                    return ((uint64_t)&obj_arr[64 * i + idx]);
                }
                else if (idx == _RSEQ_SET_IDX_MIGRATED) {
                    return FAILED_RSEQ;
                }
            }
        }

        if (freed_slots_lock) {
            // this will be corrected by first free
            return FAILED_VEC_FULL;
        }

        const uint32_t acq_lock_ret =
            restarting_acquire_lock(&freed_slots_lock, start_cpu);
        if (BRANCH_UNLIKELY(acq_lock_ret == _RSEQ_MIGRATED)) {
            return FAILED_RSEQ;
        }
        else if (BRANCH_UNLIKELY(acq_lock_ret == _RSEQ_OTHER_FAILURE)) {
            return FAILED_VEC_FULL;
        }
        // preemptively start invalidating other cores cache line
        PREFETCH_W(freed_slots);


        for (uint32_t i = 0; i < nvec; ++i) {
            if (BRANCH_UNLIKELY(available_slots[i] != FULL_ALLOC_VEC)) {
                const uint32_t idx =
                    restarting_set_idx(available_slots + i, start_cpu);
                if (BRANCH_LIKELY(idx < 64)) {
                    freed_slots_lock = 0;
                    return ((uint64_t)&obj_arr[64 * i + idx]);
                }
                else if (idx == _RSEQ_SET_IDX_MIGRATED) {
                    freed_slots_lock = 0;
                    return FAILED_RSEQ;
                }
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
