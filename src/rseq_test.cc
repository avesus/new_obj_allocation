#include <util/arg.h>
#include <util/verbosity.h>

#include <timing/stats.h>
#include <timing/thread_helper.h>
#include <timing/timers.h>

#include <allocator/rseq/rseq_base.h>
#include <optimized/const_math.h>

#include <assert.h>

#define VDIF  72
#define liter 64

#define BITWISE_FUNC  do_restarting_xor
#define ACQ_LOCK_FUNC do_restarting_acquire_lock

#define BITSET_FUNC   restarting_set_bit_or
#define BITUNSET_FUNC restarting_unset_bit
#define IDXSET_FUNC   do_restarting_2level_set_idx
//////////////////////////////////////////////////////////////////////
// Just for testing whatever rseq function I'm currently working on for race
// conditions / performance
uint32_t iter      = 0;
uint32_t test_size = (1 << 20);
uint32_t nthread   = (32);
uint32_t trials    = 1;

uint32_t MIN_IDX = 0;
uint32_t MAX_IDX = 5;

int64_t  expected   = 0;
uint64_t total_nsec = 0;
uint64_t total_sum  = 0;

__thread uint32_t sum = 0;


pthread_barrier_t b;

uint32_t inline __attribute__((always_inline))
do_restarting_2level_set_idx(uint64_t * const v, const uint32_t start_cpu) {
    if (v[0] != (~(0UL))) {
        const uint32_t ret = restarting_2level_set_idx(v, start_cpu);
        if (__builtin_expect(ret < 4096, 1)) {
            return 0;
        }
        else if (__builtin_expect(ret == 4097, 0)) {
            return _RSEQ_MIGRATED;
        }
    }
    return _RSEQ_OTHER_FAILURE;
}


uint32_t inline __attribute__((always_inline))
do_restarting_reclaim_free_slabs(uint64_t * const v,
                                 uint64_t * const f,
                                 const uint32_t   start_cpu) {
    for (uint32_t _i = 0; _i < liter; ++_i) {
        if (v[_i] == 0 && f[_i]) {
            const uint64_t ret =
                restarting_reclaim_free_slabs(v + _i, f, start_cpu);
            if (__builtin_expect(ret != 0, 1)) {
                __atomic_fetch_xor(f + _i, ret, __ATOMIC_RELAXED);
                return _RSEQ_SUCCESS;
            }
            else {
                return _RSEQ_MIGRATED;
            }
        }
    }
    return _RSEQ_OTHER_FAILURE;
}


uint32_t inline __attribute__((always_inline))
do_restarting_set_bit(uint64_t * const v,
                      const uint32_t   bit,
                      const uint32_t   start_cpu) {
    for (uint32_t _i = 0; _i < liter; ++_i) {
        if (v[_i] != (~(0UL))) {
            const uint32_t ret = restarting_set_bit(v + _i, bit, start_cpu);
            if (__builtin_expect(ret == _RSEQ_SUCCESS, 1)) {
                return ret;
            }
            else if (__builtin_expect(ret == _RSEQ_MIGRATED, 0)) {
                return _RSEQ_MIGRATED;
            }
        }
    }
    return _RSEQ_OTHER_FAILURE;
}

uint32_t inline __attribute__((always_inline))
do_restarting_set_bit_or(uint64_t * const v,
                           const uint32_t   bit,
                           const uint32_t   start_cpu) {
    for (uint32_t _i = 0; _i < liter; ++_i) {
        if (v[_i] != (~(0UL))) {
            return restarting_set_bit_or(v + _i, bit, start_cpu);
        }
    }
    return _RSEQ_OTHER_FAILURE;
}



uint32_t inline __attribute__((always_inline))
do_restarting_unset_bit(uint64_t * const v,
                        const uint32_t   bit,
                        const uint32_t   start_cpu) {
    for (uint32_t _i = 0; _i < liter; ++_i) {
        if (v[_i]) {
            const uint32_t ret = restarting_unset_bit(v + _i, bit, start_cpu);
            if (__builtin_expect(ret == _RSEQ_SUCCESS, 1)) {
                return ret;
            }
            else if (__builtin_expect(ret == _RSEQ_MIGRATED, 0)) {
                return _RSEQ_MIGRATED;
            }
        }
    }
    return _RSEQ_OTHER_FAILURE;
}




uint32_t inline __attribute__((always_inline))
do_restarting_xor(uint64_t * const v,
                  const uint64_t   mask,
                  const uint32_t   start_cpu) {
    return restarting_xor(v, mask, start_cpu);
}

uint32_t inline __attribute__((always_inline))
do_restarting_or(uint64_t * const v,
                 const uint64_t   mask,
                 const uint32_t   start_cpu) {
    return restarting_or(v, mask, start_cpu);
}

uint32_t inline __attribute__((always_inline))
do_restarting_and(uint64_t * const v,
                  const uint64_t   mask,
                  const uint32_t   start_cpu) {
    return restarting_and(v, mask, start_cpu);
}

uint32_t inline __attribute__((always_inline))
do_restarting_acquire_lock(uint64_t * const v, const uint32_t start_cpu) {
    if (*v == 0) {
        return restarting_acquire_lock(v, start_cpu);
    }
    return _RSEQ_OTHER_FAILURE;
}

// this is really just a performance test
void *
restarting_bitwise_ops_test(void * targ) {
    expected   = -1;
    sum        = 0;
    total_sum  = 0;
    total_nsec = 0;
    init_thread();
    uint64_t * v = (uint64_t *)targ;

    const uint32_t  ltest_size = test_size;
    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    for (uint32_t i = 0; i < ltest_size; ++i) {
        uint32_t ret;
        do {
            const uint32_t start_cpu = get_start_cpu();
            ret = BITWISE_FUNC(v + VDIF * start_cpu, i, start_cpu);
        } while (__builtin_expect(ret == _RSEQ_MIGRATED, 0));
    }

    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);
    return NULL;
}


void *
restarting_acq_lock_test(void * targ) {
    expected   = test_size * nthread;
    total_sum  = 0;
    total_nsec = 0;
    init_thread();
    uint64_t * v        = (uint64_t *)targ;
    uint64_t * counters = v + NPROCS * VDIF;

    const uint32_t  ltest_size = test_size;
    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    for (uint32_t i = 0; i < ltest_size; ++i) {
        volatile uint32_t ret;
        do {
            const uint32_t start_cpu = get_start_cpu();
            do {
                ret = ACQ_LOCK_FUNC(v + VDIF * start_cpu, start_cpu);
                if (ret == _RSEQ_SUCCESS) {
                    ++counters[VDIF * start_cpu];
                    v[VDIF * start_cpu] = 0;
                }
            } while (ret == _RSEQ_OTHER_FAILURE);
        } while (__builtin_expect(ret == _RSEQ_MIGRATED, 0));
    }


    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    pthread_barrier_wait(&b);
    uint64_t local_sum = 0;
    for (uint32_t i = 0; i < NPROCS; ++i) {
        local_sum += counters[VDIF * i];
    }
    // this is atomic on x86_64 (either way they should all compute the same
    // value)
    total_sum = local_sum;
    return NULL;
}


void *
restarting_set_bit_test(void * targ) {


    sum        = 0;
    total_sum  = 0;
    total_nsec = 0;
    init_thread();
    uint64_t * v = (uint64_t *)targ;

    const uint32_t  ltest_size = test_size;
    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    for (uint32_t i = 0; i < ltest_size; ++i) {
        uint32_t ret;
        do {
            const uint32_t start_cpu = get_start_cpu();
            // if unset test v = -1
            ret = BITSET_FUNC(v + VDIF * start_cpu, i, start_cpu);
        } while (__builtin_expect(ret == _RSEQ_MIGRATED, 0));
    }

    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    __atomic_fetch_add(&total_sum, sum, __ATOMIC_RELAXED);
    pthread_barrier_wait(&b);
    uint64_t local_sum = 0;
    for (uint32_t i = 0; i < NPROCS * VDIF; ++i) {
        local_sum += bits::bitcount<uint64_t>(v[i]);
    }
    expected = local_sum;
    return NULL;
}


void *
restarting_unset_bit_test(void * targ) {


    sum        = 0;
    total_sum  = 0;
    total_nsec = 0;
    init_thread();
    uint64_t * v = (uint64_t *)targ;
    for (uint32_t i = 0; i < 2 * VDIF * NPROCS; ++i) {
        v[i] = (~(0UL));
    }

    const uint32_t  ltest_size = test_size;
    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    for (uint32_t i = 0; i < ltest_size; ++i) {
        uint32_t ret;
        do {
            const uint32_t start_cpu = get_start_cpu();
            // if unset test v = -1
            ret = BITUNSET_FUNC(v + VDIF * start_cpu, i % 64, start_cpu);
        } while (__builtin_expect(ret == _RSEQ_MIGRATED, 0));
    }

    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    __atomic_fetch_add(&total_sum, sum, __ATOMIC_RELAXED);

    pthread_barrier_wait(&b);
    uint64_t local_sum = 0;
    for (uint32_t i = 0; i < NPROCS * VDIF; ++i) {
        local_sum += 64 - bits::bitcount<uint64_t>(v[i]);
    }
    expected = local_sum;
    return NULL;
}


void *
restarting_set_idx_test(void * targ) {
    _tlv_rand                = rand() % 64;
    const uint32_t min_cores = cmath::min<uint32_t>(NPROCS, nthread);
    expected =
        cmath::min<uint32_t>(nthread * test_size, liter * min_cores * 64);
    sum        = 0;
    total_sum  = 0;
    total_nsec = 0;
    init_thread();
    uint64_t * v = (uint64_t *)targ;

    const uint32_t  ltest_size = test_size;
    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    for (uint32_t i = 0; i < ltest_size; ++i) {
        uint32_t ret;
        do {
            const uint32_t start_cpu = get_start_cpu();
            // if unset test v = -1
            ret = IDXSET_FUNC(v + VDIF * start_cpu, start_cpu);
            if (ret < _RSEQ_OTHER_FAILURE) {
                sum++;
            }
        } while (__builtin_expect(ret == _RSEQ_MIGRATED, 0));
    }

    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    pthread_barrier_wait(&b);
    uint64_t local_sum = 0;
    for (uint32_t i = 0; i < NPROCS * VDIF; ++i) {
        if(i % VDIF) {
        local_sum += bits::bitcount<uint64_t>(v[i]);
        }
    }
    expected = local_sum;
    __atomic_fetch_add(&total_sum, sum, __ATOMIC_RELAXED);
    return NULL;
}

#define N_FUNCS 5
void * (*test_funcs[N_FUNCS])(void *) = { &restarting_bitwise_ops_test,
                                          &restarting_acq_lock_test,
                                          &restarting_set_bit_test,
                                          &restarting_unset_bit_test,
                                          &restarting_set_idx_test };

static const char * test_fnames[N_FUNCS]{ "restarting_bitwise_ops_test",
                                          "restarting_acq_lock_test",
                                          "restarting_set_bit_test",
                                          "restarting_unset_bit_test",
                                          "restarting_set_idx_test" };


int
main(int argc, char ** argv) {
    PREPARE_PARSER;
    ADD_ARG("-t", "--threads", false, Int, nthread, "Set nthreads");
    ADD_ARG("-n", false, Int, test_size, "Set n calls per thread");
    ADD_ARG("-s", false, Int, trials, "Set n calls per thread");
    ADD_ARG("-i", false, Int, iter, "Set number of iterations");
    ADD_ARG("-m", "--min", false, Int, MIN_IDX, "Set number of iterations");
    ADD_ARG("-x", "--max", false, Int, MAX_IDX, "Set number of iterations");
    PARSE_ARGUMENTS;

    ERROR_ASSERT(!pthread_barrier_init(&b, NULL, nthread));

    uint64_t * v = (uint64_t *)aligned_alloc(64, 2 * 64 * VDIF);
    double *   times[N_FUNCS];
    for (uint32_t i = 0; i < N_FUNCS; ++i) {
        times[i] = (double *)calloc(trials, sizeof(uint64_t));
    }

    thelp::thelper th;

    for (uint32_t f_idx = MIN_IDX; f_idx < MAX_IDX; ++f_idx) {
        for (uint32_t i = 0; i < trials; ++i) {
            fprintf(stderr, "Running: %s - ", test_fnames[f_idx]);
            memset(v, 0, 2 * 8 * VDIF * NPROCS);

            th.spawn_n(nthread,
                       test_funcs[f_idx],
                       thelp::pin_policy::FIRST_N,
                       (void *)v,
                       0);
            th.join_all();
            times[f_idx][i] = ((double)total_nsec) / (nthread * test_size);
            if (expected != (-1)) {
                if ((uint64_t)expected != total_sum) {
                    fprintf(stderr,
                            "ERROR [%lu != %lu]\n",
                            total_sum,
                            expected);
                }
                else {
                    fprintf(stderr,
                            "PASSED [%lu == %lu]\n",
                            total_sum,
                            expected);
                }
            }
            else {
                fprintf(stderr, "PASSED\n");
            }

            total_sum  = 0;
            total_nsec = 0;
        }
    }

    free(v);
    for (uint32_t i = MIN_IDX; i < MAX_IDX; ++i) {
        fprintf(stderr, "\nTimes: %s\n", test_fnames[i]);
        stats::stats_out so;
        so.get_stats(times[i], trials);
        so.units = timers::time_units::NSEC;
        so.print(stats::human_readable);
        free(times[i]);
    }
}
