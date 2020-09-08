#ifndef _DIVISION_H_
#define _DIVISION_H_

#include <stdint.h>

#include <optimized/const_math.h>
#include <util/const_utils.h>

#include <immintrin.h>

//////////////////////////////////////////////////////////////////////
// Hijacked from
// https://github.com/ridiculousfish/libdivide/blob/master/libdivide.h
// and modified for constexpr

template<typename T, T denum>
constexpr T
calculate_proposed_m() {
    const T pp2 = cmath::prev_p2<T>(denum);
    if constexpr (sizeof(T) == sizeof(uint64_t)) {
        __uint128_t n      = ((__uint128_t)pp2) << 64;
        uint64_t    result = (uint64_t)(n / denum);
        return result;
    }
    else {
        uint64_t n      = ((uint64_t)pp2) << 32;
        uint32_t result = (uint32_t)(n / denum);
        return result;
    }
}

template<typename T, T denum>
constexpr T
calculate_remainder() {
    const T pp2 = cmath::prev_p2<T>(denum);
    if constexpr (sizeof(T) == sizeof(uint64_t)) {
        __uint128_t n      = ((__uint128_t)pp2) << 64;
        uint64_t    result = (uint64_t)(n / denum);
        result             = (uint64_t)(n - result * (__uint128_t)denum);
        return result;
    }
    else {
        uint64_t n      = ((uint64_t)pp2) << 32;
        uint32_t result = (uint32_t)(n / denum);
        result          = (uint32_t)(n - result * (uint64_t)denum);
        return result;
    }
}

template<typename T, T denum>
constexpr uint32_t
calculate_should_add() {
    const T pp2       = cmath::prev_p2<T>(denum);
    T       remainder = calculate_remainder<T, denum>();

    const uint32_t e = denum - remainder;
    return e >= pp2;
}


template<typename T, T denum>
constexpr T
calculate_m() {
    const T pp2        = cmath::prev_p2<T>(denum);
    T       proposed_m = calculate_proposed_m<T, denum>();
    T       remainder  = calculate_remainder<T, denum>();

    const uint32_t e = denum - remainder;

    if (e >= pp2) {
        proposed_m += proposed_m;
        T remainder_x2 = remainder + remainder;
        if (remainder_x2 >= denum || remainder_x2 < remainder) {
            ++proposed_m;
        }
    }
    return proposed_m + 1;
}


namespace consts {

template<typename T, T denum>
struct cvals {
    static constexpr const T        m = calculate_m<T, denum>();
    static constexpr const uint32_t should_add =
        calculate_should_add<T, denum>();

    static constexpr const uint32_t is_pow_2 = cmath::is_pow2<T>(denum);
    static constexpr const uint32_t floor_log_d =
        cmath::ulog2<T>(cmath::prev_p2<T>(denum));
};

}  // namespace consts


//////////////////////////////////////////////////////////////////////
// Division stuff starts here

template<typename T, T denum>
constexpr T
do_div(T n) {

    if constexpr (consts::cvals<T, denum>::is_pow_2) {
        return n / denum;
    }
    else {
        T res;
        if constexpr (sizeof(T) == sizeof(uint64_t)) {
            __uint128_t _n = n, _m = consts::cvals<T, denum>::m;
            res = (_n * _m) >> 64;
        }
        else {
            uint64_t _n = n, _m = consts::cvals<T, denum>::m;
            res = (_n * _m) >> 32;
        }
        if constexpr (consts::cvals<T, denum>::should_add) {
            res = ((n - res) >> 1) + res;
        }
        return res >> consts::cvals<T, denum>::floor_log_d;
    }
}



template<typename T, T denum>
constexpr __m256i ALWAYS_INLINE
do_div_vector(__m256i n) {

    // need to entirely seperate 32 and 64 because of avx prefixes
    if constexpr (sizeof(T) == sizeof(uint64_t)) {
        if constexpr (consts::cvals<T, denum>::is_pow_2) {
            return _mm256_srli_epi64(n, consts::cvals<T, denum>::floor_log_d);
        }
        else {
            __m256i m = _mm256_set1_epi64x(consts::cvals<T, denum>::m);

            __m256i lomask = _mm256_set1_epi64x(0xffffffff);
            __m256i nh     = _mm256_shuffle_epi32(n, 0xB1);
            __m256i mh     = _mm256_shuffle_epi32(m, 0xB1);
            __m256i w0     = _mm256_mul_epu32(n, m);
            __m256i w1     = _mm256_mul_epu32(n, mh);
            __m256i w2     = _mm256_mul_epu32(nh, m);
            __m256i w3     = _mm256_mul_epu32(nh, mh);
            __m256i w0h    = _mm256_srli_epi64(w0, 32);
            __m256i s1     = _mm256_add_epi64(w1, w0h);
            __m256i s1l    = _mm256_and_si256(s1, lomask);
            __m256i s1h    = _mm256_srli_epi64(s1, 32);
            __m256i s2     = _mm256_add_epi64(w2, s1l);
            __m256i s2h    = _mm256_srli_epi64(s2, 32);
            __m256i res    = _mm256_add_epi64(w3, s1h);
            res            = _mm256_add_epi64(res, s2h);
            if constexpr (consts::cvals<T, denum>::should_add) {
                __m256i _res = _mm256_add_epi64(
                    _mm256_srli_epi64(_mm256_sub_epi64(n, res), 1),
                    res);
                return _mm256_srli_epi64(_res,
                                         consts::cvals<T, denum>::floor_log_d);
            }
            else {
                return _mm256_srli_epi64(res,
                                         consts::cvals<T, denum>::floor_log_d);
            }
        }
    }
    else {
        if constexpr (consts::cvals<T, denum>::is_pow_2) {
            return _mm256_srli_epi32(n, consts::cvals<T, denum>::floor_log_d);
        }

        else {
            __m256i m = _mm256_set1_epi32(consts::cvals<T, denum>::m);

            // obviously I have no idea wtf I am doing
            __m256i hi_0_2 = _mm256_srli_epi64(_mm256_mul_epu32(n, m), 32);
            __m256i s_1_3  = _mm256_srli_epi64(n, 32);
            __m256i mask   = _mm256_set_epi32(-1, 0, -1, 0, -1, 0, -1, 0);
            __m256i hi_1_3 = _mm256_and_si256(_mm256_mul_epu32(s_1_3, m), mask);
            __m256i res    = _mm256_or_si256(hi_0_2, hi_1_3);
            if constexpr (consts::cvals<T, denum>::should_add) {
                __m256i _res = _mm256_add_epi32(
                    _mm256_srli_epi32(_mm256_sub_epi32(n, res), 1),
                    res);
                return _mm256_srli_epi32(_res,
                                         consts::cvals<T, denum>::floor_log_d);
            }
            else {
                return _mm256_srli_epi32(res,
                                         consts::cvals<T, denum>::floor_log_d);
            }
        }
    }
}


#endif
