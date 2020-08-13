#include <util/arg.h>
#include <util/verbosity.h>

#include <timing/thread_helper.h>
#include <timing/timers.h>

#include <allocator/rseq/rseq_base.h>
#include <optimized/const_math.h>

#include <assert.h>

uint32_t test_size = (1 << 20);
uint32_t nthread   = (32);
uint32_t which_to_run = 0;

uint64_t total_nsec = 0;

__thread uint64_t tlv_rand;

pthread_barrier_t b;


void *
tlv_test(void * targ) {
    tlv_rand = rand() * rand();
    const uint32_t  ltest_size = test_size;
    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    
    for (uint32_t i = 0; i < ltest_size; ++i) {
        volatile uint64_t sink = tlv_rand;
    }
    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    return NULL;
}

void *
pthread_self_test(void * targ) {
    const uint32_t  ltest_size = test_size;
    struct timespec start_ts, end_ts;
    pthread_barrier_wait(&b);
    timers::gettime(timers::ELAPSE, &start_ts);
    
    for (uint32_t i = 0; i < ltest_size; ++i) {
        volatile uint64_t sink = pthread_self();
    }
    timers::gettime(timers::ELAPSE, &end_ts);
    __atomic_fetch_add(&total_nsec,
                       timers::ts_to_ns(&end_ts) - timers::ts_to_ns(&start_ts),
                       __ATOMIC_RELAXED);

    return NULL;
}

int
main(int argc, char ** argv) {
    PREPARE_PARSER;
    ADD_ARG("-t", "--threads", false, Int, nthread, "Set nthreads");
    ADD_ARG("-n", false, Int, test_size, "Set n calls per thread");
    ADD_ARG("-r", false, Set, which_to_run, "which to run (set to run tlv test)");
    PARSE_ARGUMENTS;

    ERROR_ASSERT(!pthread_barrier_init(&b, NULL, nthread));


    thelp::thelper th;
    if(which_to_run) {
    th.spawn_n(nthread,
               &tlv_test,
               thelp::pin_policy::NONE,
               NULL,
               0);
    }
    else {
    th.spawn_n(nthread,
               &pthread_self_test,
               thelp::pin_policy::NONE,
               NULL,
               0);
    }
    th.join_all();

    fprintf(stderr,
            "[nthread = %d, calls per thread = %d]\n"
            "nanoseconds per operation  : %.4f\n",
            nthread,
            test_size,
            ((double)total_nsec) / (nthread * test_size));
}
