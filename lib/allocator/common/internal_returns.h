#ifndef _INTERNAL_RETURNS_H_
#define _INTERNAL_RETURNS_H_

#include <misc/cpp_attributes.h>

static constexpr const uint64_t FULL_ALLOC_VEC = (~(0UL));
static constexpr const uint64_t EMPTY_FREE_VEC = 0;

static constexpr const uint64_t FAILED_FULL = (1UL) << 61;
static constexpr const uint64_t SLAB_READY  = (1UL) << 62;
static constexpr const uint64_t FAILED_RSEQ = (1UL) << 63;

static constexpr const uint64_t PTR_MASK = ((1UL) << 48) - 1;

static constexpr uint32_t ALWAYS_INLINE CONST_ATTR
successful(const uint64_t ret_val) {
    return ret_val < PTR_MASK;
}

static constexpr uint64_t ALWAYS_INLINE CONST_ATTR
to_valid_ptr(const uint64_t ret_val) {
    return ret_val & PTR_MASK;
}

static constexpr uint64_t ALWAYS_INLINE CONST_ATTR
retry_alloc(const uint64_t ret_val) {
    return ret_val > FAILED_FULL;
}


#endif
