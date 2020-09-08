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

#include <allocator/common/vec_ops.h>
#include <allocator/slab_layout/thread_cache.h>

//////////////////////////////////////////////////////////////////////
// simple slab manager that simply allocates 1 super_slab/obj_slab per
// processor. Region size must be set with template parameters


#define SLAB_T(T, max_capacity) typename slab_type<T, max_capacity>::type


template<typename T, typename slab_t>
struct internal_slab_manager {
    slab_t obj_slabs[NPROCS];
    internal_slab_manager() = default;
};


template<typename T, typename slab_t>
struct slab_manager {

    static constexpr const uint64_t capacity = slab_t::capacity;

    using internal_manager_t = internal_slab_manager<T, slab_t>;

    internal_manager_t * m;

    slab_manager()
        : slab_manager(mmap_alloc_noreserve(sizeof(internal_manager_t))) {

        // this is just to get the first page for each CPU
        // DO NOT USE ON MULTI SOCKET SYSTEM!!!!
        for (uint32_t i = 0; i < NPROCS; ++i) {
            *((uint64_t *)(m->obj_slabs + i)) = 0;
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
    }

    T *
    _allocate() {
        uint64_t ptr;
        do {
            const uint32_t start_cpu = get_start_cpu();
            IMPOSSIBLE_COND(start_cpu >= NPROCS);
            ptr = m->obj_slabs[start_cpu]._allocate(start_cpu);
        } while (BRANCH_UNLIKELY(retry_alloc(ptr)));
        return (T *)to_valid_ptr(ptr);
    }

    static __m256i ALWAYS_INLINE CONST_ATTR
    get_core_idx_v(__m256i ptrs_v) {
        return vmath::vdiv<uint32_t, sizeof(slab_t)>(ptrs_v);
    }

    template<typename _slab_t = slab_t>
    constexpr static __m256i ALWAYS_INLINE CONST_ATTR
    get_idx_v(__m256i ptrs_v, __m256i core_v) {
        __m256i base_v = vmath::vmult<uint32_t, sizeof(slab_t)>(core_v);
        __m256i adjusted_ptrs_v_t0 = _mm256_sub_epi32(ptrs_v, base_v);
        __m256i adjusted_ptrs_v =
            _mm256_sub_epi32(adjusted_ptrs_v_t0,
                             _mm256_set1_epi32(offsetof(slab_t, inner_slabs)));
        __m256i next_idx_v = _slab_t::template get_idx_v<0>(adjusted_ptrs_v);
        return next_idx_v;
    }


    void
    _free(T * addr) {
        if (tc.push(tc.prepare((uint64_t)addr, (uint64_t)m))) {

            __m256i ptrs_v1   = _mm256_load_si256((__m256i *)(tc.ptrs + 0));
            __m256i core_v_c1 = get_core_idx_v(ptrs_v1);
            __m256i idx_v1    = get_idx_v(ptrs_v1, core_v_c1);

            __m256i ptrs_v2   = _mm256_load_si256((__m256i *)(tc.ptrs + 8));
            __m256i core_v_c2 = get_core_idx_v(ptrs_v2);
            __m256i idx_v2    = get_idx_v(ptrs_v2, core_v_c2);

            __m256i ptrs_v3   = _mm256_load_si256((__m256i *)(tc.ptrs + 16));
            __m256i core_v_c3 = get_core_idx_v(ptrs_v3);
            __m256i idx_v3    = get_idx_v(ptrs_v3, core_v_c3);

            __m256i ptrs_v4   = _mm256_load_si256((__m256i *)(tc.ptrs + 24));
            __m256i core_v_c4 = get_core_idx_v(ptrs_v4);
            __m256i idx_v4    = get_idx_v(ptrs_v4, core_v_c4);

            __m256i core_list_v_c12 = _mm256_packus_epi16(core_v_c1, core_v_c2);
            __m256i core_list_v_c34 = _mm256_packus_epi16(core_v_c3, core_v_c4);

            __m256i core_list_v =
                _mm256_packus_epi16(core_list_v_c12, core_list_v_c34);

            _mm256_store_si256((__m256i *)(tc.ptrs + 0), idx_v1);
            _mm256_store_si256((__m256i *)(tc.ptrs + 8), idx_v2);
            _mm256_store_si256((__m256i *)(tc.ptrs + 16), idx_v3);
            _mm256_store_si256((__m256i *)(tc.ptrs + 24), idx_v4);

            uint8_t core_list[32] ALIGN_ATTR(32);
            _mm256_store_si256((__m256i *)core_list, core_list_v);

            uint32_t core      = core_list[0];
            uint32_t core_mask = _mm256_movemask_epi8(
                _mm256_cmpeq_epi8(core_list_v, _mm256_set1_epi8(core)));

            IMPOSSIBLE_COND(core_mask == 0);
            IMPOSSIBLE_COND(core >= NPROCS);

            if (core_mask == (~(0u))) {
                m->obj_slabs[core]._tc_first_free_fast(idx_v1,
                                                       idx_v2,
                                                       idx_v3,
                                                       idx_v4);
                IMPOSSIBLE_COND(get_start_cpu() >= NPROCS);
                return;
            }

            uint32_t aggregate_mask = ~0;
            while (1) {
                aggregate_mask ^= core_mask;

                m->obj_slabs[core]._tc_first_free_slow(core_mask);
                if (aggregate_mask) {

                    core = core_list[bits::tzcnt<uint32_t>(aggregate_mask)];
                    IMPOSSIBLE_COND(core >= NPROCS);

                    core_mask = _mm256_movemask_epi8(
                        _mm256_cmpeq_epi8(core_list_v,
                                          _mm256_set1_epi8(core_list[core])));

                    // let the compiler know we are always making progress
                    IMPOSSIBLE_COND(core_mask == 0);
                    IMPOSSIBLE_COND((core_mask & aggregate_mask) != core_mask);


                    continue;
                }

                break;
            }
        }
    }
    void
    _nfree(T * addr) {
        IMPOSSIBLE_COND(((uint64_t)addr) < ((uint64_t)m));
        const uint32_t from_cpu =
            (((uint64_t)addr) - ((uint64_t)m)) / sizeof(slab_t);

        IMPOSSIBLE_COND(from_cpu >= NPROCS);

        m->obj_slabs[from_cpu]._first_free(addr);
    }
};


#endif
