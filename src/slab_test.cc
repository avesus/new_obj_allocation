#include <util/arg.h>
#include <util/verbosity.h>

uint32_t do_perf_tests = 0;
uint32_t do_corr_tests = 0;
uint32_t test_size     = (1 << 20);
uint32_t nthread       = (32);

uint64_t          expected_allocs = 0;
uint64_t          total_allocs    = 0;
uint64_t          total_nsec      = 0;
pthread_barrier_t b;


#include <timing/thread_helper.h>
#include <timing/timers.h>


#include <allocator/slab_layout/create_slab_type.h>
#include <allocator/slab_layout/slab_manager.h>

#include <allocator/rseq/rseq_base.h>

#include <optimized/const_math.h>

//using allocator_t =
//    slab_manager<uint64_t, typename slab_type<uint64_t, 2, 1, 1, 2>::type>;
//using allocator_t = slab_manager<uint64_t, super_slab<uint64_t, 1, super_slab<uint64_t, 1, super_slab<uint64_t, 1, slab<uint64_t, 1>>>>>;
using allocator_t = slab_manager<uint64_t, super_slab<uint64_t, 1, super_slab<uint64_t, 1, slab<uint64_t, 2>>>>;
void *
corr_alloc_test(void * targ) {
    expected_allocs = allocator_t::capacity * cmath::min<uint32_t>(8, nthread);
    total_allocs    = 0;
    uint64_t sum    = 0;
    init_thread();

    allocator_t * allocator = (allocator_t *)targ;

    const uint32_t ltest_size = test_size;

    pthread_barrier_wait(&b);

    for (uint32_t i = 0; i < ltest_size; ++i) {
        if (allocator->_allocate()) {
            sum++;
        }
        // do something
    }

    __atomic_fetch_add(&total_allocs, sum, __ATOMIC_RELAXED);
    return NULL;
}

void *
corr_alloc_then_free_test(void * targ) {
    expected_allocs = test_size * nthread;
    total_allocs    = 0;
    uint64_t sum    = 0;
    init_thread();

    allocator_t * allocator = (allocator_t *)targ;


    const uint32_t ltest_size = test_size;

    pthread_barrier_wait(&b);

    for (uint32_t i = 0; i < ltest_size; ++i) {
        uint64_t ret = (uint64_t)allocator->_allocate();
        if (ret) {
            sum++;
            allocator->_free((uint64_t *)ret);
        }
        // do something
    }

    __atomic_fetch_add(&total_allocs, sum, __ATOMIC_RELAXED);
    return NULL;
}


void *
corr_batch_alloc_then_free_test(void * targ) {
    expected_allocs = test_size * nthread;
    total_allocs    = 0;
    uint64_t sum    = 0;
    init_thread();

    allocator_t * allocator = (allocator_t *)targ;


    const uint32_t ltest_size = test_size;
    const uint32_t batch_size =
        cmath::max<uint32_t>((rand() % (64 * 64 * 64) / nthread), 1);
    uint64_t * ptrs      = (uint64_t *)calloc(batch_size, sizeof(uint64_t));
    uint32_t   batch_idx = 0;


    pthread_barrier_wait(&b);

    for (uint32_t i = 0; i < ltest_size; ++i) {
        uint64_t ret = (uint64_t)allocator->_allocate();
        if (ret) {
            sum++;
            ptrs[batch_idx++] = ret;
            if (batch_idx == batch_size) {
                batch_idx = 0;
                for (uint32_t _i = 0; _i < batch_size; ++_i) {
                    allocator->_free((uint64_t *)ptrs[_i]);
                }
            }
        }
    }

    free(ptrs);
    __atomic_fetch_add(&total_allocs, sum, __ATOMIC_RELAXED);
    return NULL;
}


void *
perf_alloc_test(void * targ) {
    init_thread();

    allocator_t * allocator = (allocator_t *)targ;

    total_nsec = 0;

    const uint32_t ltest_size = test_size;

    struct timespec start_ts, end_ts;

    pthread_barrier_wait(&b);

    timers::gettime(timers::ELAPSE, &start_ts);
    for (uint32_t i = 0; i < ltest_size; ++i) {
        allocator->_allocate();
    }
    timers::gettime(timers::ELAPSE, &end_ts);

    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);
    return NULL;
}


void *
perf_alloc_then_free_test(void * targ) {
    init_thread();

    allocator_t * allocator = (allocator_t *)targ;

    total_nsec = 0;

    const uint32_t ltest_size = test_size;

    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    for (uint32_t i = 0; i < ltest_size; ++i) {
        uint64_t ret = (uint64_t)allocator->_allocate();
        if (ret) {
            allocator->_free((uint64_t *)ret);
        }
        // do something
    }
    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    return NULL;
}


void *
perf_batch_alloc_then_free_test(void * targ) {
    init_thread();

    allocator_t * allocator = (allocator_t *)targ;

    total_nsec = 0;

    const uint32_t ltest_size = test_size;
    const uint32_t batch_size =
        cmath::max<uint32_t>((rand() % (64 * 64 * 64) / nthread), 1);
    uint64_t * ptrs      = (uint64_t *)calloc(batch_size, sizeof(uint64_t));
    uint32_t   batch_idx = 0;

    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    for (uint32_t i = 0; i < ltest_size; ++i) {
        uint64_t ret = (uint64_t)allocator->_allocate();
        if (ret) {
            ptrs[batch_idx++] = ret;
            if (batch_idx == batch_size) {
                batch_idx = 0;
                for (uint32_t _i = 0; _i < batch_size; _i++) {
                    allocator->_free((uint64_t *)ptrs[_i]);
                }
            }
        }
    }
    timers::gettime(timers::ELAPSE, &end_ts);

    free(ptrs);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);


    return NULL;
}


const uint32_t nperf_functions                    = 3;
void * (*perf_functions[nperf_functions])(void *) = {
    &perf_alloc_test,
    &perf_alloc_then_free_test,
    &perf_batch_alloc_then_free_test
};
static const char * perf_fnames[nperf_functions]{
    "perf_alloc_test",
    "perf_alloc_then_free_test",
    "perf_batch_alloc_then_free_test"
};


const uint32_t ncorr_functions                    = 3;
void * (*corr_functions[ncorr_functions])(void *) = {
    &corr_alloc_test,
    &corr_alloc_then_free_test,
    &corr_batch_alloc_then_free_test
};

static const char * corr_fnames[ncorr_functions]{
    "corr_alloc_test",
    "corr_alloc_then_free_test",
    "corr_batch_alloc_then_free_test"
};


int
main(int argc, char ** argv) {
    PREPARE_PARSER;
    ADD_ARG("-t", "--threads", false, Int, nthread, "Set nthreads");
    ADD_ARG("-n", false, Int, test_size, "Set n calls per thread");
    ADD_ARG("-p",
            "--perf",
            false,
            Set,
            do_perf_tests,
            "Set to do performance test");
    ADD_ARG("-c",
            "--corr",
            false,
            Set,
            do_corr_tests,
            "Set to do correctness test");
    PARSE_ARGUMENTS;

    ERROR_ASSERT(!pthread_barrier_init(&b, NULL, nthread));

    DIE_ASSERT(do_perf_tests + do_corr_tests,
               "Neither perf for correctness test specified\n");

    allocator_t allocator;

    thelp::thelper th;
    if (do_perf_tests) {
        for (uint32_t i = 0; i < nperf_functions; ++i) {
            allocator.reset();

            th.spawn_n(nthread,
                       perf_functions[i],
                       thelp::pin_policy::FIRST_N,
                       (void *)(&allocator),
                       0);
            th.join_all();
            fprintf(stderr,
                    "%s [nthread = %d, calls per thread = %d]\n"
                    "nanoseconds per operation  : %lu\n",
                    perf_fnames[i],
                    nthread,
                    test_size,
                    total_nsec / (nthread * test_size));
        }
    }
    if (do_corr_tests) {
        for (uint32_t i = 0; i < ncorr_functions; ++i) {
            allocator.reset();

            th.spawn_n(nthread,
                       corr_functions[i],
                       thelp::pin_policy::FIRST_N,
                       (void *)(&allocator),
                       0);
            th.join_all();
            fprintf(stderr,
                    "%s [nthread = %d, calls per thread = %d]\n"
                    "Expected           : %lu\n"
                    "Received           : %lu\n",
                    corr_fnames[i],
                    nthread,
                    test_size,
                    expected_allocs,
                    total_allocs);
            if (total_allocs != expected_allocs) {
                fprintf(stderr,
                        "ERROR [ %lu != %lu ]\n",
                        total_allocs,
                        expected_allocs);
            }
            else {
                fprintf(stderr, "PASSED\n");
            }
        }
    }
}
