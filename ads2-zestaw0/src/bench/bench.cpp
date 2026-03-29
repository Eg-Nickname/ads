// #include "SimpleSet.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

#include "../simple_set.hpp"

constexpr int NUM_RUNS = 10;
constexpr std::size_t START_N = 10000;
constexpr std::size_t MAX_N = 1000000;
constexpr std::size_t STEP = 100000;

using Clock = std::chrono::high_resolution_clock;

template <typename T>
void do_not_optimize(T&& val) {
    auto volatile force = std::forward<T>(val);
    (void)force;
}

void run_benchmarks() {
    std::ofstream csv("set_benchmarks.csv");
    // Header for the CSV
    csv << "N,Insert_ns,Remove_ns,Contains_ns,Size_ns,"
        << "Union_ms,Intersect_ms,Subtract_ms,SymDiff_ms,IsSubset_ms\n";

    for (std::size_t n = START_N; n <= MAX_N; n += STEP) {
        // Accumulators for averages
        std::vector<double> d_ins, d_rem, d_con, d_size, d_uni, d_int, d_sub,
            d_sym, d_iss;

        for (int run = 0; run < NUM_RUNS; ++run) {
            SimpleSet s1(n), s2(n);
            std::size_t idx = n / 2;

            // --- O(1) Operations (recorded in nanoseconds) ---
            auto start = Clock::now();
            s1.insert(idx);
            d_ins.push_back(
                std::chrono::duration<double, std::nano>(Clock::now() - start)
                    .count());

            start = Clock::now();
            bool has = s1.contains(idx);
            do_not_optimize(has);
            d_con.push_back(
                std::chrono::duration<double, std::nano>(Clock::now() - start)
                    .count());

            start = Clock::now();
            s1.remove(idx);
            d_rem.push_back(
                std::chrono::duration<double, std::nano>(Clock::now() - start)
                    .count());

            start = Clock::now();
            auto sz = s1.size();
            do_not_optimize(sz);
            d_size.push_back(
                std::chrono::duration<double, std::nano>(Clock::now() - start)
                    .count());

            // BRUH
            auto cache_warmer = s1.Union(s2);
            // --- O(N) Operations (recorded in milliseconds) ---
            start = Clock::now();
            auto r_uni = s1.Union(s2);
            d_uni.push_back(
                std::chrono::duration<double, std::milli>(Clock::now() - start)
                    .count());

            start = Clock::now();
            auto r_int = s1.intersection(s2);
            d_int.push_back(
                std::chrono::duration<double, std::milli>(Clock::now() - start)
                    .count());

            start = Clock::now();
            auto r_sub = s1.subtract(s2);
            d_sub.push_back(
                std::chrono::duration<double, std::milli>(Clock::now() - start)
                    .count());

            start = Clock::now();
            auto r_sym = s1.symetric_diff(s2);
            d_sym.push_back(
                std::chrono::duration<double, std::milli>(Clock::now() - start)
                    .count());

            start = Clock::now();
            bool r_iss = s1.is_sub_set(s2);
            do_not_optimize(r_iss);
            d_iss.push_back(
                std::chrono::duration<double, std::milli>(Clock::now() - start)
                    .count());
        }

        auto avg = [](const std::vector<double>& v) {
            return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
        };

        csv << n << "," << avg(d_ins) << "," << avg(d_rem) << "," << avg(d_con)
            << "," << avg(d_size) << "," << avg(d_uni) << "," << avg(d_int)
            << "," << avg(d_sub) << "," << avg(d_sym) << "," << avg(d_iss)
            << "\n";

        std::cout << "Done N: " << n << std::endl;
    }
    csv.close();
}

auto main() -> int {
    run_benchmarks();

    return 0;
}