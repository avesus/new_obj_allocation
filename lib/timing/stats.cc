#include <timing/stats.h>

#include <util/verbosity.h>
#include <algorithm>
#include <numeric>

namespace stats {
static constexpr uint64_t sci_notation_bound = 10 * 1000 * 1000;

static const char possible_fmts[2][8] = { "%.4E", "%lu" };
static const char *
best_format(uint64_t value) {
    if (value > (sci_notation_bound)) {
        return possible_fmts[0];
    }
    return possible_fmts[1];
}

void
stats_out::print(bool format, FILE * outfile) {
    if (format == human_readable) {
        print_hr(outfile);
    }
    else {
        print_csv(outfile);
    }
}

void
stats_out::print_hr(FILE * outfile) {
    char fmt_buf[256] = "";
    sprintf(fmt_buf,
            "----------------------------------------\n"
            "Median : %s %s\n"
            "Mean   : %s %s\n"
            "Max    : %s %s\n"
            "Min    : %s %s\n"
            "P99    : %s %s\n"
            "P95    : %s %s\n"
            "P90    : %s %s\n"
            "----------------------------------------\n",
            best_format(median),
            timers::unit_to_str(units),
            best_format(mean),
            timers::unit_to_str(units),
            best_format(max),
            timers::unit_to_str(units),
            best_format(min),
            timers::unit_to_str(units),
            best_format(p99),
            timers::unit_to_str(units),
            best_format(p95),
            timers::unit_to_str(units),
            best_format(p90),
            timers::unit_to_str(units));

    fprintf(outfile, fmt_buf, median, mean, max, min, p99, p95, p90);
}

void
stats_out::print_csv(FILE * outfile) {
    fprintf(outfile,
            "median,mean,max,min,p99,p95,p90\n"
            "%lu,%lu,%lu,%lu,%lu,%lu,%lu\n",
            median,
            mean,
            max,
            min,
            p99,
            p95,
            p90);
}

void
stats_out::sorted_array_to_stats(uint64_t * data, uint32_t n) {
    if (n == 1) {
        median = data[0];
        mean   = data[0];
        max    = data[0];
        min    = data[0];
        p99    = data[0];
        p95    = data[0];
        p90    = data[0];
    }
    else {
        median =
            (n % 2) ? (data[n / 2]) : ((data[n / 2] + data[(n / 2) + 1]) / 2);
        mean = std::accumulate(data, data + n, 0) / n;
        max  = data[n - 1];
        min  = data[0];

        uint64_t p99_idx = .99 * ((double)n);
        uint64_t p95_idx = .95 * ((double)n);
        uint64_t p90_idx = .90 * ((double)n);
        p99              = data[p99_idx];
        p95              = data[p95_idx];
        p90              = data[p90_idx];
    }
}

void
stats_out::get_stats(uint64_t * data, uint32_t n) {
    if (n == 0 || data == NULL) {
        errv_print("Error: No data to collect stats on\n");
        return;
    }
    std::sort(data, data + n);
    sorted_array_to_stats(data, n);
}

void
stats_out::get_stats(std::vector<uint64_t> & data) {
    get_stats(data.data(), data.size());
}


}  // namespace stats
