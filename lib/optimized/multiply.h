#ifndef _MULTIPLY_H_
#define _MULTIPLY_H_


#include <stdint.h>
#include <assert.h>

#include <optimized/const_math.h>
#include <util/const_utils.h>

#include <immintrin.h>


static constexpr uint64_t max_n        = 8;
static constexpr uint64_t perf_n_bound = 8;

template<uint64_t mult>
constexpr uint64_t
_n_shift_steps_rd(uint64_t n) {
    return (n <= max_n && mult && !cmath::is_pow2<uint64_t>(mult))
               ? _n_shift_steps_rd<mult - cmath::prev_p2<uint64_t>(mult)>(n + 1)
               : n;
}


template<uint64_t mult>
constexpr uint64_t
_n_shift_steps_ru(uint64_t n) {
    return (n <= max_n && mult && !cmath::is_pow2<uint64_t>(mult))
               ? _n_shift_steps_ru<cmath::next_p2<uint64_t>(mult) - mult>(n + 1)
               : n;
}


template<uint64_t mult>
constexpr uint64_t
_n_shift_steps(uint64_t n) {
    return (n <= max_n && mult && !cmath::is_pow2<uint64_t>(mult))
               ? cmath::min<uint64_t>(
                     _n_shift_steps<cmath::next_p2<uint64_t>(mult) - mult>(n +
                                                                           1),
                     _n_shift_steps<mult - cmath::prev_p2<uint64_t>(mult)>(n +
                                                                           1))
               : n;
}


template<uint64_t mult>
constexpr uint64_t
n_shift_steps_rd() {
    return _n_shift_steps_rd<mult>(0);
}
static_assert(n_shift_steps_rd<0>() == 0);
static_assert(n_shift_steps_rd<1>() == 0);
static_assert(n_shift_steps_rd<2>() == 0);
static_assert(n_shift_steps_rd<3>() == 1);
static_assert(n_shift_steps_rd<4>() == 0);
static_assert(n_shift_steps_rd<5>() == 1);
static_assert(n_shift_steps_rd<6>() == 1);
static_assert(n_shift_steps_rd<7>() == 2);
static_assert(n_shift_steps_rd<8>() == 0);
static_assert(n_shift_steps_rd<16>() == 0);
static_assert(n_shift_steps_rd<40>() == 1);
static_assert(n_shift_steps_rd<17>() == 1);
static_assert(n_shift_steps_rd<8191>() == max_n + 1);
static_assert(n_shift_steps_rd<8192>() == 0);
static_assert(n_shift_steps_rd<8193>() == 1);


template<uint64_t mult>
constexpr uint64_t
n_shift_steps_ru() {
    return _n_shift_steps_ru<mult>(0);
}

static_assert(n_shift_steps_ru<0>() == 0);
static_assert(n_shift_steps_ru<1>() == 0);
static_assert(n_shift_steps_ru<2>() == 0);
static_assert(n_shift_steps_ru<3>() == 1);
static_assert(n_shift_steps_ru<4>() == 0);
static_assert(n_shift_steps_ru<5>() == 2);
static_assert(n_shift_steps_ru<6>() == 1);
static_assert(n_shift_steps_ru<7>() == 1);
static_assert(n_shift_steps_ru<8>() == 0);
static_assert(n_shift_steps_ru<15>() == 1);
static_assert(n_shift_steps_ru<16>() == 0);
static_assert(n_shift_steps_ru<40>() == 2);
static_assert(n_shift_steps_ru<8191>() == 1);
static_assert(n_shift_steps_ru<8192>() == 0);
static_assert(n_shift_steps_ru<8193>() == 2);


template<uint64_t mult>
constexpr uint64_t
n_shift_steps() {
    return _n_shift_steps<mult>(0);
}

static_assert(n_shift_steps<0>() == 0);
static_assert(n_shift_steps<1>() == 0);
static_assert(n_shift_steps<2>() == 0);
static_assert(n_shift_steps<3>() == 1);
static_assert(n_shift_steps<4>() == 0);
static_assert(n_shift_steps<5>() == 1);
static_assert(n_shift_steps<6>() == 1);
static_assert(n_shift_steps<7>() == 1);
static_assert(n_shift_steps<8>() == 0);
static_assert(n_shift_steps<15>() == 1);
static_assert(n_shift_steps<16>() == 0);
static_assert(n_shift_steps<17>() == 1);
static_assert(n_shift_steps<40>() == 1);
static_assert(n_shift_steps<8191>() == 1);
static_assert(n_shift_steps<8192>() == 0);
static_assert(n_shift_steps<8193>() == 1);


template<uint64_t mult>
constexpr uint64_t
_n_divs(uint64_t n) {
    return (mult & 0x1) ? n : _n_divs<mult / 2>(n + 1);
}

template<uint64_t mult>
constexpr uint64_t
n_divs() {
    return _n_divs<mult>(0);
}

template<uint64_t mult>
constexpr uint64_t
n_div_shift_steps() {
    return n_shift_steps<(mult >> n_divs<mult>())>();
}


enum OPS { ADD = 0, SUB = 1 };

template<uint64_t mult>
constexpr OPS
get_next_op() {
    return n_shift_steps<mult - cmath::prev_p2<uint64_t>(mult)>() <=
                   n_shift_steps<cmath::next_p2<uint64_t>(mult) - mult>()
               ? OPS::ADD
               : OPS::SUB;
}


template<typename T, T mult>
constexpr T
_do_mult(T n) {
    if constexpr (mult == 0 || cmath::is_pow2<T>(mult)) {
        return n * mult;
    }
    else if (get_next_op<(uint64_t)mult>() == OPS::ADD) {
        return n * cmath::prev_p2<T>(mult) +
               _do_mult<T, mult - cmath::prev_p2<T>(mult)>(n);
    }
    else {
        return n * cmath::next_p2<T>(mult) -
               _do_mult<T, cmath::next_p2<T>(mult) - mult>(n);
    }
}

template<typename T, T mult>
constexpr T
do_mult(T n) {
    return _do_mult<T, mult>(n);
}


template<typename T, T mult>
constexpr __m256i ALWAYS_INLINE
_do_mult_vector(__m256i n) {
    if constexpr (mult == 0 || cmath::is_pow2<T>(mult)) {
        if constexpr (mult == 1) {
            return n;
        }
        else if constexpr (sizeof(T) == sizeof(uint64_t)) {

            return _mm256_slli_epi64(n, cmath::ulog2<T>(mult));
        }
        else {
            return _mm256_slli_epi32(n, cmath::ulog2<T>(mult));
        }
    }
    else if constexpr (get_next_op<(uint64_t)mult>() == OPS::ADD) {
        if constexpr (sizeof(T) == sizeof(uint64_t)) {
            return _mm256_add_epi64(
                _mm256_slli_epi64(n, cmath::ulog2<T>(cmath::prev_p2<T>(mult))),
                _do_mult_vector<T, mult - cmath::prev_p2<T>(mult)>(n));
        }
        else {
            return _mm256_add_epi32(
                _mm256_slli_epi32(n, cmath::ulog2<T>(cmath::prev_p2<T>(mult))),
                _do_mult_vector<T, mult - cmath::prev_p2<T>(mult)>(n));
        }
    }
    else {
        if constexpr (sizeof(T) == sizeof(uint64_t)) {
            return _mm256_sub_epi64(
                _mm256_slli_epi64(n, cmath::ulog2<T>(cmath::next_p2<T>(mult))),
                _do_mult_vector<T, cmath::next_p2<T>(mult) - mult>(n));
        }
        else {
            return _mm256_sub_epi32(
                _mm256_slli_epi32(n, cmath::ulog2<T>(cmath::next_p2<T>(mult))),
                _do_mult_vector<T, cmath::next_p2<T>(mult) - mult>(n));
        }
    }
}

template<typename T, T mult>
constexpr __m256i ALWAYS_INLINE
do_mult_vector(__m256i n) {
    if constexpr (mult == 0) {
        if constexpr (sizeof(T) == sizeof(uint64_t)) {
            return _mm256_set1_epi64x(0);
        }
        else {
            return _mm256_set1_epi32(0);
        }
    }
    else if constexpr (n_shift_steps<mult>() > max_n) {
        if constexpr (sizeof(T) == sizeof(uint32_t)) {
            return _mm256_mullo_epi32(n, _mm256_set1_epi32(mult));
        }
        else {
            assert(0);
        }
    }
    else if constexpr (sizeof(T) == sizeof(uint32_t) &&
                       n_shift_steps<mult>() > perf_n_bound) {
        return _mm256_mullo_epi32(n, _mm256_set1_epi32(mult));
    }
    else {
        if constexpr (!(mult & 0x1) &&
                      n_div_shift_steps<mult>() <= n_shift_steps<mult>()) {
            if constexpr (sizeof(T) == sizeof(uint64_t)) {
                return _mm256_slli_epi64(
                    _do_mult_vector<T, (mult >> n_divs<mult>())>(n),
                    n_divs<mult>());
            }
            else {
                return _mm256_slli_epi32(
                    _do_mult_vector<T, (mult >> n_divs<mult>())>(n),
                    n_divs<mult>());
            }
        }
        else {
            return _do_mult_vector<T, mult>(n);
        }
    }
}

static_assert(do_mult<uint64_t, 0>(1) == 0);
static_assert(do_mult<uint64_t, 0>(0) == 0);
static_assert(do_mult<uint64_t, 1>(0) == 0);

static_assert(do_mult<uint64_t, 8>(1) == 8);
static_assert(do_mult<uint64_t, 9>(1) == 9);
static_assert(do_mult<uint64_t, 9>(2) == 18);
static_assert(do_mult<uint64_t, 9>(3) == 27);


#endif
