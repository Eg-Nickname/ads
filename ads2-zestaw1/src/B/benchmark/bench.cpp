// #include "SimpleSet.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

#include "../list_set.hpp"

constexpr int NUM_RUNS = 10;
constexpr std::size_t START_N = 0;
constexpr std::size_t MAX_N = 1000000;
constexpr std::size_t STEP = 100000;

using Clock = std::chrono::high_resolution_clock;

template <typename T>
void do_not_optimize(T&& val) {
    auto volatile force = std::forward<T>(val);
    (void)force;
}

void run_benchmarks() {
    std::ofstream csv("list_set_benchmarks.csv");
    // Header for the CSV
    csv << "N,Insert_ms,Remove_ms,Contains_ms,Size_ns,"
        << "Union_ms,Intersect_ms,Subtract_ms,SymDiff_ms,IsSubset_ms\n";

    ListSet main_s1{}, main_s2{};
    for (std::size_t n = START_N; n <= MAX_N; n += STEP) {
        // Accumulators for averages
        std::vector<double> d_ins, d_rem, d_con, d_size, d_uni, d_int, d_sub,
            d_sym, d_iss;

        // Insert elements to sets
        for (int i = STEP; i > 0; --i) {
            // Inset only even elements
            main_s1.inner_set.push_back(main_s1.size() * 2);
            // Insert only odd elements
            main_s2.inner_set.push_back(main_s2.size() * 2 + 1);
        }

        for (int run = 0; run < NUM_RUNS; ++run) {
            auto s1 = main_s1;
            auto s2 = main_s2;
            std::cout << "Cur set size " << s1.size() << std::endl;
            std::size_t idx = s1.size() * 2;

            // --- O(n) Operations (recorded in ms) ---
            auto start = Clock::now();
            s1.insert(idx);
            d_ins.push_back(
                std::chrono::duration<double, std::milli>(Clock::now() - start)
                    .count());

            start = Clock::now();
            bool has = s1.contains(idx);
            do_not_optimize(has);
            d_con.push_back(
                std::chrono::duration<double, std::milli>(Clock::now() - start)
                    .count());

            start = Clock::now();
            s1.remove(idx);
            d_rem.push_back(
                std::chrono::duration<double, std::milli>(Clock::now() - start)
                    .count());

            start = Clock::now();
            auto sz = s1.size();
            do_not_optimize(sz);
            d_size.push_back(
                std::chrono::duration<double, std::milli>(Clock::now() - start)
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
            bool r_iss = s1.is_sub_set(s1);
            do_not_optimize(r_iss);
            d_iss.push_back(
                std::chrono::duration<double, std::milli>(Clock::now() - start)
                    .count());
        }

        auto avg = [](const std::vector<double>& v) {
            return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
        };

        csv << main_s1.size() << "," << avg(d_ins) << "," << avg(d_rem) << ","
            << avg(d_con) << "," << avg(d_size) << "," << avg(d_uni) << ","
            << avg(d_int) << "," << avg(d_sub) << "," << avg(d_sym) << ","
            << avg(d_iss) << "\n";

        std::cout << "Done N: " << n << std::endl;
    }
    csv.close();
}

auto main() -> int {
    run_benchmarks();

    return 0;
}