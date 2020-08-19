#ifndef _RSEQ_OPS_H_
#define _RSEQ_OPS_H_

#include <misc/cpp_attributes.h>
#include <misc/macro_helper.h>
#include <stdint.h>
#include <system/sys_info.h>
#include "rseq_asm_defs.h"
#include "rseq_base.h"

#define FAST_ABORT
//////////////////////////////////////////////////////////////////////
// General unless special case
#define _RSEQ_MIGRATED      2
#define _RSEQ_OTHER_FAILURE 1
#define _RSEQ_SUCCESS       0

/* Man pages
    https://elixir.bootlin.com/linux/latest/source/kernel/rseq.c
    https://lore.kernel.org/patchwork/patch/896892/
*/

__thread uint64_t _tlv_rand;


#define _RSEQ_SET_IDX_MIGRATED      65
#define _RSEQ_SET_IDX_OTHER_FAILURE 64
// any value [0 - 63] is success

#define _FAILURE_MIGRATED 4097

//////////////////////////////////////////////////////////////////////
// The restarting_set_*idx(...) functions are on the SUPER hot path. Any line
// that can be optimized should be


uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_2level_rand_set_idx(uint64_t * const v1,
                                   const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    // _tlv_rand is a random [0 - 63].
    // Pin to %rcx so its ready in %cl for ror
    register uint64_t local_r asm("rcx") = _tlv_rand;

    // Pin for return so compiler doesnt fuck up
    register uint64_t idx asm("rax");

    // some temps I trust the compiler to allocate smartly
    uint64_t idx_v1, temp_v1, temp_v2;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()

        // any 64 bit register will do
        RSEQ_PREP_CS_DEF(%[temp_v1])

        // return value if thread migrated
        "mov $ " V_TO_STR(_FAILURE_MIGRATED) ", %[idx]\n\t"

#ifdef FAST_ABORT
        // skip abort first time
        "jmp 1f\n\t"
        
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"
        "mov $" V_TO_STR(_FAILURE_MIGRATED) ", %[idx]\n\t"
#endif

        
        // start critical section
        "1:\n\t"
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v1]), %[temp_v1]\n\t"
        

        // start loop: while(temp_v1 != -1)
        "5:\n\t"
                
        // idx = ~temp_v
        "movq %[temp_v1], %[idx]\n\t"

        // if (%[v1]) is full leave.
        // This branch is VERY unexpected.
        
        // The reason we can't do this after notq %[idx] is because
        // 0 is a valid idx to return whereas -1 is not
        // (also why setting idx before the comparison)
        "cmpq $-1, %[idx]\n\t"
        "jz 2f\n\t"

        // rotate randomly to spread first bit
        "rorq %%cl, %[idx]\n\t"
        "notq %[idx]\n\t"
        
        // idx_v1 = tzcnt(idx) (find first one)
        "tzcntq %[idx], %[idx_v1]\n\t"

        // get actual v1 idx
        "addq %[local_r], %[idx_v1]\n\t"
        "and $63, %[idx_v1]\n\t"

        // temp_v2 = v[idx_v1 + 1]
        "movq 8(%[v1], %[idx_v1], 8), %[temp_v2]\n\t"

        // test if temp_v2 is full
        "cmpq $-1, %[temp_v2]\n\t"
        "jz 7f\n\t" // 7f is btsq %[idx_outer], %[temp_v1], jmp 5b
                
        // idx = ~temp_v2
        "movq %[temp_v2], %[idx]\n\t"
        "notq %[idx]\n\t"
        // could replace the cmpq $-1, %[temp_v2], jz above with
        // testq %[idx], %[idx], jz here

        // idx = tzcnt(idx)
        "tzcntq %[idx], %[idx]\n\t"

        // temp_v2 |= 1 << idx
        "btsq %[idx], %[temp_v2]\n\t"
        "jmp 9f\n\t"

        "7:\n\t"
        "btsq %[idx_v1], %[temp_v1]\n\t"

        // this is a completely valid state to be migrated out after
        // (all we have really done is cleaned up v1 vector a bit)
        // because we can be migrated out here we don't check/set if
        // temp_v2 is full as that could lead to invalid state in v1
        // again it may be better to move this to 9: so that we can reduce
        // writes to (%[v1])
        "movq %[temp_v1], (%[v1])\n\t"
        
        // this is } in while loop starting at 5:
        "jmp 5b\n\t"

        "9:\n\t"
        "btsq %[idx], %[temp_v2]\n\t"
               
        // prepare success return
        "salq $6, %[idx_v1]\n\t"
        "addq %[idx_v1], %[idx]\n\t"
        
        // commit
        "movq %[temp_v2], 8(%[v1], %[idx_v1], 8)\n\t"

        // end critical section
        "2:\n\t"

#ifndef FAST_ABORT        
        RSEQ_START_ABORT_DEF()
        // given that the critical section is fairly involved
        // it may be worth it to put this in the same code section
        // as critical section for faster aborts
        "mov $" V_TO_STR(_FAILURE_MIGRATED) ", %[idx]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
#endif
        : [ idx] "=&r" (idx),
          [ idx_v1 ] "=&r" (idx_v1),
          [ temp_v2 ] "=&r" (temp_v2),
          [ temp_v1 ] "=&r" (temp_v1)
        : [ local_r ] "r" (local_r),
          [ v1 ] "g" (v1),
          [ start_cpu] "g" (start_cpu)
        : "memory", "cc");

    return idx;
}


#define _FAILURE_MIGRATED 4097
uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_2level_set_idx(uint64_t * const v1, const uint32_t start_cpu) {
    // return [0 - 4095] -> success (that is the index)
    // return [4097] -> failure the thread migrated
    // return [-1] -> failure the bit vector is full

    
#pragma GCC diagnostic ignored "-Wuninitialized"
    // Pin for return so compiler doesnt fuck up
    uint64_t idx;

    // some temps I trust the compiler to allocate smartly
    uint64_t idx_v1, temp_v1, temp_v2;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()

        // any register will do
        RSEQ_PREP_CS_DEF(%[temp_v1])

        "mov $" V_TO_STR(_FAILURE_MIGRATED) ", %[idx]\n\t"

#ifdef FAST_ABORT
        // skip abort first time
        "jmp 1f\n\t"
        
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"
        "mov $" V_TO_STR(_FAILURE_MIGRATED) ", %[idx]\n\t"
#endif
        
        // start critical section
        "1:\n\t"
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v1]), %[temp_v1]\n\t"

        // start loop: while(temp_v1 != -1)
        "5:\n\t"
                
        // idx = ~temp_v
        "movq %[temp_v1], %[idx]\n\t"

        // if (%[v1]) is full leave.
        // This branch is VERY unexpected.
        
        // The reason we can't do this after notq %[idx] is because
        // 0 is a valid idx to return whereas -1 is not
        // (also why setting idx before the comparison)
        "cmpq $-1, %[idx]\n\t"
        "jz 2f\n\t"
        
        "notq %[idx]\n\t"
        
        // idx_v1 = tzcnt(idx) (find first one)
        "tzcntq %[idx], %[idx_v1]\n\t"

        // temp_v2 = v[idx_v1 + 1]
        "movq 8(%[v1], %[idx_v1], 8), %[temp_v2]\n\t"

        // test if temp_v2 is full
        "cmpq $-1, %[temp_v2]\n\t"
        "jz 7f\n\t" // 7f is btsq %[idx_outer], %[temp_v1], jmp 5b
        
        // idx = ~temp_v2
        "movq %[temp_v2], %[idx]\n\t"
        "notq %[idx]\n\t"
        // could replace the cmpq $-1, %[temp_v2], jz above with
        // testq %[idx], %[idx], jz here

        // idx = tzcnt(idx)
        "tzcntq %[idx], %[idx]\n\t"

        // temp_v2 |= 1 << idx
        "btsq %[idx], %[temp_v2]\n\t"
        "jmp 9f\n\t"

        "7:\n\t"
        "btsq %[idx_v1], %[temp_v1]\n\t"
        
        // this is a completely valid state to be migrated out after
        // (all we have really done is cleaned up v1 vector a bit)
        // because we can be migrated out here we don't check/set if
        // temp_v2 is full as that could lead to invalid state in v1
        "movq %[temp_v1], (%[v1])\n\t"

        // this is } in while loop starting at 5:
        "jmp 5b\n\t"

        "9:\n\t"
        "btsq %[idx], %[temp_v2]\n\t"
               
        // prepare success return
        "salq $3, %[idx_v1]\n\t"
        "leaq (%[idx],%[idx_v1],8), %[idx]\n\t"
        
        // commit
        "movq %[temp_v2], 8(%[v1], %[idx_v1], )\n\t"

        // end critical section
        "2:\n\t"

#ifndef FAST_ABORT
          RSEQ_START_ABORT_DEF()
        // given that the critical section is fairly involved
        // it may be worth it to put this in the same code section
        // as critical section for faster aborts
        "mov $" V_TO_STR(_FAILURE_MIGRATED) ", %[idx]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
#endif

        : [ idx] "=&r" (idx),
          [ idx_v1 ] "=&r" (idx_v1),
          [ temp_v2 ] "=&r" (temp_v2),
          [ temp_v1 ] "=&r" (temp_v1)
        : [ v1 ] "g" (v1),
          [ start_cpu] "g" (start_cpu)
        : "memory", "cc");

    return idx;
}



uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_set_idx(uint64_t * const v, const uint32_t start_cpu) {

    // special case where failure must be > 64. Pin to rax to avoid move at
    // return statement (compiler was putting idx in other registers)
    register uint64_t idx asm("rax");
#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"
        
        "movq $" V_TO_STR(_RSEQ_SET_IDX_MIGRATED) ", %[idx]\n\t"
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[temp_v]\n\t"
        
        // idx = ~temp_v
        "movq %[temp_v], %[idx]\n\t"
        "notq %[idx]\n\t"

        // idx = tzcnt(idx) (find first one)
        "tzcntq %[idx], %[idx]\n\t"
        // carry flag is set if src == 0 i.e output == 64
        "jc 2f\n"
        
        // temp_v |= ((1UL) << idx)
        "btsq %[idx], %[temp_v]\n\t"
        
        // *v = temp_v
        "movq %[temp_v], (%[v])\n\t"

        // end critical section
        "2:\n\t"

        
        RSEQ_START_ABORT_DEF()
        // abort go back to start of cs (that will compare cpu)
        // if migrated jmp 2: which which ret idx == _RSEQ_SET_IDX_MIGRATED
        // else retry (we were just preempted)
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        : [ idx] "=&r" (idx),
          [ temp_v ] "=&r" (temp_v)
        : [ v] "g" (v),
          [ start_cpu] "g" (start_cpu)
        : "memory", "cc");
    // clang-format on
    return idx;
}


uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_fast_abort_set_idx(uint64_t * const v,
                                  const uint32_t   start_cpu) {
    // special case where failure must be > 64
    register uint64_t idx asm("rax");
#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic pop

    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // skip abort definition first time
        "jmp 1f\n\t"

        // abort definition in same section as critical section
        // (so it aborts are likely will be handled faster
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"

        // start critical section
        "1:\n\t"

        "mov $" V_TO_STR(_RSEQ_SET_IDX_MIGRATED) ", %[idx]\n\t"
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[temp_v]\n\t"

        // idx = ~temp_v
        "movq %[temp_v], %[idx]\n\t"
        "notq %[idx]\n\t"

        // idx = tzcnt(idx) (find first one)
        "tzcntq %[idx], %[idx]\n\t"
        // carry flag is set if src == 0 i.e output == 64
        "jc 2f\n"
        
        // temp_v |= ((1UL) << idx)
        "btsq %[idx], %[temp_v]\n\t"
        
        // *v = temp_v
        "movq %[temp_v], (%[v])\n\t"

        // end critical section
        "2:\n\t"
        
        : [ idx] "=&r" (idx),
          [ temp_v ] "=&r" (temp_v)
        : [ v] "g" (v),
          [ start_cpu] "g" (start_cpu)
        : "memory", "cc");
    // clang-format on

    return idx;
}


uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_set_rand_idx(uint64_t * const v, const uint32_t start_cpu) {
    register uint64_t local_r asm("rcx") = _tlv_rand;

    // special case where failure must be > 64
    register uint64_t idx asm("rax");
#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"
        
        "mov $" V_TO_STR(_RSEQ_SET_IDX_MIGRATED) ", %[idx]\n\t"
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[temp_v]\n\t"
        "movq %[temp_v], %[idx]\n\t"

        // we pin tlv_rand to rcx == cl above
        "rolq %%cl, %[idx]\n\t"
        "notq %[idx]\n\t"

        // idx = tzcnt(idx) (find first one)
        "tzcntq %[idx], %[idx]\n\t"
        // carry flag is set if src == 0 i.e output == 64
        "jc 2f\n"

        // restore to original idx
        "addq %[local_r], %[idx]\n\t"
        "and $63, %[idx]\n\t"
        
        // temp_v |= ((1UL) << idx)
        "btsq %[idx], %[temp_v]\n\t"
        
        // *v = temp_v
        "movq %[temp_v], (%[v])\n\t"

        // end critical section
        "2:\n\t"
        
        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        : [ idx] "=&r" (idx),
          [ temp_v ] "=&r" (temp_v)
        : [ local_r ] "r" (local_r),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu)
        : "memory", "cc");
    // clang-format on

    return idx;
}

uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_fast_abort_set_rand_idx(uint64_t * const v,
                                       const uint32_t   start_cpu) {
    register uint64_t local_r asm("rcx") = _tlv_rand;

    // special case where failure must be > 64
    register uint64_t idx asm("rax");

#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // skip abort first time
        "jmp 1f\n\t"
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"

        // start critical section
        "1:\n\t"

        "mov $" V_TO_STR(_RSEQ_SET_IDX_MIGRATED) ", %[idx]\n\t"
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[temp_v]\n\t"
        "movq %[temp_v], %[idx]\n\t"

        // we pin tlv_rand to rcx == cl above
        "rolq %%cl, %[idx]\n\t"
        "notq %[idx]\n\t"

        // idx = tzcnt(idx) (find first one)
        "tzcntq %[idx], %[idx]\n\t"
        // carry flag is set if src == 0 i.e output == 64
        "jc 2f\n"

        // restore to original idx
        "addq %[local_r], %[idx]\n\t"
        "and $63, %[idx]\n\t"
        
        // temp_v |= ((1UL) << idx)
        "btsq %[idx], %[temp_v]\n\t"
        
        // *v = temp_v
        "movq %[temp_v], (%[v])\n\t"

        // end critical section
        "2:\n\t"
        
        RSEQ_START_ABORT_DEF()
        "mov $" V_TO_STR(_RSEQ_SET_IDX_MIGRATED) ", %[idx]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        : [ idx] "=&r" (idx),
          [ temp_v ] "=&r" (temp_v)
        : [ local_r ] "r" (local_r),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu)
        : "memory", "cc");
    // clang-format on
    return idx;
}


uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_reclaim_free_slabs(uint64_t * const v,
                                  uint64_t * const free_v,
                                  const uint32_t   start_cpu) {
    register uint64_t ret_reclaimed_slots asm("rax");
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[ret_reclaimed_slots])

        // start critical section
        "1:\n\t"

        "movq $-1, %[ret_reclaimed_slots]\n\t"
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // get current free vec
        "movq (%[free_v]), %[ret_reclaimed_slots]\n\t"
        // invert bits because avail vec uses 0s to mark free slots
        "notq %[ret_reclaimed_slots]\n\t"

        // and -> force 0 all free slots (rest unaffected)
        "andq %[ret_reclaimed_slots], (%[v])\n\t"

        // end critical section
        "2:\n\t"
        
        RSEQ_START_ABORT_DEF()
        "movq $-1, %[ret_reclaimed_slots]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        : [ ret_reclaimed_slots ] "=&r"(ret_reclaimed_slots)
        : [ start_cpu ] "g"(start_cpu), 
          [ v ] "g"(v),
          [ free_v ] "g"(free_v)
        : "memory", "cc");
    // clang-format on

    // special case where 0 is actually failure
    return ~ret_reclaimed_slots;
}


uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_fast_abort_reclaim_free_slabs(uint64_t * const v,
                                             uint64_t * const free_v,
                                             const uint32_t   start_cpu) {
    register uint64_t ret_reclaimed_slots asm("rax");
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[ret_reclaimed_slots])



        // jump to critical section first time
        "jmp 1f\n\t"
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"
        "movq $-1, %[ret_reclaimed_slots]\n\t"
        
        // start critical section
        "1:\n\t"

        "movq $-1, %[ret_reclaimed_slots]\n\t"

        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // get current free vec
        "movq (%[free_v]), %[ret_reclaimed_slots]\n\t"

        // invert bits so and will unset those in v
        "notq %[ret_reclaimed_slots]\n\t"

        // andq and return
        "andq %[ret_reclaimed_slots], (%[v])\n\t"

        // end critical section
        "2:\n\t"
        
        : [ ret_reclaimed_slots ] "=&r"(ret_reclaimed_slots)
        : [ start_cpu ] "g"(start_cpu), 
          [ v ] "g"(v),
          [ free_v ] "g"(free_v)         
        : "memory", "cc");
    // clang-format on

    // special case where 0 is failure and there is no indication of migrated vs
    // preempted
    return ~ret_reclaimed_slots;
}


uint32_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_set_bit(uint64_t * const v,
                                               const uint64_t   bit,
                                               const uint32_t   start_cpu) {


#pragma GCC diagnostic ignored "-Wuninitialized"
    register uint32_t ret asm("rax");
    uint64_t          temp_v;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"

        "mov $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // temp_v = *v;
        "movq (%[v]), %[temp_v]\n\t"

        // prep unsuccess return
        "mov $" V_TO_STR(_RSEQ_OTHER_FAILURE) ", %[ret]\n\t"

        // temp_v |= 1 << bit
        "btsq %[bit], %[temp_v]\n\t"

        // jump if previous bit was 1
        "jc 2f\n\t"

        // prep success return value
        "xorl %[ret], %[ret]\n\t"
        
        // commit 
        "movq %[temp_v], (%[v])\n\t"
        
        "2:\n\t"
        // end critical section

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ret] "=&r" (ret),
          [ temp_v] "=&r" (temp_v)
        : [ bit ] "r"(bit),
          [ start_cpu ] "g"(start_cpu),
          [ v ] "g"(v)
        : "memory", "cc");
    // clang-format on

    return ret;
}



uint32_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_goto_set_bit_bts(uint64_t * const v,
                                  const uint64_t   bit,
                                  const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push
    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        // temp_v = *v;
        "movq (%[v]), %[temp_v]\n\t"

        // temp_v &= ~(1 << bit)
        "btsq %[bit], %[temp_v]\n\t"

        // jump if previos bit was not 1
        "jnc %l[no_set]\n\t"

        //commit
        "movq %[temp_v], (%[v])\n\t"

        "2:\n\t"  
        // end critical section

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : 
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r" (bit),
          [ temp_v] "r" (temp_v),
          [ v ] "g"(v)
        : "memory", "cc"
        : abort, no_set);
    // clang-format on

    return _RSEQ_SUCCESS;
no_set:
    __attribute__((cold));
    return _RSEQ_OTHER_FAILURE;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


uint32_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_set_bit_hard_bts_jc(uint64_t * const v,
                                   const uint64_t   bit,
                                   const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        // temp_v = *v;
        "movq (%[v]), %[temp_v]\n\t"

        // temp_v |= 1 << bit
        "btsq %[bit], %[temp_v]\n\t"
        "jc 2f\n\t"
        
        // commit 
        "movq %[temp_v], (%[v])\n\t"
        
        "2:\n\t"
        // end critical section

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : 
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ temp_v] "r" (temp_v),
          [ v ] "g"(v)
        : "memory", "cc"
        : abort);
    // clang-format on

    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}

uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_set_bit_hard_bts(uint64_t * const v,
                                const uint64_t   bit,
                                const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        // temp_v = *v;
        "movq (%[v]), %[temp_v]\n\t"

        // temp_v |= 1 << bit
        "btsq %[bit], %[temp_v]\n\t"
        
        // commit 
        "movq %[temp_v], (%[v])\n\t"
        
        "2:\n\t"
        // end critical section

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : 
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ temp_v] "r" (temp_v),
          [ v ] "g"(v)
        : "memory", "cc"
        : abort);
    // clang-format on

    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}

uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_set_bit_hard_or(uint64_t * const v,
                                const uint64_t   bit,
                                const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // prep to avoid repeating this on preemption
        "movq $1, %[temp_v]\n\t"
        "shlx %[bit], %[temp_v], %[temp_v]\n\t"
        
        // start critical section
        "1:\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz %l[abort]\n\t"
        
        // commit 
        "orq %[temp_v], (%[v])\n\t"
        
        "2:\n\t"
        // end critical section

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : 
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ temp_v] "r" (temp_v),
          [ v ] "g"(v)
        : "memory", "cc"
        : abort);
    // clang-format on

    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_set_bit_hard_ret(uint64_t * const v,
                                const uint64_t   bit,
                                const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    register uint32_t ret asm("rax");
    uint64_t          temp_v;
#pragma GCC diagnostic push


    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"

        "mov $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // temp_v = *v;
        "movq (%[v]), %[temp_v]\n\t"

        "xorl %[ret], %[ret]\n\t"

        "testq %[temp_v], %[temp_v]\n\t"
        "setz %%al\n\t"

        // temp_v |= 1 << bit
        "btsq %[bit], %[temp_v]\n\t"
        
        // commit 
        "movq %[temp_v], (%[v])\n\t"
        
        "2:\n\t"
        // end critical section

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ ret ] "=&r" (ret),
          [ temp_v ] "=&r" (temp_v)
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ v ] "g"(v)
        : "memory", "cc");
    // clang-format on

    return ret;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_goto_unset_bit_btr(uint64_t * const v,
                                  const uint64_t   bit,
                                  const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push
    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        // temp_v = *v;
        "movq (%[v]), %[temp_v]\n\t"

        // temp_v &= ~(1 << bit)
        "btrq %[bit], %[temp_v]\n\t"

        // jump if previos bit was not 1
        "jnc %l[no_unset]\n\t"

        //commit
        "movq %[temp_v], (%[v])\n\t"

        "2:\n\t"  
        // end critical section

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : 
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r" (bit),
          [ temp_v] "r" (temp_v),
          [ v ] "g"(v)
        : "memory", "cc"
        : abort, no_unset);
    // clang-format on

    return _RSEQ_SUCCESS;
no_unset:
    __attribute__((cold));
    return _RSEQ_OTHER_FAILURE;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_unset_bit_btr(uint64_t * const v,
                                                     const uint64_t   bit,
                                                     const uint32_t start_cpu) {


#pragma GCC diagnostic ignored "-Wuninitialized"
    register uint32_t ret asm("rax");
    uint64_t          temp_v;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"
        
        "mov $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // temp_v = *v;
        "movq (%[v]), %[temp_v]\n\t"

        // prep unsuccess return
        "mov $" V_TO_STR(_RSEQ_OTHER_FAILURE) ", %[ret]\n\t"
        
        // temp_v |= 1 << bit
        "btrq %[bit], %[temp_v]\n\t"
        "jnc 2f\n\t"

        // prep success return
        "xorl %[ret], %[ret]\n\t"
        
        // commit 
        "movq %[temp_v], (%[v])\n\t"

        // end critical section
        "2:\n\t"  

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ret] "=&r" (ret),
          [ temp_v] "=&r" (temp_v)
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ v ] "g"(v)
        : "memory", "cc");
    // clang-format on

    return ret;
}


uint32_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_unset_bit_hard_btr_jnc(uint64_t * const v,
                                      const uint64_t   bit,
                                      const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        // temp_v = *v;
        "movq (%[v]), %[temp_v]\n\t"

        // temp_v &= ~(1 << bit)
        "btrq %[bit], %[temp_v]\n\t"
        // worth it so skip mov instruction
        "jnc 2f\n"
        
        // commit 
        "movq %[temp_v], (%[v])\n\t"

        // end critical section
        "2:\n\t"  

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        :
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ temp_v] "r" (temp_v),
          [ v ] "g"(v)
        : "memory", "cc"
        : abort);
    // clang-format on

    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}

uint32_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_unset_bit_hard_btr_jnc_tt(uint64_t * const v,
                                      const uint64_t   bit,
                                      const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    register uint32_t idx asm("rax");
    uint64_t temp_v;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile (
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"
        
        "mov $ " V_TO_STR(_RSEQ_MIGRATED) ", %[idx]\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // temp_v = *v;
        "movq (%[v]), %[temp_v]\n\t"

        "xor %[idx], %[idx]\n\t"

        // temp_v &= ~(1 << bit)
        "btrq %[bit], %[temp_v]\n\t"
        // worth it so skip mov instruction
        "jnc 2f\n"
        
        // commit 
        "movq %[temp_v], (%[v])\n\t"

        // end critical section
        "2:\n\t"  

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ idx] "=&r" (idx),
          [ temp_v] "=&r" (temp_v)
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ v ] "g"(v)
        : "memory", "cc");
    // clang-format on

    return idx;
}

uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_unset_bit_hard_btr(uint64_t * const v,
                                  const uint64_t   bit,
                                  const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        // temp_v = *v;
        "movq (%[v]), %[temp_v]\n\t"

        // temp_v |= 1 << bit
        "btrq %[bit], %[temp_v]\n\t"
        
        // commit 
        "movq %[temp_v], (%[v])\n\t"

        // end critical section
        "2:\n\t"  

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        :
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ temp_v] "r" (temp_v),
          [ v ] "g"(v)
        : "memory", "cc"
        : abort);
    // clang-format on

    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


uint64_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_unset_bit_hard_ret(uint64_t * const v,
                                  const uint64_t   bit,
                                  const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    register uint64_t temp_v asm("rax");
#pragma GCC diagnostic push

    // clang-format off
    asm volatile (
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_v])

        // start critical section
        "1:\n\t"

        // in this case 0 return means migrated
        "xorq %[temp_v], %[temp_v]\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // temp_v = *v;
        "movq (%[v]), %[temp_v]\n\t"

        // temp_v ^= 1 << bit
        "btrq %[bit], %[temp_v]\n\t"
        
        // commit 
        "movq %[temp_v], (%[v])\n\t"

        // end critical section
        "2:\n\t"  

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ temp_v] "=&r" (temp_v)
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ v ] "g"(v)
        : "memory", "cc");

    // clang-format on

    return temp_v;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_unset_bit_hard_rol(uint64_t * const v,
                                  const uint64_t   bit,
                                  const uint32_t   start_cpu) {


    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%%rcx)

        // start critical section
        "1:\n\t"
        
        // check if migrated
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        "movq %[bit], %%rcx\n\t"
        "movq $-2, %[bit]\n\t"
        "rolq %%cl, %[bit]\n\t"
        "andq %[bit], (%[v])\n\t"

        // end critical section
        "2:\n\t"  

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        :
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ v ] "g"(v)
        : "memory", "cc", "rcx"
        : abort);
    // clang-format on

    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_goto_xor(uint64_t * const v,
                                                const uint64_t   new_bit_mask,
                                                const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_r;
#pragma GCC diagnostic push
    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_r])

        // start critical section
        "1:\n\t"
        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        "xorq %[new_bit_mask], (%[v])\n\t"

        // end critical section
        "2:\n\t" 

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        :
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          [ v ] "g"(v),
          [ temp_r] "r" (temp_r)
        : "memory", "cc"
        : abort);

    // clang-format on
    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}

uint64_t NEVER_INLINE
                       ALIGN_ATTR(CACHE_LINE_SIZE) restarting_xor(uint64_t * const v,
                                           const uint64_t   new_bit_mask,
                                           const uint32_t   start_cpu) {
#pragma GCC diagnostic ignored "-Wuninitialized"
    register uint64_t ret asm("rax");
#pragma GCC diagnostic push
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[ret])

        // start critical section
        "1:\n\t"

        "movq $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
            
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // prep success return
        "xorq %[ret], %[ret]\n\t"
        
        "xorq %[new_bit_mask], (%[v])\n\t"

        // end critical section
        "2:\n\t" 


        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ret] "=&r" (ret)
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          [ v ] "g"(v)
        : "memory", "cc");
    // clang-format on

    return ret;
}


uint32_t NEVER_INLINE
                       ALIGN_ATTR(CACHE_LINE_SIZE) restarting_goto_or(uint64_t * const v,
                                               const uint64_t   new_bit_mask,
                                               const uint32_t   start_cpu) {
#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_r;
#pragma GCC diagnostic push
    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_r])

        // start critical section
        "1:\n\t"
        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        "orq %[new_bit_mask], (%[v])\n\t"

        // end critical section
        "2:\n\t"  


        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        :
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          [ v ] "g"(v),
          [ temp_r] "r" (temp_r)
          /* end input labels */
        : "memory", "cc"
        : abort);
    // clang-format on
    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


// use this or goto version if you want to set bit w.o setting its previous
// value (1UL) << bit will compiler to shlx which is cheap
uint64_t NEVER_INLINE
                       ALIGN_ATTR(CACHE_LINE_SIZE) restarting_or(uint64_t * const v,
                                          const uint64_t   new_bit_mask,
                                          const uint32_t   start_cpu) {
#pragma GCC diagnostic ignored "-Wuninitialized"
    register uint64_t ret asm("rax");
#pragma GCC diagnostic push
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[ret])


        // start critical section
        "1:\n\t"

        "movq $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // prep success return
        "xorq %[ret], %[ret]\n\t"
        
        "orq %[new_bit_mask], (%[v])\n\t"

        // end critical section
        "2:\n\t" 

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ret] "=&r" (ret)
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          [ v ] "g"(v)
        : "memory", "cc");

    // clang-format on
    return ret;
}

uint32_t NEVER_INLINE
                       ALIGN_ATTR(CACHE_LINE_SIZE) restarting_goto_and(uint64_t * const v,
                                                const uint64_t   new_bit_mask,
                                                const uint32_t   start_cpu) {
#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_r;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_r])

        // start critical section
        "1:\n\t"
        
        RSEQ_CMP_CUR_VS_START_CPUS()
            // if migrated goto 2:
        "jnz %l[abort]\n\t"

        "andq %[new_bit_mask], (%[v])\n\t"

        // end critical section
        "2:\n\t" 

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        :
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          [ v ] "g"(v),
          [ temp_r] "r" (temp_r)
        : "memory", "cc"
        : abort);

    // clang-format on
    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}

// not is free so use this if you need andn
uint64_t NEVER_INLINE
                       ALIGN_ATTR(CACHE_LINE_SIZE) restarting_and(uint64_t * const v,
                                           const uint64_t   new_bit_mask,
                                           const uint32_t   start_cpu) {
#pragma GCC diagnostic ignored "-Wuninitialized"
    register uint64_t ret asm("rax");
#pragma GCC diagnostic push
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[ret])

        // start critical section
        "1:\n\t"

        "movq $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // prep success return
        "xorq %[ret], %[ret]\n\t"
        
        "andq %[new_bit_mask], (%[v])\n\t"

        // end critical section
        "2:\n\t"

        RSEQ_START_ABORT_DEF()

        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ret] "=&r" (ret)
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          [ v ] "g"(v)
        : "memory", "cc");

    // clang-format on
    return ret;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_goto_acquire_lock(uint64_t * const lock_ptr,
                                 const uint32_t   start_cpu) {
#pragma GCC diagnostic ignored "-Wuninitialized"
    uint64_t temp_r;
#pragma GCC diagnostic push

    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[temp_r])

        // start critical section
        "1:\n\t"
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        // if 0 not locked
        "cmpq $0, (%[lock_ptr])\n\t"
        // if not 0 was locked return as much
        "jnz %l[already_locked]\n\t"

        // otherwise lock and fall through to return success
        "movq $1, (%[lock_ptr])\n\t"

        // end critical section
        "2:\n\t"  

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        :
        : [ start_cpu ] "g"(start_cpu),
          [ lock_ptr ] "g"(lock_ptr),
          [ temp_r] "r" (temp_r)
        : "memory", "cc"
        : abort, already_locked);

    // clang-format on
    return _RSEQ_SUCCESS;
already_locked:
    return _RSEQ_OTHER_FAILURE;
abort:
    return _RSEQ_MIGRATED;
}


uint64_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_acquire_lock(uint64_t * const lock_ptr,
                                                    const uint32_t start_cpu) {

    register uint64_t ret asm("rax");

    // clang-format off
    asm volatile (
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[ret])
        "movq $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"

        // start critical section
        "1:\n\t"
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // prep unsuccesful return
        "mov $" V_TO_STR(_RSEQ_OTHER_FAILURE) ", %[ret]\n\t"

        // check if locked
        "cmpq $0, (%[lock_ptr])\n\t"
        // skip 
        "jnz 2f\n\t"

        // success return
        "xorq %[ret], %[ret]\n\t"
        
        // set lock
        "movq $1, (%[lock_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "movq $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ret] "+r" (ret)
        : [ start_cpu ] "g"(start_cpu),
          [ lock_ptr ] "g"(lock_ptr)
        : "memory", "cc");
    // clang-format on

    return ret;
}


#endif
