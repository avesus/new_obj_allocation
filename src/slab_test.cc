#include <util/arg.h>
#include <util/verbosity.h>


uint32_t do_perf_tests     = 0;
uint32_t do_corr_tests     = 0;
uint32_t do_baseline_tests = 0;

uint32_t lower_bound = 0;
uint32_t upper_bound = ~0;

uint32_t test_size = (1 << 20);
uint32_t nthread   = (32);

uint64_t          expected_allocs = 0;
uint64_t          total_allocs    = 0;
uint64_t          total_nsec      = 0;
pthread_barrier_t b;

__thread uint64_t tlv_incr = 0;

#define NBYTES 8
//#define GLIBC_ALLOC
#ifdef GLIBC_ALLOC
    #define ALLOCATE malloc(NBYTES)
    #define FREE     free
#else
    #define ALLOCATE allocator->_allocate()
    #define FREE     allocator->_free
#endif


#include <timing/thread_helper.h>
#include <timing/timers.h>


#include <allocator/rseq/rseq_base.h>
#include <allocator/slab_layout/create_slab_type.h>
#include <allocator/slab_layout/slab_manager.h>

#include <optimized/const_math.h>

typedef struct nbytes {
    uint8_t filler[NBYTES];
} nbytes_t;

// using allocator_t =
//    slab_manager<uint64_t, typename slab_type<uint64_t, 2, 1, 1, 2>::type>;
// using allocator_t = slab_manager<uint64_t, super_slab<uint64_t, 1,
// super_slab<uint64_t, 1, super_slab<uint64_t, 1, slab<uint64_t, 1>>>>>;
using allocator_t = slab_manager<
    nbytes_t,
    super_slab<nbytes_t, super_slab<nbytes_t, slab<nbytes_t>, 1>, 1>>;
// using allocator_t = slab_manager<uint64_t, super_slab<uint64_t, 1,
// super_slab<uint64_t, 1, slab<uint64_t, 2>>>>;
void *
corr_alloc_test(void * targ) {
    expected_allocs = cmath::min<uint32_t>(
        test_size * nthread,
        allocator_t::capacity * cmath::min<uint32_t>(NPROCS, nthread));
    total_allocs = 0;
    uint64_t sum = 0;
    _tlv_rand    = rand() % 64;
    init_thread();

    allocator_t * allocator = (allocator_t *)targ;

    const uint32_t ltest_size = test_size;

    pthread_barrier_wait(&b);

    for (uint32_t i = 0; i < ltest_size; ++i) {
        if (ALLOCATE) {
            sum++;
        }
        // do something
    }

    __atomic_fetch_add(&total_allocs, sum, __ATOMIC_RELAXED);

    (void)(allocator);
    return NULL;
}

void *
corr_alloc_then_free_test(void * targ) {
    expected_allocs = test_size * nthread;
    total_allocs    = 0;
    uint64_t sum    = 0;
    _tlv_rand       = rand() % 64;
    init_thread();

    allocator_t * allocator = (allocator_t *)targ;


    const uint32_t ltest_size = test_size;

    pthread_barrier_wait(&b);

    for (uint32_t i = 0; i < ltest_size; ++i) {
        uint64_t ret = (uint64_t)ALLOCATE;
        if (ret) {
            sum++;
            FREE((nbytes_t *)ret);
        }
        // do something
    }

    __atomic_fetch_add(&total_allocs, sum, __ATOMIC_RELAXED);
    (void)(allocator);
    return NULL;
}


void *
corr_alloc_all_free_all_alloc_all_test(void * targ) {
    expected_allocs =
        cmath::min<uint32_t>(NPROCS, nthread) * allocator_t::capacity;
    total_allocs = 0;
    uint64_t sum = 0;
    init_thread();

    allocator_t * allocator = (allocator_t *)targ;

    uint64_t ** ptrs = (uint64_t **)calloc(expected_allocs, sizeof(uint64_t *));
    uint32_t    p_idx = 0;

    pthread_barrier_wait(&b);
    uint64_t * ptr;
    while (1) {
        ptr = (uint64_t *)ALLOCATE;
        if (ptr == NULL) {
            break;
        }
        ptrs[p_idx++] = ptr;
    }
    for (uint32_t i = 0; i < p_idx; ++i) {
        FREE((nbytes_t *)ptrs[i]);
    }
    pthread_barrier_wait(&b);
    while (1) {
        ptr = (uint64_t *)ALLOCATE;
        if (ptr == NULL) {
            break;
        }
        sum++;
    }

    free(ptrs);
    __atomic_fetch_add(&total_allocs, sum, __ATOMIC_RELAXED);
    (void)(allocator);
    return NULL;
}


void *
corr_batch_alloc_then_free_test(void * targ) {
    expected_allocs = test_size * nthread;
    total_allocs    = 0;
    uint64_t sum    = 0;
    _tlv_rand       = rand() % 64;
    init_thread();

    allocator_t * allocator = (allocator_t *)targ;


    const uint32_t ltest_size = test_size;
    const uint32_t batch_size =
        cmath::max<uint32_t>((rand() % (64 * 64 * 64) / nthread), 1);
    uint64_t * ptrs      = (uint64_t *)calloc(batch_size, sizeof(uint64_t));
    uint32_t   batch_idx = 0;


    pthread_barrier_wait(&b);

    for (uint32_t i = 0; i < ltest_size; ++i) {
        uint64_t ret = (uint64_t)ALLOCATE;
        if (ret) {
            sum++;
            ptrs[batch_idx++] = ret;
            if (batch_idx == batch_size) {
                batch_idx = 0;
                for (uint32_t _i = 0; _i < batch_size; ++_i) {
                    FREE((nbytes_t *)ptrs[_i]);
                }
            }
        }
    }

    free(ptrs);
    __atomic_fetch_add(&total_allocs, sum, __ATOMIC_RELAXED);
    (void)(allocator);
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

        volatile uint64_t sink = (uint64_t)ALLOCATE;
        (void)(sink);
    }
    timers::gettime(timers::ELAPSE, &end_ts);

    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);
    (void)(allocator);
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
        uint64_t ret = (uint64_t)ALLOCATE;
        if (ret) {
            FREE((nbytes_t *)ret);
        }
        // do something
    }
    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    (void)(allocator);
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
        uint64_t ret = (uint64_t)ALLOCATE;
        if (ret) {
            ptrs[batch_idx++] = ret;
            if (batch_idx == batch_size) {
                batch_idx = 0;
                for (uint32_t _i = 0; _i < batch_size; _i++) {
                    FREE((nbytes_t *)ptrs[_i]);
                }
            }
        }
    }
    timers::gettime(timers::ELAPSE, &end_ts);

    free(ptrs);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);


    (void)(allocator);
    return NULL;
}

void *
perf_alloc_all_free_all_alloc_all_test(void * targ) {
    init_thread();

    allocator_t * allocator = (allocator_t *)targ;

    total_nsec = 0;

    uint64_t ** ptrs = (uint64_t **)calloc(
        cmath::min<uint32_t>(NPROCS, nthread) * allocator_t::capacity,
        sizeof(uint64_t *));
    uint32_t p_idx = 0;

    struct timespec start_ts, end_ts;

    pthread_barrier_wait(&b);
    uint64_t * ptr;
    while (1) {
        ptr = (uint64_t *)ALLOCATE;
        if (ptr == NULL) {
            break;
        }
        ptrs[p_idx++] = ptr;
    }
    for (uint32_t i = 0; i < p_idx; ++i) {
        FREE((nbytes_t *)ptrs[i]);
    }
    pthread_barrier_wait(&b);

    timers::gettime(timers::ELAPSE, &start_ts);
    volatile uint64_t sink;
    do {
        sink = (uint64_t)ALLOCATE;
    } while (sink);
    timers::gettime(timers::ELAPSE, &end_ts);

    free(ptrs);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    test_size =
        (cmath::min<uint32_t>(NPROCS, nthread) * allocator_t::capacity) /
        nthread;
    (void)(allocator);
    return NULL;
}


void *
baseline_tlv_incr(void * targ) {
    init_thread();

    total_nsec = 0;

    const uint32_t ltest_size = test_size;

    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    for (uint32_t i = 0; i < ltest_size; ++i) {
        volatile uint64_t sink = ++tlv_incr;
        (void)(sink);
    }
    timers::gettime(timers::ELAPSE, &end_ts);

    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);
    (void)(targ);

    return NULL;
}

void *
baseline_atomic_incr(void * targ) {
    init_thread();

    uint64_t * counter = (uint64_t *)targ;

    total_nsec = 0;

    const uint32_t ltest_size = test_size;

    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    for (uint32_t i = 0; i < ltest_size; ++i) {
        __atomic_fetch_add(counter, 1, __ATOMIC_RELAXED);
    }
    timers::gettime(timers::ELAPSE, &end_ts);

    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);
    (void)(targ);

    return NULL;
}

void *
baseline_per_core_incr(void * targ) {
    init_thread();

    uint64_t * per_core_counters = (uint64_t *)targ;

    total_nsec = 0;

    const uint32_t ltest_size = test_size;

    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    for (uint32_t i = 0; i < ltest_size; ++i) {
        uint32_t start_cpu;
        do {
            start_cpu = get_start_cpu();
        } while (BRANCH_UNLIKELY(
            _RSEQ_MIGRATED ==
            restarting_incr(per_core_counters + 8 * start_cpu, start_cpu)));
    }
    timers::gettime(timers::ELAPSE, &end_ts);

    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);


    return NULL;
}


typedef void * (*tfunc_t)(void *);

const uint32_t nperf_functions                 = 4;
tfunc_t        perf_functions[nperf_functions] = {
    &perf_alloc_test,
    &perf_alloc_then_free_test,
    &perf_batch_alloc_then_free_test,
    &perf_alloc_all_free_all_alloc_all_test
};
static const char * perf_fnames[nperf_functions]{
    "perf_alloc_test",
    "perf_alloc_then_free_test",
    "perf_batch_alloc_then_free_test",
    "perf_alloc_all_free_all_alloc_all_test"
};


const uint32_t ncorr_functions                 = 4;
tfunc_t        corr_functions[ncorr_functions] = {
    &corr_alloc_test,
    &corr_alloc_then_free_test,
    &corr_batch_alloc_then_free_test,
    &corr_alloc_all_free_all_alloc_all_test
};

static const char * corr_fnames[ncorr_functions]{
    "corr_alloc_test",
    "corr_alloc_then_free_test",
    "corr_batch_alloc_then_free_test",
    "corr_alloc_all_free_all_alloc_all_test"

};

const uint32_t nbaseline_functions                     = 3;
tfunc_t        baseline_functions[nbaseline_functions] = { &baseline_tlv_incr,
                                                    &baseline_per_core_incr,
                                                    &baseline_atomic_incr };

static const char * baseline_fnames[nbaseline_functions]{
    "baseline_tlv_incr",
    "baseline_per_core_incr",
    "baseline_atomic_incr"
};


int
main(int argc, char ** argv) {
    PREPARE_PARSER;
    ADD_ARG("-t", "--threads", false, Int, nthread, "Set nthreads");
    ADD_ARG("-n", false, Int, test_size, "Set n calls per thread");
    ADD_ARG("-l", "--lb", false, Int, lower_bound, "Lower Bound For Tests\n");
    ADD_ARG("-u", "--ub", false, Int, upper_bound, "Upper Bound For Tests\n");
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
    ADD_ARG("-b",
            "--baseline",
            false,
            Set,
            do_baseline_tests,
            "Set to do baseline test");
    PARSE_ARGUMENTS;

    ERROR_ASSERT(!pthread_barrier_init(&b, NULL, nthread));

    DIE_ASSERT((do_perf_tests + do_corr_tests + do_baseline_tests) == 1,
               "Invalid testing options specified (specify either perf, corr, "
               "or baseline)\n");

    allocator_t allocator;

    thelp::thelper th;
    if (do_perf_tests || do_baseline_tests) {
        uint32_t nrun_funcs =
            do_perf_tests ? nperf_functions : nbaseline_functions;
        const char ** run_fnames =
            (const char **)(do_perf_tests ? perf_fnames : baseline_fnames);
        tfunc_t * run_funcs =
            (tfunc_t *)(do_perf_tests ? perf_functions : baseline_functions);

        upper_bound = cmath::min<uint32_t>(nrun_funcs, upper_bound);

        void * run_arg =
            (void *)(do_perf_tests ? (void *)&allocator : (void *)allocator.m);

        for (uint32_t i = lower_bound; i < upper_bound; ++i) {
            allocator.reset();

            th.spawn_n(nthread,
                       run_funcs[i],
                       thelp::pin_policy::FIRST_N,
                       run_arg,
                       0);
            th.join_all();
            fprintf(stderr,
                    "%s [nthread = %d, calls per thread = %d]\n"
                    "nanoseconds per operation  : %.2lf\n",
                    run_fnames[i],
                    nthread,
                    test_size,
                    ((double)total_nsec) / (nthread * test_size));
        }
    }
    if (do_corr_tests) {

        upper_bound = cmath::min<uint32_t>(ncorr_functions, upper_bound);

        for (uint32_t i = lower_bound; i < upper_bound; ++i) {
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
