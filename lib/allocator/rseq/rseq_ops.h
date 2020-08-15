#ifndef _RSEQ_OPS_H_
#define _RSEQ_OPS_H_

#include <misc/cpp_attributes.h>
#include <misc/macro_helper.h>
#include <stdint.h>
#include <system/sys_info.h>
#include "rseq_asm_defs.h"
#include "rseq_base.h"

//////////////////////////////////////////////////////////////////////
// General unless special case
#define _RSEQ_MIGRATED      2
#define _RSEQ_OTHER_FAILURE 1
#define _RSEQ_SUCCESS       0

/* Man pages
    https://elixir.bootlin.com/linux/latest/source/kernel/rseq.c
    https://lore.kernel.org/patchwork/patch/896892/
*/

static __thread uint64_t _tlv_rand;


#define _RSEQ_SET_IDX_MIGRATED      65
#define _RSEQ_SET_IDX_OTHER_FAILURE 64
// any value [0 - 63] is success

//////////////////////////////////////////////////////////////////////
// The restarting_set_*idx(...) functions are on the SUPER hot path. Any line
// that can be optimized should be

uint64_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_set_idx(uint64_t * const v, const uint32_t start_cpu) {

    // special case where failure must be > 64. Pin to rax to avoid move at
    // return statement (compiler was putting idx in other registers)
    register uint64_t idx asm("rax") = _RSEQ_SET_IDX_MIGRATED;
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
        "mov $" V_TO_STR(_RSEQ_SET_IDX_MIGRATED) ", %[idx]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        : [ idx] "+r" (idx)
        : [ temp_v ] "r" (temp_v),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu)
        : "memory", "cc");
    // clang-format on
    return idx;
}


uint64_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_fast_abort_set_idx(uint64_t * const v,
                                  const uint32_t   start_cpu) {
    // special case where failure must be > 64
    register uint64_t idx asm("rax") = _RSEQ_SET_IDX_MIGRATED;
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
        "mov $" V_TO_STR(_RSEQ_SET_IDX_MIGRATED) ", %[idx]\n\t"

        // start critical section
        "1:\n\t"
        
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
        
        : [ idx] "+r" (idx)
        : [ temp_v ] "r" (temp_v),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu)
        : "memory", "cc");
    // clang-format on

    return idx;
}


uint64_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_set_rand_idx(uint64_t * const v, const uint32_t start_cpu) {
    register uint64_t local_r asm("rcx") = _tlv_rand;

    // special case where failure must be > 64
    register uint64_t idx asm("rax") = _RSEQ_SET_IDX_MIGRATED;
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
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[temp_v]\n\t"
        "movq %[temp_v], %[idx]\n\t"

        // we pin tlv_rand to rcx == cl above
        "rorq %%cl, %[idx]\n\t"
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
        : [ idx] "+r" (idx)
        : [ temp_v ] "r" (temp_v),
          [ local_r ] "r" (local_r),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu)
        : "memory", "cc");
    // clang-format on

    return idx;
}

uint64_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_fast_abort_set_rand_idx(uint64_t * const v,
                                       const uint32_t   start_cpu) {
    register uint64_t local_r asm("rcx") = _tlv_rand;

    // special case where failure must be > 64
    register uint64_t idx asm("rax") = _RSEQ_SET_IDX_MIGRATED;

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
        "mov $" V_TO_STR(_RSEQ_SET_IDX_MIGRATED) ", %[idx]\n\t"

        // start critical section
        "1:\n\t"
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // "cmpl %[start_cpu], %%fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[temp_v]\n\t"
        "movq %[temp_v], %[idx]\n\t"

        // we pin tlv_rand to rcx == cl above
        "rorq %%cl, %[idx]\n\t"
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
        : [ idx] "+r" (idx)
        : [ temp_v ] "r" (temp_v),
          [ local_r ] "r" (local_r),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu)
        : "memory", "cc");
    // clang-format on
    return idx;
}


uint64_t NEVER_INLINE
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

        // we used ret_reclaimed_slots as a time in RSEQ_PREP_CS_DEF
        // so initialize it to failure value before starting critical
        // section
        "movq $-1, %[ret_reclaimed_slots]\n\t"

        // start critical section
        "1:\n\t"
        
        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // "cmpl %[start_cpu], %%fs:__rseq_abi@tpoff+4\n\t"
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
        : [ ret_reclaimed_slots ] "+r"(ret_reclaimed_slots)
        : [ start_cpu ] "g"(start_cpu), 
          [ v ] "g"(v),
          [ free_v ] "g"(free_v)
        : "memory", "cc");
    // clang-format on

    // special case where 0 is actually failure
    return ~ret_reclaimed_slots;
}


uint64_t NEVER_INLINE
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

        // same reason as above
        "movq $-1, %[ret_reclaimed_slots]\n\t"

        // jump to critical section first time
        "jmp 1f\n\t"
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"
        "movq $-1, %[ret_reclaimed_slots]\n\t"
        
        // start critical section
        "1:\n\t"

        // check if migrated        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // "cmpl %[start_cpu], %%fs:__rseq_abi@tpoff+4\n\t"
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
        
        : [ ret_reclaimed_slots ] "+r"(ret_reclaimed_slots)
        : [ start_cpu ] "g"(start_cpu), 
          [ v ] "g"(v),
          [ free_v ] "g"(free_v)
        : "memory", "cc");
    // clang-format on

    // special case where 0 is failure and there is no indication of migrated vs
    // preempted
    return ~ret_reclaimed_slots;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_goto_set_bit(uint64_t * const v,
                                                    const uint64_t   bit,
                                                    const uint32_t start_cpu) {

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

        // carry flag == previous bit (so if 1 we didnt set
        // someone else did)
        "jc %l[no_set]\n\t"
        
        // commit
        "movq %[temp_v], (%[v])\n\t"

        // end critical section
        "2:\n\t" 

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        // no output register due to goto statement
        : 
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ temp_v] "r" (temp_v),
          [ v ] "g"(v)
        : "memory", "cc"
        : abort, no_set);
    // clang-format on
    return _RSEQ_SUCCESS;
no_set:
    return _RSEQ_OTHER_FAILURE;
abort:
    return _RSEQ_MIGRATED;
}

uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_set_bit(uint64_t * const v,
                                               const uint64_t   bit,
                                               const uint32_t   start_cpu) {

    register uint32_t ret asm("rax") = _RSEQ_MIGRATED;
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
        "mov $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ret] "+r" (ret)
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ temp_v] "r" (temp_v),
          [ v ] "g"(v)
        : "memory", "cc");
    // clang-format on

    return ret;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_set_bit_hard(uint64_t * const v,
                                                    const uint64_t   bit,
                                                    const uint32_t start_cpu) {

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
    return _RSEQ_MIGRATED;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_goto_unset_bit(uint64_t * const v,
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
    return _RSEQ_OTHER_FAILURE;
abort:
    return _RSEQ_MIGRATED;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_unset_bit(uint64_t * const v,
                                                 const uint64_t   bit,
                                                 const uint32_t   start_cpu) {

    register uint32_t ret asm("rax") = _RSEQ_MIGRATED;
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
        "mov $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ret] "+r" (ret)
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ temp_v] "r" (temp_v),
          [ v ] "g"(v)
        : "memory", "cc");
    // clang-format on

    return ret;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_unset_bit_hard(uint64_t * const v,
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
    return _RSEQ_MIGRATED;
}

uint64_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_xor(uint64_t * const v,
                                           const uint64_t   new_bit_mask,
                                           const uint32_t   start_cpu) {

    register uint64_t ret asm("rax");
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[ret])
        "movq $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"

        // start critical section
        "1:\n\t"
            
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // prep success return
        "xorq %[ret], %[ret]\n\t"
        
        "xorq %[new_bit_mask], (%[v])\n\t"

        // end critical section
        "2:\n\t" 


        RSEQ_START_ABORT_DEF()
        "movq $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        /* start output labels */
        : [ret] "+r" (ret)
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          [ v ] "g"(v)
          /* end input labels */
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
    return _RSEQ_MIGRATED;
}


// use this or goto version if you want to set bit w.o setting its previous
// value (1UL) << bit will compiler to shlx which is cheap
uint64_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_or(uint64_t * const v,
                                          const uint64_t   new_bit_mask,
                                          const uint32_t   start_cpu) {

    register uint64_t ret asm("rax");
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[ret])
        "movq $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"

        // start critical section
        "1:\n\t"
        
        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // prep success return
        "xorq %[ret], %[ret]\n\t"
        
        "orq %[new_bit_mask], (%[v])\n\t"

        // end critical section
        "2:\n\t" 

        RSEQ_START_ABORT_DEF()
        "movq $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ret] "+r" (ret)
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
    return _RSEQ_MIGRATED;
}

// not is free so use this if you need andn
uint64_t NEVER_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_and(uint64_t * const v,
                                           const uint64_t   new_bit_mask,
                                           const uint32_t   start_cpu) {

    register uint64_t ret asm("rax");
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[ret])


        "movq $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"

        // start critical section
        "1:\n\t"
        
        RSEQ_CMP_CUR_VS_START_CPUS()
        // if migrated goto 2:
        "jnz 2f\n\t"

        // prep success return
        "xorq %[ret], %[ret]\n\t"
        
        "andq %[new_bit_mask], (%[v])\n\t"

        // end critical section
        "2:\n\t"

        RSEQ_START_ABORT_DEF()
        "movq $" V_TO_STR(_RSEQ_MIGRATED) ", %[ret]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ret] "+r" (ret)
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
