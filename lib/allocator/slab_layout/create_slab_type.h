#ifndef _CREATE_SLAB_TYPE_H_
#define _CREATE_SLAB_TYPE_H_

#include <allocator/slab_layout/obj_slab.h>
#include <allocator/slab_layout/super_slab.h>

template<uint32_t... per_level_nvec>
constexpr uint32_t
nlevel_specified(uint32_t n) {
    uint32_t temp[] = { static_cast<uint32_t>(per_level_nvec)... };
    return sizeof(temp) / sizeof(uint32_t);
}


template<uint32_t... per_level_nvec>
constexpr uint32_t
get_N(uint32_t n) {
    uint32_t temp[] = { static_cast<uint32_t>(per_level_nvec)... };
    return temp[n];
}

template<typename T,
         uint32_t nlevels,
         uint32_t level,
         uint32_t... per_level_nvec>
struct type_helper;


template<typename T, uint32_t nlevel, uint32_t... per_level_nvec>
struct type_helper<T, nlevel, nlevel, per_level_nvec...> {
    typedef slab<T, get_N<per_level_nvec...>(nlevel)> type;
};

template<typename T,
         uint32_t nlevels,
         uint32_t level,
         uint32_t... per_level_nvec>
struct type_helper {
    typedef super_slab<
        T,
        get_N<per_level_nvec...>(level),
        typename type_helper<T, nlevels, level + 1, per_level_nvec...>::type>
        type;
};


template<typename T, uint32_t levels, uint32_t... per_level_nvec>
struct slab_type {
    using type = typename type_helper<T, levels, 0, per_level_nvec...>::type;
};

#endif
