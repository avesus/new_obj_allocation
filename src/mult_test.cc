#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <misc/error_handling.h>

#include <util/arg.h>
#include <util/verbosity.h>

#include <system/sys_info.h>

#include <timing/timers.h>

#include <immintrin.h>

#include <optimized/multiply.h>


uint32_t which_to_run = 0;
uint32_t do_perf      = 0;
uint32_t do_corr      = 0;
uint32_t rseed        = 0;
uint32_t test_size    = (100000);

#ifndef MULT
    #define MULT 184
#endif

#ifndef TEST_T
    #define TEST_T uint64_t
#endif
const uint32_t sratio = sizeof(__m256i) / sizeof(TEST_T);

void
corr_test_do_mult(TEST_T * vals, const uint32_t tsize) {
    for (uint32_t i = 0; i < tsize; ++i) {
        uint64_t res = do_mult<TEST_T, MULT>(vals[i]);
        DIE_ASSERT(res == vals[i] * MULT,
                   "%lu * %lu -> %lu != %lu\n",
                   (uint64_t)vals[i],
                   (uint64_t)MULT,
                   res,
                   (uint64_t)(vals[i] * MULT));
        if (verbose) {
            fprintf(stderr,
                    "%lu * %lu -> %lu == %lu\n",
                    (uint64_t)vals[i],
                    (uint64_t)MULT,
                    res,
                    (uint64_t)(vals[i] * MULT));
        }
    }

    fprintf(stderr, "All Tests Passed\n");
}


void
corr_test_do_mult_vec(__m256i * vals, const uint32_t tsize) {


    for (uint32_t i = 0; i < tsize / sratio; ++i) {
        vals[i] = do_mult_vector<TEST_T, MULT>(vals[i]);
    }
    srand(rseed);
    TEST_T * tvals = (TEST_T *)vals;
    for (uint32_t i = 0; i < tsize; ++i) {
        TEST_T v = rand();
        if (sizeof(TEST_T) == sizeof(uint64_t)) {
            v *= rand();
        }
        DIE_ASSERT(tvals[i] == v * MULT,
                   "%lu * %lu -> %lu != %lu\n",
                   (uint64_t)v,
                   (uint64_t)MULT,
                   tvals[i],
                   v * MULT);

        if (verbose) {
            fprintf(stderr,
                    "%lu * %lu -> %lu == %lu\n",
                    (uint64_t)v,
                    (uint64_t)MULT,
                    (uint64_t)tvals[i],
                    (uint64_t)(v * MULT));
        }
    }
    fprintf(stderr, "All Tests Passed\n");
}


void
perf_test_mult(TEST_T * vals, const uint32_t tsize) {
    uint64_t start, end;

    start = timers::get_cycles();
    for (uint32_t i = 0; i < tsize; ++i) {
        volatile TEST_T sink = vals[i] * MULT;
        (void)(sink);
    }
    end = timers::get_cycles();

    double res = end - start;
    res /= tsize;
    fprintf(stderr, "Normal Mult\n\tCycles Per Op: %.3lf\n", res);
}


void
perf_test_mult_vec(__m256i * vals, const uint32_t tsize) {
    const uint32_t _tsize = tsize / sratio;

    uint64_t start, end;

    start = timers::get_cycles();
    for (uint32_t i = 0; i < _tsize; ++i) {
        volatile __m256i sink =
            _mm256_mullo_epi32(vals[0], _mm256_set1_epi32(MULT));
        (void)(sink);
    }
    end = timers::get_cycles();

    double res = end - start;
    res /= tsize;
    fprintf(stderr, "Mult Vec\n\tCycles Per Op: %.3lf\n", res);
}


void
perf_test_do_mult(TEST_T * vals, const uint32_t tsize) {
    uint64_t start, end;

    for (uint32_t i = 0; i < tsize; ++i) {
        volatile TEST_T sink = do_mult<TEST_T, MULT>(vals[i]);
        (void)(sink);
    }
    start = timers::get_cycles();
    for (uint32_t i = 0; i < tsize; ++i) {
        volatile TEST_T sink = do_mult<TEST_T, MULT>(vals[i]);
        (void)(sink);
    }
    end = timers::get_cycles();

    double res = end - start;
    res /= tsize;
    fprintf(stderr, "Do Mult\n\tCycles Per Op: %.3lf\n", res);
}


void
perf_test_do_mult_vec(__m256i * vals, const uint32_t tsize) {
    const uint32_t _tsize = tsize / sratio;

    uint64_t start, end;


    start = timers::get_cycles();
    for (uint32_t i = 0; i < _tsize; ++i) {
        volatile __m256i sink = do_mult_vector<TEST_T, MULT>(vals[0]);
        (void)(sink);
    }
    end = timers::get_cycles();

    double res = end - start;
    res /= tsize;
    fprintf(stderr, "Do Mult Vec\n\tCycles Per Op: %.3lf\n", res);
}


int
main(int argc, char ** argv) {
    PREPARE_PARSER;
    ADD_ARG("-n", false, Int, test_size, "Set n calls per thread");
    ADD_ARG("-w",
            false,
            Int,
            which_to_run,
            "0 = normal mult, 1 = do_mult, 2 = vec_mult");
    ADD_ARG("-p", false, Set, do_perf, "Set to do perf test");
    ADD_ARG("-c", false, Set, do_corr, "Set to do corr test");
    ADD_ARG("-r", false, Int, rseed, "Rand seed");
    PARSE_ARGUMENTS;

    srand(rseed);

    DIE_ASSERT(
        do_perf + do_corr,
        "Error: either -p or -c must be specified, not both nor neither\n");
    DIE_ASSERT(which_to_run < 4, "Error: unknown run specified\n");


    test_size = cmath::roundup(test_size, sratio);

    TEST_T * vals =
        (TEST_T *)aligned_alloc(CACHE_LINE_SIZE, test_size * sizeof(TEST_T));
    for (uint32_t i = 0; i < test_size; ++i) {
        vals[i] = rand();
        if (sizeof(TEST_T) == sizeof(uint64_t)) {
            vals[i] *= rand();
        }
    }


    if (do_perf) {
        if (which_to_run == 0) {
            perf_test_mult(vals, test_size);
        }
        else if (which_to_run == 1) {
            perf_test_do_mult(vals, test_size);
        }
        else if (which_to_run == 2) {
            perf_test_do_mult_vec((__m256i *)vals, test_size);
        }
        else if (which_to_run == 3) {
            perf_test_mult_vec((__m256i *)vals, test_size);
        }
    }
    else if (do_corr) {
        if (which_to_run == 0) {
            fprintf(stderr, "I trust gcc\n");
        }
        else if (which_to_run == 1) {
            corr_test_do_mult(vals, test_size);
        }
        else if (which_to_run == 2) {
            corr_test_do_mult_vec((__m256i *)vals, test_size);
        }
    }
}
