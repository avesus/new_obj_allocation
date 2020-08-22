#ifndef _RSEQ_OPS_H_
#define _RSEQ_OPS_H_

#include <misc/cpp_attributes.h>
#include <misc/macro_helper.h>
#include <stdint.h>
#include <system/sys_info.h>
#include "rseq_asm_defs.h"
#include "rseq_base.h"


__thread uint64_t _tlv_rand;

//#define FAST_ABORT
//////////////////////////////////////////////////////////////////////
// General unless special case
#define _RSEQ_MIGRATED      2
#define _RSEQ_OTHER_FAILURE 1
#define _RSEQ_SUCCESS       0

/* Man pages
    https://elixir.bootlin.com/linux/latest/source/kernel/rseq.c
    https://lore.kernel.org/patchwork/patch/896892/
*/


//////////////////////////////////////////////////////////////////////
// The restarting_set_*idx(...) functions are on the SUPER hot path. Any line
// that can be optimized should be


#define _RSEQ_SET_IDX_MIGRATED 4096
#define _RSEQ_SET_IDX_FAILURE  (~(0UL))

uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_set_idx(uint64_t * const v1, const uint32_t start_cpu) {
    // return [0 - 4095] -> success (that is the index)
    // return [4097] -> failure the thread migrated
    // return [-1] -> failure the bit vector is full


#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    // Pin for return so compiler doesnt fuck up
    uint64_t idx;

    // some temps I trust the compiler to allocate smartly
    uint64_t idx_v1, temp_v1, temp_v2;
#pragma GCC diagnostic push
#pragma GCC diagnostic push

    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()

        // any register will do
        RSEQ_PREP_CS_DEF(%[temp_v1])

        "mov $" V_TO_STR(_RSEQ_SET_IDX_MIGRATED) ", %[idx]\n\t"

#ifdef FAST_ABORT
        // skip abort first time
        "jmp 1f\n\t"
        
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"
        "mov $" V_TO_STR(_RSEQ_SET_IDX_MIGRATED) ", %[idx]\n\t"
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
                
        // idx = temp_v
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
        "mov $" V_TO_STR(_RSEQ_SET_IDX_MIGRATED) ", %[idx]\n\t"
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
#endif

        : [ idx] "=&r" (idx),
          [ idx_v1 ] "=&r" (idx_v1),
          [ temp_v2 ] "=&r" (temp_v2),
          [ temp_v1 ] "=&r" (temp_v1)
        : [ v1 ] "r" ( v1 ),
          [ v1_clobber ] "m" (*v1),
          [ start_cpu] "g" (start_cpu)
        : "cc");

    return idx;
}




uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_reclaim_free_slabs(uint64_t * const v,
                                  uint64_t * const free_v,
                                  const uint32_t   start_cpu) {
    uint64_t ret_reclaimed_slots;
    // clang-format off
    asm volatile(
        RSEQ_INFO_DEF(32)
        RSEQ_CS_ARR_DEF()
        RSEQ_PREP_CS_DEF(%[ret_reclaimed_slots])

#ifdef FAST_ABORT
        // jump to critical section first time
        "jmp 1f\n\t"
        ".byte 0x0f, 0xb9, 0x3d\n\t"
        ".long 0x53053053\n\t"
        "4:\n\t"

#endif
        
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

#ifndef FAST_ABORT
        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()
#endif
        : [ ret_reclaimed_slots ] "=&r"(ret_reclaimed_slots)
        : [ start_cpu ] "g"(start_cpu), 
          [ v ] "g"(v),
          [ v_clobber ] "m"(*v),
          [ free_v ] "g"(free_v),
          [ free_v_clobber ] "m"(*free_v)
        : "cc");
    // clang-format on

    // special case where 0 is actually failure
    return ~ret_reclaimed_slots;
}


uint32_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_set_bit(uint64_t * const v,
                                               const uint64_t   bit,
                                               const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push
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
          [ v ] "g"(v),
          [ v_clobber ] "m"(*v)
        : "cc"
        : abort);
    // clang-format on

    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}

uint32_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_set_bit_or(uint64_t * const v,
                                                  const uint64_t   bit,
                                                  const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push
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
          [ v ] "g"(v),
          [ v_clobber ] "m"(*v)
        : "cc"
        : abort);
    // clang-format on

    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_set_bit_fetch(uint64_t * const v,
                                                     const uint64_t   bit,
                                                     const uint32_t start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push
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

        // temp_v |= 1 << bit
        "btsq %[bit], %[temp_v]\n\t"
        
        // commit 
        "movq %[temp_v], (%[v])\n\t"
        
        "2:\n\t"
        // end critical section

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        : [ temp_v ] "=&r" (temp_v)
        : [ start_cpu ] "g"(start_cpu),
          [ bit ] "r"(bit),
          [ v ] "g"(v),
          [ v_clobber ] "g"(*v)
        : "cc");
    // clang-format on

    return temp_v;
}


uint32_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_unset_bit(uint64_t * const v,
                                                 const uint64_t   bit,
                                                 const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push
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
          [ v ] "g"(v),
          [ v_clobber ] "m"(*v)
        : "cc"
        : abort);
    // clang-format on

    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


uint64_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_unset_bit_fetch(uint64_t * const v,
                               const uint64_t   bit,
                               const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    uint64_t temp_v;
#pragma GCC diagnostic push
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
          [ v ] "g"(v),
          [ v_clobber ] "m"(*v)
        : "cc");

    // clang-format on

    return temp_v;
}


uint32_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE) restarting_xor(uint64_t * const v,
                                           const uint64_t   new_bit_mask,
                                           const uint32_t   start_cpu) {

#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    uint64_t temp_r;
#pragma GCC diagnostic push
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
          [ temp_r] "r" (temp_r),
          [ v ] "g"(v),
          [ v_clobber ] "m"(*v)
        : "cc"
        : abort);

    // clang-format on
    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


uint32_t ALWAYS_INLINE
                       ALIGN_ATTR(CACHE_LINE_SIZE) restarting_or(uint64_t * const v,
                                          const uint64_t   new_bit_mask,
                                          const uint32_t   start_cpu) {
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    uint64_t temp_r;
#pragma GCC diagnostic push
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
          [ temp_r] "r" (temp_r),
          [ v ] "g"(v),
          [ v_clobber ] "m"(*v)
          /* end input labels */
        : "cc"
        : abort);
    // clang-format on
    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


uint32_t ALWAYS_INLINE
                       ALIGN_ATTR(CACHE_LINE_SIZE) restarting_and(uint64_t * const v,
                                           const uint64_t   new_bit_mask,
                                           const uint32_t   start_cpu) {
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    uint64_t temp_r;
#pragma GCC diagnostic push
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
          [ temp_r] "r" (temp_r),
          [ v ] "g"(v),
          [ v_clobber ] "m"(*v)
        : "cc"
        : abort);

    // clang-format on
    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


uint32_t ALWAYS_INLINE
ALIGN_ATTR(CACHE_LINE_SIZE)
    restarting_incr(uint64_t * const v, const uint32_t start_cpu) {
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    uint64_t temp_r;
#pragma GCC diagnostic push
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

        "addq $1, (%[v])\n\t"

        // end critical section
        "2:\n\t" 

        RSEQ_START_ABORT_DEF()
        "jmp 1b\n\t"
        RSEQ_END_ABORT_DEF()

        :
        : [ start_cpu ] "g"(start_cpu),
          [ temp_r] "r" (temp_r),
          [ v ] "g"(v),
          [ v_clobber ] "m"(*v)
        : "cc"
        : abort);

    // clang-format on
    return _RSEQ_SUCCESS;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


uint32_t NEVER_INLINE
                       ALIGN_ATTR(CACHE_LINE_SIZE) restarting_acquire_lock(uint64_t * const lock_ptr,
                                                    const uint32_t start_cpu) {
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    uint64_t temp_r;
#pragma GCC diagnostic push
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
          [ temp_r] "r" (temp_r),
          [ lock_ptr ] "g"(lock_ptr),
          [ lock_ptr_clobber ] "m"(*lock_ptr)
        : "cc"
        : abort, already_locked);

    // clang-format on
    return _RSEQ_SUCCESS;
already_locked:
    return _RSEQ_OTHER_FAILURE;
abort:
    __attribute__((cold));
    return _RSEQ_MIGRATED;
}


#endif
