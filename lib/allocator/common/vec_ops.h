#ifndef _VEC_OPS_H_
#define _VEC_OPS_H_

#include <misc/cpp_attributes.h>
#include <misc/macro_helper.h>

#include <optimized/vmath.h>


#define VEC_PRINT(X, Y, Z)                                                     \
    _mm256_store_si256((__m256i *)(Y), Z);                                     \
    fprintf(stderr, "%s: [%x", V_TO_STR(Z), (Y)[0]);                           \
    for (uint32_t _i = 1; _i < X; _i++) {                                      \
        fprintf(stderr, ", %x", (Y)[_i]);                                      \
    }                                                                          \
    fprintf(stderr, "]\n");


// inlining this is important so avoid memory write on next_idx_mask
uint64_t ALWAYS_INLINE PURE_ATTR
create_full_mask(const uint32_t * const ptrs, uint32_t idx_mask) {
    IMPOSSIBLE_COND(idx_mask == 0);
    uint64_t freed_mask = 0;

    do {
        uint32_t p_idx = bits::tzcnt<uint32_t>(idx_mask);
        idx_mask ^= (1 << p_idx);
        freed_mask |= (1UL) << ptrs[p_idx];
    } while (idx_mask);

    return freed_mask;
}

uint32_t ALWAYS_INLINE PURE_ATTR
create_idx_mask(const uint32_t * const ptrs,
                const uint32_t         target_idx,
                const uint32_t         target_mask,
                uint32_t               idx_mask) {
    uint32_t next_idx = 0;
    do {
        uint32_t p_idx = bits::tzcnt<uint32_t>(idx_mask);
        idx_mask ^= (1 << p_idx);
        uint32_t ptr = ptrs[p_idx];
        if ((ptr & target_mask) == target_idx) {
            next_idx |= p_idx;
        }
    } while (idx_mask);
    return next_idx;
}


uint64_t ALWAYS_INLINE CONST_ATTR
reduce_mask_v(const __m256i m) {
    __m128i m128 =
        _mm_or_si128(_mm256_castsi256_si128(m), _mm256_extracti128_si256(m, 1));
    __m128i m128_reduced = _mm_or_si128(m128, _mm_unpackhi_epi64(m128, m128));
    return (uint64_t)_mm_cvtsi128_si64(m128_reduced);
}


__m256i ALWAYS_INLINE CONST_ATTR
merge_partial_masks_v(const __m256i m1, const __m256i m2) {
    return _mm256_or_si256(m1, m2);
}


__m256i ALWAYS_INLINE CONST_ATTR
create_packed_idx_vec_v(__m256i idx_v1, __m256i idx_v2) {
    return _mm256_packus_epi16(idx_v1, idx_v2);
}


__m256i ALWAYS_INLINE CONST_ATTR
create_partial_mask_v(__m256i idx_v) {
    __m256i indexes_lo =
        _mm256_and_si256(idx_v, _mm256_set1_epi64x(0xffffffff));
    __m256i indexes_hi = _mm256_shuffle_epi32(idx_v, 0x55);

    __m256i mask_lo = _mm256_sllv_epi64(_mm256_set1_epi64x(1), indexes_lo);
    __m256i mask_hi = _mm256_sllv_epi64(_mm256_set1_epi64x(1), indexes_hi);

    return _mm256_or_si256(mask_lo, mask_hi);
}


#endif
