#ifndef _THREAD_CACHE_H_
#define _THREAD_CACHE_H_

#include <misc/cpp_attributes.h>
#include <optimized/bits.h>
#include <system/sys_info.h>

//////////////////////////////////////////////////////////////////////
// for now taking advantage of the fact that im never using > 2^32 bytes...
template<uint32_t n>
struct thread_cache {
    uint32_t idx;
    uint32_t ptr_difs[n];

    uint32_t
    push(uint32_t ptr_dif) {
        ptr_difs[idx] = ptr_dif;
        ++idx;

        return idx == n;
    }

    uint64_t
    pop() {
        if (idx) {
            const uint32_t ret = ptr_difs[idx];
            --idx;
            return ret;
        }
        return 0;
    }

    void
    prep_free() {
        
    }
};


#endif
