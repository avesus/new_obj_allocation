#include <util/arg.h>
#include <util/verbosity.h>

#include <timing/thread_helper.h>
#include <timing/timers.h>
#include <timing/stats.h>

#include <allocator/rseq/rseq_base.h>
#include <optimized/const_math.h>

#include <assert.h>

template<uint32_t i>
using find_and_set = uint64_t (*)(uint64_t * const, const uint32_t);

using find_and_set_base = uint64_t (*)(uint64_t * const, const uint32_t);


static const find_and_set_base fas_funcs[64] = {
    &restarting_set_idx3<0>,  &restarting_set_idx3<1>,
    &restarting_set_idx3<2>,  &restarting_set_idx3<3>,
    &restarting_set_idx3<4>,  &restarting_set_idx3<5>,
    &restarting_set_idx3<6>,  &restarting_set_idx3<7>,
    &restarting_set_idx3<8>,  &restarting_set_idx3<9>,
    &restarting_set_idx3<10>, &restarting_set_idx3<11>,
    &restarting_set_idx3<12>, &restarting_set_idx3<13>,
    &restarting_set_idx3<14>, &restarting_set_idx3<15>,
    &restarting_set_idx3<16>, &restarting_set_idx3<17>,
    &restarting_set_idx3<18>, &restarting_set_idx3<19>,
    &restarting_set_idx3<20>, &restarting_set_idx3<21>,
    &restarting_set_idx3<22>, &restarting_set_idx3<23>,
    &restarting_set_idx3<24>, &restarting_set_idx3<25>,
    &restarting_set_idx3<26>, &restarting_set_idx3<27>,
    &restarting_set_idx3<28>, &restarting_set_idx3<29>,
    &restarting_set_idx3<30>, &restarting_set_idx3<31>,
    &restarting_set_idx3<32>, &restarting_set_idx3<33>,
    &restarting_set_idx3<34>, &restarting_set_idx3<35>,
    &restarting_set_idx3<36>, &restarting_set_idx3<37>,
    &restarting_set_idx3<38>, &restarting_set_idx3<39>,
    &restarting_set_idx3<40>, &restarting_set_idx3<41>,
    &restarting_set_idx3<42>, &restarting_set_idx3<43>,
    &restarting_set_idx3<44>, &restarting_set_idx3<45>,
    &restarting_set_idx3<46>, &restarting_set_idx3<47>,
    &restarting_set_idx3<48>, &restarting_set_idx3<49>,
    &restarting_set_idx3<50>, &restarting_set_idx3<51>,
    &restarting_set_idx3<52>, &restarting_set_idx3<53>,
    &restarting_set_idx3<54>, &restarting_set_idx3<55>,
    &restarting_set_idx3<56>, &restarting_set_idx3<57>,
    &restarting_set_idx3<58>, &restarting_set_idx3<59>,
    &restarting_set_idx3<60>, &restarting_set_idx3<61>,
    &restarting_set_idx3<62>, &restarting_set_idx3<63>
};

//////////////////////////////////////////////////////////////////////
// Just for testing whatever rseq function I'm currently working on for race
// conditions / performance
uint32_t iter      = 0;
uint32_t test_size = (1 << 20);
uint32_t nthread   = (32);
uint32_t trials    = 1;

uint64_t total_nsec = 0;

uint64_t          true_sum = 0;
__thread uint32_t sum      = 0;

static __thread uint64_t r;

#define VDIF  512
#define liter 512
pthread_barrier_t b;

uint32_t inline __attribute__((always_inline))
do_set(uint64_t * v, const uint32_t start_cpu) {
    for (uint32_t _i = 0; _i < liter; ++_i) {
        if (v[_i] != (~(0UL))) {
            const uint32_t ret = restarting_set_idx(v + _i, start_cpu);
            if (__builtin_expect(ret < 64, 1)) {
                return ret;
            }
            else if (__builtin_expect(ret == 65, 0)) {
                return 65;
            }
        }
    }
    return 64;
}

uint32_t inline __attribute__((always_inline))
do_set4(uint64_t * v, const uint32_t start_cpu) {
    for (uint32_t _i = 0; _i < liter; ++_i) {
        if (v[_i] != (~(0UL))) {
            const uint32_t ret = restarting_set_idx4(v + _i, start_cpu);
            if (__builtin_expect(ret < 64, 1)) {
                return ret;
            }
            else if (__builtin_expect(ret == 65, 0)) {
                return 65;
            }
        }
    }
    return 64;
}

uint32_t inline __attribute__((always_inline))
do_set2(uint64_t * v, const uint32_t start_cpu) {
    for (uint32_t _i = 0; _i < liter; ++_i) {
        if (v[_i] != (~(0UL))) {
            const uint32_t ret = restarting_set_idx2(v + _i, start_cpu, r);
            if (__builtin_expect(ret < 64, 1)) {
                return ret;
            }
            else if (__builtin_expect(ret == 65, 0)) {
                return 65;
            }
        }
    }
    return 64;
}


uint32_t inline __attribute__((always_inline))
do_set3(uint64_t * v, const uint32_t start_cpu) {
    for (uint32_t _i = 0; _i < liter; ++_i) {
        if (v[_i] != (~(0UL))) {
            if(r > 63) {
                __builtin_unreachable();
            }
            const uint32_t ret = fas_funcs[r](v + _i, start_cpu);
            if (__builtin_expect(ret < 64, 1)) {
                return ret;
            }
            else if (__builtin_expect(ret == 65, 0)) {
                return 65;
            }
        }
    }
    return 64;
}


uint32_t inline __attribute__((always_inline))
do_normal_set(uint64_t * v, const uint32_t start_cpu) {
    for (uint32_t _i = 0; _i < liter; ++_i) {
        if (v[_i] != (~(0UL))) {
            const uint32_t idx = _tzcnt_u64(~(v[_i]));
            if (__builtin_expect(idx < 64, 1)) {
                if (__builtin_expect(
                        or_if_unset(v + _i, ((1UL) << idx), start_cpu),
                        0)) {
                    return 65;
                }
                return idx;
            }
        }
    }
    return 64;
}


void *
restarting_set_idx_test(void * targ) {
    true_sum   = 0;
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
            ret                      = do_set(v + VDIF * start_cpu, start_cpu);
        } while (__builtin_expect(ret == 65, 0));
        sum += __builtin_expect(ret < 64, 1) ? 1 : 0;
    }
    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    __atomic_fetch_add(&true_sum, sum, __ATOMIC_RELAXED);
    return NULL;
}

void *
restarting_set_idx_test4(void * targ) {
    true_sum   = 0;
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
            ret                      = do_set4(v + VDIF * start_cpu, start_cpu);
        } while (__builtin_expect(ret == 65, 0));
        sum += __builtin_expect(ret < 64, 1) ? 1 : 0;
    }
    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    __atomic_fetch_add(&true_sum, sum, __ATOMIC_RELAXED);
    return NULL;
}

void *
restarting_set_idx_test2(void * targ) {
    true_sum   = 0;
    total_nsec = 0;
    r          = rand() % 64;
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
            ret                      = do_set2(v + VDIF * start_cpu, start_cpu);
        } while (__builtin_expect(ret == 65, 0));
        sum += __builtin_expect(ret < 64, 1) ? 1 : 0;
    }
    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    __atomic_fetch_add(&true_sum, sum, __ATOMIC_RELAXED);
    return NULL;
}


void *
restarting_set_idx_test3(void * targ) {
    true_sum   = 0;
    total_nsec = 0;
    r          = rand() % 64;
    __builtin_prefetch((void *)fas_funcs[r]);
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
            ret                      = do_set3(v + VDIF * start_cpu, start_cpu);
        } while (__builtin_expect(ret == 65, 0));
        sum += __builtin_expect(ret < 64, 1) ? 1 : 0;
    }
    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    __atomic_fetch_add(&true_sum, sum, __ATOMIC_RELAXED);
    return NULL;
}


void *
normal_set_idx_test(void * targ) {
    true_sum   = 0;
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
            ret = do_normal_set(v + start_cpu * VDIF, start_cpu);
        } while (__builtin_expect(ret == 65, 0));
        sum += __builtin_expect(ret < 64, 1) ? 1 : 0;
    }
    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    __atomic_fetch_add(&true_sum, sum, __ATOMIC_RELAXED);
    return NULL;
}


int
main(int argc, char ** argv) {
    PREPARE_PARSER;
    ADD_ARG("-t", "--threads", false, Int, nthread, "Set nthreads");
    ADD_ARG("-n", false, Int, test_size, "Set n calls per thread");
    ADD_ARG("-s", false, Int, trials, "Set n calls per thread");
    ADD_ARG("-i", false, Int, iter, "Set number of iterations");
    PARSE_ARGUMENTS;

    ERROR_ASSERT(!pthread_barrier_init(&b, NULL, nthread));

    uint64_t * v     = (uint64_t *)aligned_alloc(64, 64 * VDIF);
    uint64_t * times = (uint64_t *)calloc(trials, sizeof(uint64_t));

    thelp::thelper th;
    for (uint32_t i = 0; i < trials; i++) {
        memset(v, 0, 64 * VDIF);
        if (iter == 0) {
            th.spawn_n(nthread,
                       &normal_set_idx_test,
                       thelp::pin_policy::NONE,
                       (void *)v,
                       0);
        }
        else if (iter == 1) {
            th.spawn_n(nthread,
                       &restarting_set_idx_test,
                       thelp::pin_policy::NONE,
                       (void *)v,
                       0);
        }

        else if (iter == 2) {
            th.spawn_n(nthread,
                       &restarting_set_idx_test2,
                       thelp::pin_policy::NONE,
                       (void *)v,
                       0);
        }
        else if (iter == 3) {
            th.spawn_n(nthread,
                       &restarting_set_idx_test3,
                       thelp::pin_policy::NONE,
                       (void *)v,
                       0);
        }
        else if (iter == 4) {
            th.spawn_n(nthread,
                       &restarting_set_idx_test4,
                       thelp::pin_policy::NONE,
                       (void *)v,
                       0);
        }
        th.join_all();
        times[i] = total_nsec / (nthread * test_size);
        /*        fprintf(stderr, "True Sum: %lu\n", true_sum);

        fprintf(stderr,
                "[nthread = %d, calls per thread = %d]\n"
                "nanoseconds per operation  : %.4lf\n",
                nthread,
                test_size,
                ((double)total_nsec) / (nthread * test_size));*/
    }

    stats::stats_out so;
    so.get_stats(times, trials);
    so.units = timers::NSEC;
    so.print(stats::human_readable);
}
