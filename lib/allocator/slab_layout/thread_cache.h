#ifndef _THREAD_CACHE_H_
#define _THREAD_CACHE_H_

#include <misc/cpp_attributes.h>
#include <optimized/bits.h>
#include <optimized/division.h>
#include <system/sys_info.h>

#include <immintrin.h>


//////////////////////////////////////////////////////////////////////
// for now taking advantage of the fact that im never using > 2^32 bytes...

template<typename T>
constexpr uint32_t
get_T_idx() {
    if constexpr (sizeof(T) <= sizeof(uint64_t)) {
        return cmath::ulog2<uint64_t>(sizeof(T));
    }
    else {
        return cmath::ulog2<uint64_t>(sizeof(uint64_t)) +
               (sizeof(T) - sizeof(uint64_t)) / sizeof(uint64_t);
    }
}

template<uint32_t n>
struct _thread_cache {
    uint32_t idx;
    uint64_t ptrs[n];


    uint64_t
    push(uint64_t ptr) {
        ptrs[idx] = ptr;
        if (idx == (n - 1)) {
            idx = 0;
            return 1;
        }
        ++idx;
        return 0;
    }

    uint64_t
    pop() {
        if (idx) {
            const uint64_t ret = ptrs[idx];
            --idx;
            return ret;
        }
        return 0;
    }
};

template<uint32_t n, uint32_t m>
struct thread_cache {
    _thread_cache<n> _tcaches[m];

    template<typename T>
    uint64_t
    push(uint64_t ptr) {
        return _tcaches[get_T_idx<T>()].push(ptr);
    }

    template<typename T>
    uint64_t
    pop() {
        return _tcaches[get_T_idx<T>()].pop();
    }
};

__thread thread_cache<32, 8> tc;


#endif
