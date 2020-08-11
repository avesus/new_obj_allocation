#ifndef _STATS_H_
#define _STATS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include <timing/timers.h>


namespace stats {

static constexpr bool human_readable = true;
static constexpr bool csv            = false;

struct stats_out {


    uint64_t median;
    uint64_t mean;
    uint64_t max;
    uint64_t min;

    uint64_t p99;
    uint64_t p95;
    uint64_t p90;

    timers::time_units units;

    void print(bool format, FILE * outfile = stderr);

    void print_csv(FILE * outfile);
    void print_hr(FILE * outfile);

    void get_stats(uint64_t * data, uint32_t n);
    void get_stats(std::vector<uint64_t> & data);

    void sorted_array_to_stats(uint64_t * data, uint32_t n);
};

}  // namespace stats

#endif
