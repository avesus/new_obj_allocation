#ifndef _RSEQ_OPS_H_
#define _RSEQ_OPS_H_

#include <misc/cpp_attributes.h>
#include <stdint.h>
#include "rseq_asm_defs.h"
#include "rseq_base.h"

/* Man pages 
    https://elixir.bootlin.com/linux/latest/source/kernel/rseq.c
    https://lore.kernel.org/patchwork/patch/896892/
*/


uint64_t NEVER_INLINE ALIGN_ATTR(64)
restarting_set_idx(uint64_t * const v, const uint32_t start_cpu) {
    uint64_t idx = 65, temp_v = 0;
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated        
        "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[idx]\n\t"
        "movq %[idx], %[temp_v]\n\t"
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
        : "memory", "cc", "rax");
    return idx;
}



uint64_t NEVER_INLINE ALIGN_ATTR(64)
restarting_set_idx4(uint64_t * const v, const uint32_t start_cpu) {
    uint64_t idx = 65, temp_v = 0;
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        "leaq 3b (%%rip), %%rax\n\t"
        "movq %%rax, 8(%[rseq_abi])\n\t"
        "jmp 1f\n\t"
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"
        "mov $65, %[idx]\n\t"
        "1:\n\t"
        // check if migrated        
        "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[idx]\n\t"
        "movq %[idx], %[temp_v]\n\t"
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
        : "memory", "cc", "rax");
    return idx;
}


uint64_t NEVER_INLINE ALIGN_ATTR(64)
restarting_set_idx2(uint64_t * const v, const uint32_t start_cpu, const uint64_t r) {
    uint64_t idx = 65, temp_v = 0;

    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated        
        "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[idx]\n\t"
        "movq %[idx], %[temp_v]\n\t"

        "movq %[r], %%rcx\n\t"
        "rorq %%cl, %[idx]\n\t"
        "notq %[idx]\n\t"

        // idx = tzcnt(~*v) (find first zero)
        "tzcntq %[idx], %[idx]\n\t"
        // carry flag is set if src == 0 i.e output == 64
        "jc 2f\n"

        // restore to original idx
        "addq %%rcx, %[idx]\n\t"
        "andq $63, %[idx]\n\t"
        
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
          [ r ] "g" (r),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu),
          [ rseq_abi] "g" (&__rseq_abi)
        : "memory", "cc", "rax", "rcx");
    return idx;
}


uint64_t NEVER_INLINE
restarting_set_idx5(uint64_t * const v, const uint32_t start_cpu, const uint64_t r) {
    uint64_t idx = 65, temp_v = 0;
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        "jmp 6f\n\t"
        "4:\n\t"
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "mov $65, %[idx]\n\t"
        "6:\n\t"
        // check if migrated        
        "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[idx]\n\t"
        "movq %[idx], %[temp_v]\n\t"

        "movq %[r], %%rcx\n\t"
        "rorq %%cl, %[idx]\n\t"
        "notq %[idx]\n\t"

        // idx = tzcnt(~*v) (find first zero)
        "tzcntq %[idx], %[idx]\n\t"
        // carry flag is set if src == 0 i.e output == 64
        "jc 2f\n"
        "addq %%rcx, %[idx]\n\t"
        "andq $63, %[idx]\n\t"
        
        // temp_v |= ((1UL) << idx)
        "btsq %[idx], %[temp_v]\n\t"
        
        // *v = temp_v
        "movq %[temp_v], (%[v])\n\t"
        "2:\n\t"
        : [ idx] "+r" (idx)
        : [ temp_v ] "r" (temp_v),
          [ r ] "g" (r),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu),
          [ rseq_abi] "g" (&__rseq_abi)
        : "memory", "cc", "rax", "rcx");
    return idx;
}


template<uint32_t r>
uint64_t NEVER_INLINE ALIGN_ATTR(64)
restarting_set_idx3(uint64_t * const v, const uint32_t start_cpu) {
    uint64_t idx = 65, temp_v = 0;
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        // check if migrated        
        "cmpl %[start_cpu], 4(%[rseq_abi])\n\t"
        // if migrated goto 2:
        "jnz 2f\n\t"

        // if not migrated temp_v = *v
        "movq (%[v]), %[temp_v]\n\t"
        "rorxq %[r], %[temp_v], %[idx]\n\t"
        "notq %[idx]\n\t"

        // idx = tzcnt(~*v) (find first zero)
        "tzcntq %[idx], %[idx]\n\t"
        // carry flag is set if src == 0 i.e output == 64
        "jc 2f\n"
        "addq %[r], %[idx]\n\t"
        "andq $63, %[idx]\n\t"
        
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
          [ r ] "i" (r),
          [ v] "g" (v),
          [ start_cpu] "g" (start_cpu),
          [ rseq_abi] "g" (&__rseq_abi)
        : "memory", "cc", "rax");
    return idx;
}


uint64_t NEVER_INLINE
try_reclaim_free_slots(uint64_t * v_cpu_ptr,
                       uint64_t * free_v_cpu_ptr_then_temp,
                       const uint32_t   start_cpu) {
    uint64_t ret_reclaimed_slots = 0;
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        RSEQ_CMP_CUR_VS_START_CPUS()
        
        "movq (%[free_v_cpu_ptr_then_temp]), %[ret_reclaimed_slots]\n\t"  // get current free vec
        "testq %[ret_reclaimed_slots], %[ret_reclaimed_slots]\n\t"              // if is 0 nothing to do
        "jz 2f\n\t"
        "leaq -1(%[ret_reclaimed_slots]), %[free_v_cpu_ptr_then_temp]\n\t" // now temp
        "andq %[ret_reclaimed_slots], %[free_v_cpu_ptr_then_temp]\n\t"
        
        "xorq %[free_v_cpu_ptr_then_temp], (%[v_cpu_ptr])\n\t"       // xor bits
        "2:\n\t"
        RSEQ_START_ABORT_DEF()
        "movq $0, %[ret_reclaimed_slots]\n\t"
        "jmp 2b\n\t"
        RSEQ_END_ABORT_DEF()
        : [ ret_reclaimed_slots ] "+g"(ret_reclaimed_slots)
        : [ start_cpu ] "g"(start_cpu), 
          [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr),
          [ free_v_cpu_ptr_then_temp ] "r"(free_v_cpu_ptr_then_temp)
        : "memory", "cc", "rax");
    return ret_reclaimed_slots;
}


uint64_t NEVER_INLINE
try_reclaim_all_free_slabs(uint64_t * v_cpu_ptr,
                           uint64_t * free_v_cpu_ptr,
                           const uint32_t   start_cpu) {
    uint64_t ret_reclaimed_slots = 0;
    asm volatile(
        RSEQ_INFO_DEF(32) RSEQ_CS_ARR_DEF() RSEQ_PREP_CS_DEF()
            RSEQ_CMP_CUR_VS_START_CPUS()
        
        "movq (%[free_v_cpu_ptr]), %[ret_reclaimed_slots]\n\t"  // get current free vec
        "notq %[ret_reclaimed_slots]\n\t"
        "andq %[ret_reclaimed_slots], (%[v_cpu_ptr])\n\t"       // xor bits
        "2:\n\t"
        RSEQ_START_ABORT_DEF()
        "movq $-1, %[ret_reclaimed_slots]\n\t"
        "jmp 2b\n\t"
        RSEQ_END_ABORT_DEF()
        : [ ret_reclaimed_slots ] "+r"(ret_reclaimed_slots)
        : [ start_cpu ] "g"(start_cpu), 
          [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr),
          [ free_v_cpu_ptr ] "g"(free_v_cpu_ptr)
        : "memory", "cc", "rax");
    return ~ret_reclaimed_slots;
}


uint32_t NEVER_INLINE
or_if_unset(uint64_t * v_cpu_ptr, const uint64_t new_bit_mask, const uint32_t start_cpu) {
    asm volatile goto(
        RSEQ_INFO_DEF(32) RSEQ_CS_ARR_DEF() RSEQ_PREP_CS_DEF()
            RSEQ_CMP_CUR_VS_START_CPUS()
        /* start critical section contents */
        "testq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "jnz 4f\n\t"
        "orq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF() "jmp %l[abort]\n\t" RSEQ_END_ABORT_DEF()

        /* start output labels */
        :
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "r"(new_bit_mask),
          [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc", "rax"
        : abort);
    return 0;
abort:
    return 1;
}


uint32_t NEVER_INLINE
xor_if_set(uint64_t * v_cpu_ptr, const uint64_t new_bit_mask, const uint32_t start_cpu) {
    asm volatile goto(
        RSEQ_INFO_DEF(32) RSEQ_CS_ARR_DEF() RSEQ_PREP_CS_DEF()
            RSEQ_CMP_CUR_VS_START_CPUS()
        /* start critical section contents */
        "testq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "jz 4f\n\t"
        "xorq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF() "jmp %l[abort]\n\t" RSEQ_END_ABORT_DEF()

        /* start output labels */
        :
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc", "rax"
        : abort);
    return 0;
abort:
    return 1;
}

uint32_t NEVER_INLINE
rseq_xor(uint64_t * const v_cpu_ptr,
         const uint64_t   new_bit_mask,
         const uint32_t   start_cpu) {
    asm volatile goto(
        RSEQ_INFO_DEF(32) RSEQ_CS_ARR_DEF() RSEQ_PREP_CS_DEF()
            RSEQ_CMP_CUR_VS_START_CPUS()
        /* start critical section contents */
        "xorq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF() "jmp %l[abort]\n\t" RSEQ_END_ABORT_DEF()

        /* start output labels */
        :
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc", "rax"
        : abort);
    return 0;
abort:
    return 1;
}


uint32_t NEVER_INLINE
rseq_or(uint64_t * const v_cpu_ptr,
        const uint64_t   new_bit_mask,
        const uint32_t   start_cpu) {
    asm volatile goto(
        RSEQ_INFO_DEF(32) RSEQ_CS_ARR_DEF() RSEQ_PREP_CS_DEF()
            RSEQ_CMP_CUR_VS_START_CPUS()
        /* start critical section contents */
        "orq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF() "jmp %l[abort]\n\t" RSEQ_END_ABORT_DEF()

        /* start output labels */
        :
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc", "rax"
        : abort);
    return 0;
abort:
    return 1;
}

uint32_t NEVER_INLINE
rseq_and(uint64_t * const v_cpu_ptr,
        const uint64_t   new_bit_mask,
        const uint32_t   start_cpu) {
    asm volatile goto(
        RSEQ_INFO_DEF(32) RSEQ_CS_ARR_DEF() RSEQ_PREP_CS_DEF()
            RSEQ_CMP_CUR_VS_START_CPUS()
        /* start critical section contents */
        "andq %[new_bit_mask], (%[v_cpu_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF() "jmp %l[abort]\n\t" RSEQ_END_ABORT_DEF()

        /* start output labels */
        :
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ new_bit_mask ] "g"(new_bit_mask),
          [ rseq_abi ] "g"(&__rseq_abi),
          [ v_cpu_ptr ] "g"(v_cpu_ptr)
        /* end input labels */
        : "memory", "cc", "rax"
        : abort);
    return 0;
abort:
    return 1;
}


uint32_t NEVER_INLINE
rseq_any_cpu_or(uint64_t * const v_start_ptr, const uint64_t new_bit_mask) {
    asm volatile goto(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF()
        "movl 4(%[rseq_abi]), %%ecx\n\t"
        "sal $6, %%ecx\n\t"
        "leaq (%[v_start_ptr], %%rcx, 1), %%rcx\n\t"
        "orq %[new_bit_mask], (%%rcx)\n\t"
        "2:\n\t"
        RSEQ_START_ABORT_DEF() "jmp %l[abort]\n\t" RSEQ_END_ABORT_DEF()
        /* start output labels */
        :
        /* end output labels */

        /* start input labels */
        : [ new_bit_mask ] "r"(new_bit_mask),
          [ rseq_abi ] "g"(&__rseq_abi),
          [ v_start_ptr ] "g"(v_start_ptr)
        /* end input labels */
        : "memory", "cc", "rax", "rcx"
        : abort);
    return 0;
abort:
    return 1;
}


uint32_t NEVER_INLINE
acquire_lock(uint64_t * const lock_ptr, const uint32_t start_cpu) {
    asm volatile goto(
        RSEQ_INFO_DEF(32) RSEQ_CS_ARR_DEF() RSEQ_PREP_CS_DEF()
            RSEQ_CMP_CUR_VS_START_CPUS()
        /* start critical section contents */
        "testq $1, (%[lock_ptr])\n\t"
        "jnz 4f\n\t"
        "addq $1, (%[lock_ptr])\n\t"
        "2:\n\t"  // post_commit_ip - start_ip
        /* end critical section contents */

        RSEQ_START_ABORT_DEF() "jmp %l[abort]\n\t" RSEQ_END_ABORT_DEF()

        /* start output labels */
        :
        /* end output labels */

        /* start input labels */
        : [ start_cpu ] "g"(start_cpu),
          [ rseq_abi ] "g"(&__rseq_abi),
          [ lock_ptr ] "g"(lock_ptr)
        /* end input labels */
        : "memory", "cc", "rax"
        : abort);
    return 0;
abort:
    return 1;
}

#endif
