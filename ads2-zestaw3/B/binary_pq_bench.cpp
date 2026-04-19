#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

#include "binary_pq.hpp"

constexpr int NUM_RUNS = 100;
constexpr std::size_t START_N = 0;
constexpr std::size_t MAX_N = 4500000;
constexpr std::size_t STEP = 2000;

using Clock = std::chrono::high_resolution_clock;

template <typename T>
void do_not_optimize(T&& val) {
    auto volatile force = std::forward<T>(val);
    (void)force;
}

void run_benchmarks() {
    std::ofstream csv("binary_pq_benchmarks.csv");
    // Header for the CSV
    csv << "N,Insert_Avg_ms,Remove_ms,Insert_worst_ms\n";

    auto cmp = [](const uint32_t& lhs, const uint32_t& rhs) {
        return lhs > rhs;
    };

    std::vector<BinaryPq<uint32_t, decltype(cmp)>> pqs(
        NUM_RUNS, BinaryPq<uint32_t, decltype(cmp)>(cmp));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint32_t> random_number =
        std::uniform_int_distribution<std::uint32_t>(
            0, std::numeric_limits<uint32_t>::max());

    auto start_step = STEP;
    for (std::size_t n = START_N; n <= MAX_N; n += start_step) {
        // Accumulators for averages
        std::vector<double> d_ins_avg, d_rem, d_ins;

        for (int i = start_step; i > 0; --i) {
            for (auto& pq : pqs) {
                auto num = random_number(gen);
                pq.insert(num);
            }
        }

        auto start = Clock::now();
        // auto num = ;
        for (int run = 0; run <= NUM_RUNS; ++run) {
            for (auto& pq : pqs) {
                pq.insert(random_number(gen));
            }
        }
        d_ins_avg.push_back(
            std::chrono::duration<double, std::micro>(Clock::now() - start)
                .count());

        start = Clock::now();
        for (int run = 0; run < NUM_RUNS; ++run) {
            for (auto& pq : pqs) {
                pq.pop();
            }
        }
        d_rem.push_back(
            std::chrono::duration<double, std::micro>(Clock::now() - start)
                .count());

        start = Clock::now();
        for (int run = 0; run < NUM_RUNS; ++run) {
            for (auto& pq : pqs) {
                pq.insert(0);
                pq.insert(std::numeric_limits<uint32_t>::max());
            }
        }
        d_ins.push_back(
            std::chrono::duration<double, std::micro>(Clock::now() - start)
                .count());

        auto avg = [](const std::vector<double>& v) {
            return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
        };

        csv << pqs[0].size() << "," << avg(d_ins_avg) << "," << avg(d_rem)
            << "," << avg(d_ins) << "\n";

        std::cout << "Done N: " << n << std::endl;
        start_step *= 2;
    }
    csv.close();
}

auto main() -> int {
    run_benchmarks();

    return 0;
}