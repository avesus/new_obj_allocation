#include <util/arg.h>
#include <util/verbosity.h>

#include <timing/thread_helper.h>
#include <timing/timers.h>

#include <allocator/rseq/rseq_base.h>
#include <optimized/const_math.h>

#include <assert.h>

uint32_t iter      = 0;
uint32_t test_size = (1 << 20);
uint32_t nthread   = (32);

uint64_t total_nsec = 0;

uint64_t          true_sum = 0;
__thread uint32_t sum      = 0;

#define VDIF  8
#define liter 2
pthread_barrier_t b;

uint32_t inline __attribute__((always_inline))
do_set(uint64_t * v, const uint32_t start_cpu) {
    for (uint32_t _i = 0; _i < liter; ++_i) {
        if (v[_i]) {
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
do_normal_set(uint64_t * v, const uint32_t start_cpu) {
    for (uint32_t _i = 0; _i < liter; ++_i) {
        const uint32_t idx = _tzcnt_u64(~(v[_i]));
        if (__builtin_expect(idx < 64, 1)) {
            if (__builtin_expect(or_if_unset(v + _i, ((1UL) << idx), start_cpu),
                                 0)) {
                return 65;
            }
            return idx;
        }
    }
    return 64;
}


void *
restarting_set_idx_test(void * targ) {
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
normal_set_idx_test(void * targ) {
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
    ADD_ARG("-i", false, Set, iter, "Set number of iterations");
    PARSE_ARGUMENTS;

    ERROR_ASSERT(!pthread_barrier_init(&b, NULL, nthread));

    uint64_t * v = (uint64_t *)aligned_alloc(64, 64 * VDIF);
    memset(v, 0, 64 * VDIF);

    thelp::thelper th;
    if(iter) {
    th.spawn_n(nthread,
               &normal_set_idx_test,
               thelp::pin_policy::NONE,
               (void *)v,
               0);
    }
    else {
    th.spawn_n(nthread,
               &restarting_set_idx_test,
               thelp::pin_policy::NONE,
               (void *)v,
               0);
    }
    th.join_all();
    fprintf(stderr, "True Sum: %lu\n", true_sum);
    fprintf(stderr,
            "[nthread = %d, calls per thread = %d]\n"
            "nanoseconds per operation  : %lu\n",
            nthread,
            test_size,
            total_nsec / (nthread * test_size));
}
