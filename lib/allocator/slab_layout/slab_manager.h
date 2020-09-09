#ifndef _SLAB_MANAGER_H_
#define _SLAB_MANAGER_H_

#include <stdint.h>
#include <new>
#include <type_traits>

#include <misc/cpp_attributes.h>
#include <optimized/bits.h>

#include <system/mmap_helpers.h>
#include <system/sys_info.h>

#include <allocator/common/internal_returns.h>
#include <allocator/rseq/rseq_base.h>

#include <allocator/slab_layout/obj_slab.h>
#include <allocator/slab_layout/super_slab.h>

#include <allocator/slab_layout/core_cache.h>
#include <allocator/slab_layout/thread_cache.h>


//////////////////////////////////////////////////////////////////////
// simple slab manager that simply allocates 1 super_slab/obj_slab per
// processor. Region size must be set with template parameters


#define SLAB_T(T, max_capacity) typename slab_type<T, max_capacity>::type

template<typename T, typename slab_t>
struct internal_slab_manager {
    slab_t     obj_slabs[NPROCS];
    internal_slab_manager() = default;
};

template<typename T, typename slab_t>
struct slab_manager {

    static constexpr const uint32_t cc_n = 8;
    static constexpr const uint64_t capacity = slab_t::capacity;

    using internal_manager_t = internal_slab_manager<T, slab_t>;

    internal_manager_t * m;
    core_cache<cc_n> cc[NPROCS];

    slab_manager()
        : slab_manager(mmap_alloc_noreserve(sizeof(internal_manager_t))) {

        // this is just to get the first page for each CPU
        // DO NOT USE ON MULTI SOCKET SYSTEM!!!!
        for (uint32_t i = 0; i < NPROCS; ++i) {
            *((uint64_t *)(m->obj_slabs + i)) = 0;
            cc[i].idx = 0;
        }
    }

    slab_manager(void * const base) {
        m = (internal_manager_t *)base;
        new ((void * const)base) internal_manager_t();
    }

    ~slab_manager() {
        safe_munmap(m, sizeof(internal_manager_t));
    }

    void
    reset() {
        memset(m, 0, sizeof(internal_manager_t));
        for (uint32_t i = 0; i < NPROCS; ++i) {
            cc[i].idx = 0;
        }
    }

    T *
    _allocate() {
        uint32_t start_cpu = get_start_cpu();
        uint64_t ptr = cc[start_cpu].pop(start_cpu);
        if(ptr > core_cache<cc_n>::migrated) {
            return (T *)ptr;
        }
        do {
            start_cpu = get_start_cpu();            
            IMPOSSIBLE_COND(start_cpu >= NPROCS);
            ptr = m->obj_slabs[start_cpu]._allocate(start_cpu);
        } while (BRANCH_UNLIKELY(retry_alloc(ptr)));
        return (T *)to_valid_ptr(ptr);
    }

    void
    _free(T * addr) {

         const uint32_t start_cpu = get_start_cpu();
        const uint32_t ret = cc[start_cpu].push((uint64_t)addr, start_cpu);
        if(ret == (cc_n - 1)) {
            for(uint32_t i = 0; i < cc_n; ++i) {
                _inner_free((T *)(cc[start_cpu].ptrs[i]));
            }
            cc[start_cpu].idx = 0;
            return;
        }
        else if(ret >= cc_n) {
            _inner_free(addr);
            return;
        }
    }
    void
    _inner_free(T * addr) {
        IMPOSSIBLE_COND(((uint64_t)addr) < ((uint64_t)m));
        const uint32_t from_cpu =
            (((uint64_t)addr) - ((uint64_t)m)) / sizeof(slab_t);
            IMPOSSIBLE_COND(from_cpu >= NPROCS);
            m->obj_slabs[from_cpu]._first_free(addr);
    }
};


#endif
