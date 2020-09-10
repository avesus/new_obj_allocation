#ifndef _CORE_CACHE_H_
#define _CORE_CACHE_H_

#include <assert.h>
#include <stdint.h>

#include <misc/cpp_attributes.h>
#include <misc/macro_helper.h>

#include <allocator/rseq/rseq_asm_defs.h>
#include <allocator/rseq/rseq_common.h>


template<uint32_t n>
struct core_cache {

    static constexpr const uint32_t migrated = n + 1;
    static constexpr const uint32_t no_pop   = ~n;

    uint32_t idx;
    uint64_t ptrs[n];

    uint64_t
    pop(const uint32_t start_cpu) {
        if (idx == 0) {
            return 0;
        }
        uint32_t _idx;
        uint64_t ret;
        // clang-format off
            asm volatile(
                RSEQ_INFO_DEF(32)
                RSEQ_CS_ARR_DEF()
                RSEQ_PREP_CS_DEF(%[ret])
                

                // start critical section
                "1:\n\t"

                "mov %[_migrated], %[ret]\n\t"
                RSEQ_CMP_CUR_VS_START_CPUS()
                "jnz 2f\n\t"

                // prepare 0 return 
                "xorq %[ret], %[ret]\n\t"

                // read idx from memory
                "movl (%[_this]), %[_idx]\n\t"

                // check if idx is 0, if 0 jump to end
                "testl %[_no_pop], %[_idx]\n\t"
                "jz 2f\n\t"

                "subl $1, %[_idx]\n\t"
                
                // mov ptrs[_idx] -> ret
                "movq 8(%[_this], %q[_idx], 8), %[ret]\n\t"

                // idx = _idx
                "movl %[_idx], (%[_this])\n\t"

                // end critical section
                "2:\n\t"

                RSEQ_START_ABORT_DEF()
                "jmp 1b\n\t"
                RSEQ_END_ABORT_DEF()
                : [ret] "=&r" (ret),
                  [_idx] "=&r" (_idx)
                : [start_cpu] "r" (start_cpu),
                  [_no_pop] "i" (no_pop),
                  [_migrated] "i" (migrated),
                  [_this] "g" (this),
                  [this_clobber] "m" (*this)
                : "cc");
        // clang-format on
        return ret;
    }

    uint32_t
    push(uint64_t ptr, const uint32_t start_cpu) {
        if (idx == n) {
            return 1;
        }
        uint64_t temp;
        // clang-format off
            asm volatile goto(
                RSEQ_INFO_DEF(32)
                RSEQ_CS_ARR_DEF()
                RSEQ_PREP_CS_DEF(%[temp])
                
                // start critical section
                "1:\n\t"
                
                RSEQ_CMP_CUR_VS_START_CPUS()
                "jnz %l[abort]\n\t"

                // read idx from memory
                "movl (%[_this]), %k[temp]\n\t"
                
                // check if idx is 0, if 0 jump to end
                "testl %[_n], %k[temp]\n\t"                
                "jnz %l[cc_full]\n\t"
                
                "movq %[ptr], 8(%[_this], %[temp], 8)\n\t"

                // ++idx
                "addl $1, (%[_this])\n\t"

                // end critical section
                "2:\n\t"

                RSEQ_START_ABORT_DEF()
                "jmp 1b\n\t"
                RSEQ_END_ABORT_DEF()

                : 
                : [ptr] "r" (ptr),
                  [temp] "r" (temp),
                  [start_cpu] "r" (start_cpu),
                  [_migrated] "i" (migrated),
                  [_n] "i" (n),
                  [_this] "r" (this),
                  [this_clobber] "m" (*this)
                : "cc"
                : cc_full, abort);
        // clang-format on
        return 0;
    cc_full:
        return 1;
    abort:
        __attribute__((cold));
        return 2;
    }
};

template<uint32_t n>
struct l2_aligned_core_cache {
    core_cache<n> cc;

    uint64_t
    pop(const uint32_t start_cpu) {
        return cc.pop(start_cpu);
    }

    uint32_t
    push(uint64_t ptr, const uint32_t start_cpu) {
        return cc.push(ptr, start_cpu);
    }

    void
    reset() {
        cc.idx = 0;
    }
} L2_LOAD_ALIGN;


#endif
