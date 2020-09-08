#ifndef _THREAD_CACHE_H_
#define _THREAD_CACHE_H_

#include <misc/cpp_attributes.h>
#include <system/sys_info.h>

#include <optimized/bits.h>

//////////////////////////////////////////////////////////////////////
// for now taking advantage of the fact that im never using > 2^32 bytes...


struct thread_cache {
    using ptr_t = uint32_t;

    static const constexpr uint32_t n      = 32;
    static const constexpr uint32_t sratio = sizeof(__m256i) / sizeof(ptr_t);

    ptr_t    ptrs[n];
    uint32_t idx;


    uint32_t
    push(ptr_t ptr) {
        ptrs[idx] = ptr;

        if(idx == (n - 1)) {
            idx = 0;
            return 1;
        }
        ++idx;
        return 0;
    }

    ptr_t
    pop() {
        if (idx) {
            const ptr_t ret = ptrs[idx];
            --idx;
            return ret;
        }
        return 0;
    }

    uint64_t ALWAYS_INLINE CONST_ATTR
    restore(ptr_t ptr, const uint64_t base) {
        if constexpr (sizeof(ptr_t) == sizeof(uint64_t)) {
            return ptr;
        }
        else {
            return ptr + base;
        }
    }

    ptr_t ALWAYS_INLINE CONST_ATTR
    prepare(uint64_t ptr, const uint64_t base) {
        if constexpr (sizeof(ptr_t) == sizeof(uint64_t)) {
            return ptr;
        }
        else {
            IMPOSSIBLE_COND(ptr < base);
            IMPOSSIBLE_COND(ptr - base >= ((1UL) << 32));
            return ptr - base;
        }
    }
} ALIGN_ATTR(64);
__thread thread_cache tc;

#endif

// Local Variables:
// rmsbolt-command: "/usr/bin/c++
// -I/home/noah/programs/branch_2/new_obj_allocation/lib    -O3 -Wall -Wextra
// -Wno-unused-function -march=native -mtune=native -mavx2 -std=gnu++1z"
// rmsbolt-disassemble: t
// End:
