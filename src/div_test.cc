#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <system/sys_info.h>

#include <immintrin.h>
#include <optimized/division.h>

#define TEST_SIZE (1u << 22)

#ifndef DENUM
    #define DENUM 43243
#endif

#ifndef TEST_T
    #define TEST_T uint64_t
#endif

int
main() {

    const TEST_T min_bound_test = DENUM * 4096;
    for (TEST_T i = 0; i < min_bound_test; ++i) {
        if (!(i / DENUM == do_div<TEST_T, DENUM>(i))) {
            fprintf(stderr,
                    "%lu / %d (%lu != %lu)\n",
                    i,
                    DENUM,
                    i / DENUM,
                    do_div<uint64_t, DENUM>(i));
        }
    }


    TEST_T t = min_bound_test;
    for (uint32_t i = 0; i < TEST_SIZE; ++i) {
        if (!(t / DENUM == do_div<TEST_T, DENUM>(t))) {
            fprintf(stderr,
                    "%lu / %d (%lu != %lu)\n",
                    t,
                    DENUM,
                    t / DENUM,
                    do_div<TEST_T, DENUM>(t));
        }
        t += rand();
    }

    
    TEST_T * vals = (TEST_T *)aligned_alloc(CACHE_LINE_SIZE, TEST_SIZE * sizeof(TEST_T));

    srand(0);
    int32_t first_rand = rand();
    for (uint32_t i = 0; i < TEST_SIZE; ++i) {
        vals[i] = rand();
    }
    
    const uint32_t sratio = sizeof(__m256i) / sizeof(TEST_T);

    for (uint32_t i = 0; i < TEST_SIZE; i += sratio) {
        *((__m256i *)(vals + i)) =
            do_div_vector<TEST_T, DENUM>(*((__m256i *)(vals + i)));
    }
    srand(0);
    assert(first_rand == rand());
    for (uint32_t i = 0; i < TEST_SIZE; ++i) {
        assert(vals[i] == (((TEST_T)rand()) / DENUM));
    }
}
