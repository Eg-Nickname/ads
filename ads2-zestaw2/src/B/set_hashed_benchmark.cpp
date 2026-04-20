// #include "SimpleSet.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <variant>
#include <vector>

#include "set_hashed.hpp"
using SetTypes = std::variant<SetHashed<1>, SetHashed<2>, SetHashed<4>,
                              SetHashed<10>, SetHashed<100>>;

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
    csv << "N,Insert_ms, Union_ms\n";

    SetHashed<1> sh1{};
    SetHashed<2> sh2{};
    SetHashed<4> sh4{};
    SetHashed<10> sh10{};
    SetHashed<100> sh100{};

    std::vector<SetTypes> sets1{sh1, sh2, sh4, sh10, sh100};
    std::vector<SetTypes> sets2{sh1, sh2, sh4, sh10, sh100};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::uint32_t> random_number =
        std::uniform_int_distribution<std::uint32_t>(
            0, std::numeric_limits<uint32_t>::max());

    ListSet main_s1{}, main_s2{};
    for (std::size_t n = START_N; n <= MAX_N; n += STEP) {
        // Accumulators for averages
        std::vector<double> d_ins, d_uni;

        // Insert elements to sets
        for (int i = STEP; i > 0; --i) {
            auto num1 = random_number(gen);
            for (auto& s : sets1) {
                std::visit([&num1](auto& set) { set.insert(num1); }, s);
            }
            auto num2 = random_number(gen);
            for (auto& s : sets2) {
                std::visit([&num2](auto& set) { set.insert(num2); }, s);
            }
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

            // BRUH
            start = Clock::now();
            auto r_uni = s1.Union(s2);
            d_uni.push_back(
                std::chrono::duration<double, std::milli>(Clock::now() - start)
                    .count());

            auto avg = [](const std::vector<double>& v) {
                return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
            };

            csv << main_s1.size() << "," << avg(d_ins) << avg(d_uni) << "\n";

            std::cout << "Done N: " << n << std::endl;
        }
        csv.close();
    }
}

auto main() -> int {
    run_benchmarks();

    return 0;
}