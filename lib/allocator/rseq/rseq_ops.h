#ifndef _RSEQ_OPS_H_
#define _RSEQ_OPS_H_

#include <misc/cpp_attributes.h>
#include <stdint.h>
#include "rseq_asm_defs.h"
#include "rseq_base.h"

#define _RSEQ_MIGRATED     2
#define _RSEQ_OTHER_FAILRE 1
#define _RSEQ_SUCCESS      0

/* Man pages
    https://elixir.bootlin.com/linux/latest/source/kernel/rseq.c
    https://lore.kernel.org/patchwork/patch/896892/
*/

static __thread uint64_t _tlv_rand;

uint64_t NEVER_INLINE
ALIGN_ATTR(64)
    restarting_set_idx(uint64_t * const v, const uint32_t start_cpu) {
    // special case where failure must be > 64
    register uint64_t idx asm("rax") = 65;
    uint64_t          temp_v;

    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[temp_v]\n\t"
        "movq %[temp_v], %[idx]\n\t"
        "notq %[idx]\n\t"

        // idx = tzcnt(~*v) (find first zero)
        "tzcntq %[idx], %[idx]\n\t"
        // carry flag is set if src == 0 i.e output == 64
        "jc 2f\n"
        
        // temp_v |= ((1UL) << idx)
        "btsq %[idx], %[temp_v]\n\t"
        
        // *v = temp_v
        "movq %[temp_v], (%[v])\n\t"
        "2:\n\t"
        RSEQ_START_ABORT_DEF()
        // abort go back to start of cs (that will compare cpu)
        // if migrated jmp 5:, else retry (we were just preempted)
        "mov $65, %[idx]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        : [ idx] "+r" (idx)
        : [ temp_v ] "r" (temp_v),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu),
          [ rseq_abi] "g" (&__rseq_abi)
        : "memory", "cc");
    // clang-format on
    return idx;
}


uint64_t NEVER_INLINE
ALIGN_ATTR(64) restarting_fast_abort_set_idx(uint64_t * const v,
                                             const uint32_t   start_cpu) {
    // special case where failure must be > 64
    register uint64_t idx asm("rax") = 65;
    uint64_t          temp_v;

    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        "leaq 3b (%%rip), %fs:__rseq_abi@tpoff+8\n\t"
    "1:\n\t"
        "jmp 1f\n\t"
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"
        "mov $65, %[idx]\n\t"

        // start critical section
        "1:\n\t"
        
        // check if migrated        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[temp_v]\n\t"
        "movq %[temp_v], %[idx]\n\t"
        "notq %[idx]\n\t"

        // idx = tzcnt(~*v) (find first zero)
        "tzcntq %[idx], %[idx]\n\t"
        // carry flag is set if src == 0 i.e output == 64
        "jc 2f\n"
        
        // temp_v |= ((1UL) << idx)
        "btsq %[idx], %[temp_v]\n\t"
        
        // *v = temp_v
        "movq %[temp_v], (%[v])\n\t"
        "2:\n\t"
        : [ idx] "+r" (idx)
        : [ temp_v ] "r" (temp_v),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu),
          [ rseq_abi] "g" (&__rseq_abi)
        : "memory", "cc");
    // clang-format on

    return idx;
}


uint64_t NEVER_INLINE
ALIGN_ATTR(64)
    restarting_set_rand_idx(uint64_t * const v, const uint32_t start_cpu) {
    register uint64_t local_r asm("rcx") = _tlv_rand;

    // special case where failure must be > 64
    register uint64_t idx asm("rax") = 65;
    uint64_t          temp_v;
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[temp_v]\n\t"
        "movq %[temp_v], %[idx]\n\t"

        // we pin tlv_rand to rcx == cl above
        "rorq %%cl, %[idx]\n\t"
        "notq %[idx]\n\t"

        // idx = tzcnt(~*v) (find first zero)
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
        "2:\n\t"
        RSEQ_START_ABORT_DEF()
        // abort go back to start of cs (that will compare cpu)
        // if migrated jmp 5:, else retry (we were just preempted)
        "mov $65, %[idx]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        : [ idx] "+r" (idx)
        : [ temp_v ] "r" (temp_v),
          [ local_r ] "g" (local_r),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu),
          [ rseq_abi] "g" (&__rseq_abi)
        : "memory", "cc");
    // clang-format on

    return idx;
}

uint64_t NEVER_INLINE
ALIGN_ATTR(64) restarting_fast_abort_set_rand_idx(uint64_t * const v,
                                                  const uint32_t   start_cpu) {
    register uint64_t local_r asm("rcx") = _tlv_rand;

    // special case where failure must be > 64
    register uint64_t idx asm("rax") = 65;
    uint64_t          temp_v;
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        "leaq 3b (%%rip), %fs:__rseq_abi@tpoff+8\n\t"
    "1:\n\t"
        "jmp 1f\n\t"
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"
        "mov $65, %[idx]\n\t"

        // start critical section
        "1:\n\t"
        // check if migrated        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[temp_v]\n\t"
        "movq %[temp_v], %[idx]\n\t"

        // we pin tlv_rand to rcx == cl above
        "rorq %%cl, %[idx]\n\t"
        "notq %[idx]\n\t"

        // idx = tzcnt(~*v) (find first zero)
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
        "2:\n\t"
        RSEQ_START_ABORT_DEF()
        // abort go back to start of cs (that will compare cpu)
        // if migrated jmp 5:, else retry (we were just preempted)
        
        // worth noting its possible to put this in same section as cs.
        // this will make for faster aborts but is ultimately more code
        // to get through for the fast path
        "mov $65, %[idx]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        : [ idx] "+r" (idx)
        : [ temp_v ] "r" (temp_v),
          [ local_r ] "g" (local_r),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu),
          [ rseq_abi] "g" (&__rseq_abi)
        : "memory", "cc");
    // clang-format on
    return idx;
}


uint64_t NEVER_INLINE
ALIGN_ATTR(64) restarting_reclaim_free_slabs(uint64_t * const v_cpu_ptr,
                                             uint64_t * const free_v_cpu_ptr,
                                             const uint32_t   start_cpu) {
    register uint64_t ret_reclaimed_slots asm("rax") = (~(0UL));
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // get current free vec
        "movq (%[free_v_cpu_ptr]), %[ret_reclaimed_slots]\n\t"
        "notq %[ret_reclaimed_slots]\n\t"
        "andq %[ret_reclaimed_slots], (%[v_cpu_ptr])\n\t"       // xor bits
        "2:\n\t"
        RSEQ_START_ABORT_DEF()
        "movq $-1, %[ret_reclaimed_slots]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        : [ ret_reclaimed_slots ] "+r"(ret_reclaimed_slots)
        : [ start_cpu ] "g"(start_cpu), 
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr),
          [ free_v_cpu_ptr ] "g"(free_v_cpu_ptr)
        : "memory", "cc");
    // clang-format on

    // special case where 0 is actually failure
    return ~ret_reclaimed_slots;
}


uint64_t NEVER_INLINE
ALIGN_ATTR(64)
    restarting_fast_abort_reclaim_free_slabs(uint64_t * const v_cpu_ptr,
                                             uint64_t * const free_v_cpu_ptr,
                                             const uint32_t   start_cpu) {
    register uint64_t ret_reclaimed_slots asm("rax") = (~(0UL));
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        "leaq 3b (%%rip), %fs:__rseq_abi@tpoff+8\n\t"
        "1:\n\t"
        "jmp 1f\n\t"
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"
        "mov $-1, %[ret_reclaimed_slots]\n\t"

        // start critical section
        "1:\n\t"

        // check if migrated        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // get current free vec
        "movq (%[free_v_cpu_ptr]), %[ret_reclaimed_slots]\n\t"

        // invert bits so and will unset those in v_cpu_ptr
        "notq %[ret_reclaimed_slots]\n\t"

        // andq and return
        "andq %[ret_reclaimed_slots], (%[v_cpu_ptr])\n\t" 
        "2:\n\t"
        : [ ret_reclaimed_slots ] "+r"(ret_reclaimed_slots)
        : [ start_cpu ] "g"(start_cpu), 
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr),
          [ free_v_cpu_ptr ] "g"(free_v_cpu_ptr)
        : "memory", "cc");
    // clang-format on

    // special case where 0 is failure
    return ~ret_reclaimed_slots;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(64) restarting_goto_set_bit(uint64_t *     v_cpu_ptr,
                                       const uint32_t bit,
                                       const uint32_t start_cpu) {

    uint64_t temp_v;
    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        // temp_v = *v;
        "movq (%[v_cpu_ptr]), %[temp_v]\n\t"

        // temp_v |= 1 << bit
        "btsq %[bit], %[temp_v]\n\t"

        // carry flag == previous bit
        "jc %l[no_set]\n\t"
        
        // commit
        "movq %[temp_v], (%[v_cpu_ptr])\n\t"
        
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        /* start output labels */
        : 
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ temp_v] "r" (temp_v),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc"
        : abort, no_set);
    // clang-format on
    return _RSEQ_SUCCESS;
abort:
    return _RSEQ_MIGRATED;
no_set:
    return _RSEQ_OTHER_FAILURE;
}

uint32_t NEVER_INLINE
ALIGN_ATTR(64) restarting_set_bit(uint64_t *     v_cpu_ptr,
                                  const uint32_t bit,
                                  const uint32_t start_cpu) {

    register uint32_t ret asm("rax") = _RSEQ_MIGRATED;
    uint64_t          temp_v;
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // temp_v = *v;
        "movq (%[v_cpu_ptr]), %[temp_v]\n\t"
        "xorl %[ret], %[ret]\n\t"

        // temp_v |= 1 << bit
        "btsq %[bit], %[temp_v]\n\t"

        // carry == previous bit (so will set if was already set i.e
        // we didnt set i.e _RSEQ_OTHER_FAILURE)
        "setc %[ret]\n\t"
        
        // commit 
        "movq %[temp_v], (%[v_cpu_ptr])\n\t"
        
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "mov $2, %[ret]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        /* start output labels */
        : [ret] "+r" [ret]
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ temp_v] "r" (temp_v),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc");
    // clang-format on

    return ret;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(64) restarting_goto_unset_bit(uint64_t *     v_cpu_ptr,
                                         const uint32_t bit,
                                         const uint32_t start_cpu) {

    uint64_t temp_v;
    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        // temp_v = *v;
        "movq (%[v_cpu_ptr]), %[temp_v]\n\t"
        // if temp_v & 1 << local_bit jump to no_unset


        // temp_v &= ~(1 << local_bit)
        "btcq %[bit], %[temp_v]\n\t"

        // jump if previos bit was not 1
        "jnc %l[no_unset]\n\t"

        //commit
        "movq %[temp_v], (%[v_cpu_ptr])\n\t"

        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        /* start output labels */
        : 
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ local_bit ] "r"(local_bit),
          [ temp_v] "r" (temp_v),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc"
        : abort, no_unset);
    // clang-format on
    return _RSEQ_SUCCESS;
abort:
    return _RSEQ_MIGRATED;
no_unset:
    return _RSEQ_OTHER_FAILURE;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(64) restarting_unset_bit(uint64_t *     v_cpu_ptr,
                                    const uint32_t bit,
                                    const uint32_t start_cpu) {

    register uint32_t ret asm("rax") = _RSEQ_MIGRATED;
    uint64_t          temp_v;
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // temp_v = *v;
        "movq (%[v_cpu_ptr]), %[temp_v]\n\t"
        "xorl %[ret], %[ret]\n\t"
        
        // temp_v |= 1 << bit
        "btcq %[bit], %[temp_v]\n\t"

        // if previous bit was 0 (CF == 0)
        // then ret = 1 -> _RSEQ_OTHER_FAILURE
        "setnc %[ret]\n\t"
        
        // commit 
        "movq %[temp_v], (%[v_cpu_ptr])\n\t"
        
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "mov $2, %[ret]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        /* start output labels */
        : [ret] "+r" [ret]
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ temp_v] "r" (temp_v),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc");
    // clang-format on

    return ret;
}

uint32_t NEVER_INLINE
ALIGN_ATTR(64) restarting_goto_xor(uint64_t * const v_cpu_ptr,
                                   const uint64_t   new_bit_mask,
                                   const uint32_t   start_cpu) {
    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        /* start critical section contents */
        "xorq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        /* start output labels */
        :
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc"
        : abort);
    // clang-format on
    return _RSEQ_SUCCESS;
abort:
    return _RSEQ_MIGRATED;
}

uint32_t NEVER_INLINE
ALIGN_ATTR(64) restarting_xor(uint64_t * const v_cpu_ptr,
                              const uint64_t   new_bit_mask,
                              const uint32_t   start_cpu) {

    register uint32_t ret asm("rax") = _RSEQ_MIGRATED;
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        "xorl %[ret], %[ret]\n\t"
        "xorq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "mov $2, %[ret]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        /* start output labels */
        : [ret] "+r" [ret]
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc");
    // clang-format on
    return ret;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(64) restarting_goto_or(uint64_t * const v_cpu_ptr,
                                  const uint64_t   new_bit_mask,
                                  const uint32_t   start_cpu) {
    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        /* start critical section contents */
        "orq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        /* start output labels */
        :
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
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
uint32_t NEVER_INLINE
ALIGN_ATTR(64) restarting_or(uint64_t * const v_cpu_ptr,
                             const uint64_t   new_bit_mask,
                             const uint32_t   start_cpu) {

    register uint32_t ret asm("rax") = _RSEQ_MIGRATED;
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        "xorl %[ret], %[ret]\n\t"
        "orq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "mov $2, %[ret]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        /* start output labels */
        : [ret] "+r" [ret]
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc");
    // clang-format on
    return ret;
}

uint32_t NEVER_INLINE
ALIGN_ATTR(64) restarting_goto_and(uint64_t * const v_cpu_ptr,
                                   const uint64_t   new_bit_mask,
                                   const uint32_t   start_cpu) {
    // clang-format off
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz %l[abort]\n\t"

        /* start critical section contents */
        "andq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        /* start output labels */
        :
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc"
        : abort);
    // clang-format on
    return _RSEQ_SUCCESS;
abort:
    return _RSEQ_MIGRATED;
}

// not is free so use this if you need andn
uint32_t NEVER_INLINE
ALIGN_ATTR(64) restarting_and(uint64_t * const v_cpu_ptr,
                              const uint64_t   new_bit_mask,
                              const uint32_t   start_cpu) {

    register uint32_t ret asm("rax") = _RSEQ_MIGRATED;
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        "xorl %[ret], %[ret]\n\t"
        "andq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "mov $2, %[ret]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        /* start output labels */
        : [ret] "+r" [ret]
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc");
    // clang-format on
    return ret;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(64) restartable_goto_acquire_lock(uint64_t * const lock_ptr,
                                             const uint32_t   start_cpu) {
    // clang-format off

    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz %l[abort]\n\t"
        
        "cmpq $0, (%[lock_ptr])\n\t"
        "je %l[already_locked]\n\t"
        "movq $1, %[temp_v]\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        /* start output labels */
        :
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ lock_ptr ] "g"(lock_ptr)
        /* end input labels */
        : "memory", "cc"
        : abort, already_locked);
    // clang-format on
    return _RSEQ_SUCCESS;
already_locked:
    return _RSEQ_OTHER_FAILURE;
abort:
    return _RSEQ_MIGRATED;
}


uint32_t NEVER_INLINE
ALIGN_ATTR(64) restartable_acquire_lock(uint64_t * const lock_ptr,
                                        const uint32_t   start_cpu) {
    // clang-format off

    register uint32_t ret asm("rax") = _RSEQ_MIGRATED;
    asm volatile (
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated        
        // "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        "cmpl %[start_cpu], %fs:__rseq_abi@tpoff+4\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"
        
        "cmpq $0, (%[lock_ptr])\n\t"
        "je 2f\n\t"
        "movq $1, %[temp_v]\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
        /* start output labels */
        : [ret] "+r" [ret]
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          // [ rseq_abi ] "g"(&__rseq_abi),
          [ lock_ptr ] "g"(lock_ptr)
        /* end input labels */
        : "memory", "cc");
    // clang-format on
    return ret;
}

#endif
