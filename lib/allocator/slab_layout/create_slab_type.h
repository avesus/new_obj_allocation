#ifndef _CREATE_SLAB_TYPE_H_
#define _CREATE_SLAB_TYPE_H_

#include <allocator/slab_layout/obj_slab.h>
#include <allocator/slab_layout/super_slab.h>

#include <optimized/const_math.h>

template<typename T, uint64_t max_capacity>
struct type_helper;


template<typename T>
struct type_helper<T, 4096> {
    typedef slab<T> type;
};


template<typename T, uint64_t max_capacity>
struct type_helper {
    typedef super_slab<T, typename type_helper<T, max_capacity / 64>::type>
        type;
};


template<typename T, uint64_t max_capacity>
struct slab_type {
    static constexpr uint64_t _max_capacity =
        cmath::min<uint64_t>(cmath::roundup<uint64_t>(max_capacity, 64), 4096);
    
    using type = typename type_helper<T, _max_capacity>::type;
};

#endif
