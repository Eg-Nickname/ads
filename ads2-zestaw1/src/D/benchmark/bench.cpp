// #include "SimpleSet.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <ratio>
#include <string>
#include <vector>

#include "../string_set.hpp"

constexpr int NUM_RUNS = 10;
constexpr std::size_t START_N = 0;
constexpr std::size_t MAX_N = 20000;
constexpr std::size_t STEP = 2000;

using Clock = std::chrono::high_resolution_clock;

template <typename T>
void do_not_optimize(T&& val) {
    auto volatile force = std::forward<T>(val);
    (void)force;
}

std::string generate_random_string(std::size_t length = 40) {
    const std::string characters =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string random_string;
    random_string.reserve(length);

    for (std::size_t i = 0; i < length; ++i) {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}
void run_benchmarks() {
    std::ofstream csv("string_set_benchmarks.csv");
    // Header for the CSV
    csv << "N,Insert_ns,Remove_ns,Contains_ns\n";

    StringSet main_s1{}, main_s2{};
    for (std::size_t n = START_N; n <= MAX_N; n += STEP) {
        // Accumulators for averages
        std::vector<double> d_ins, d_rem, d_con;

        // Insert elements to sets
        for (int i = STEP; i > 0; --i) {
            // Inset only even elements
            auto s = generate_random_string();
            auto s2 = s + 'a';
            main_s1.insert(std::move(s));
            // Insert only odd elements
            main_s2.insert(std::move(s2));
        }

        for (int run = 0; run < NUM_RUNS; ++run) {
            auto s1 = main_s1;
            auto s2 = main_s2;

            std::string idx = "AAAAAAAAAAAAAAAAAAAAAAAAAA";
            // --- O(1) Operations (recorded in ms) ---
            auto start = Clock::now();
            auto idx2 = idx;
            s1.insert(std::move(idx2));
            d_ins.push_back(
                std::chrono::duration<double, std::micro>(Clock::now() - start)
                    .count());

            start = Clock::now();
            bool has = s1.contains(idx);
            do_not_optimize(has);
            d_con.push_back(
                std::chrono::duration<double, std::micro>(Clock::now() - start)
                    .count());

            start = Clock::now();
            s1.remove(idx);
            d_rem.push_back(
                std::chrono::duration<double, std::micro>(Clock::now() - start)
                    .count());
        }

        auto avg = [](const std::vector<double>& v) {
            return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
        };

        csv << main_s1.ss.size() << "," << avg(d_ins) << "," << avg(d_rem)
            << "," << avg(d_con) << "\n";

        std::cout << "Done N: " << n << std::endl;
    }
    csv.close();
}

auto main() -> int {
    run_benchmarks();

    return 0;
}