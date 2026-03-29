#include <cassert>
#include <cstddef>
#include <iostream>
#include <random>

#include "simple_set.hpp"

class SSTests {
    public:
    static SimpleSet gen_random_set(std::size_t N) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::size_t> dist(-0, N - 1);
        SimpleSet ss(N);

        for (std::size_t i = 0; i < N / 2; i++) {
            ss.insert(dist(gen));
        }

        return ss;
    }

    static void size_test() {
        SimpleSet s1(0);
        SimpleSet s2(16);
        SimpleSet s3(32);

        assert(s1.size() == 0);
        assert(s2.size() == 16);
        assert(s3.size() == 32);
    }

    static void eq_test() {
        SimpleSet s1(16);
        SimpleSet s2(16);
        assert(s1 == s2);

        s1.insert(14);
        assert(s1 != s2);

        s2.insert(14);
        assert(s1 == s2);

        s2.insert(2);
        assert(s1 != s2);

        s1.insert(2);
        assert(s1 == s2);
    }

    static void assign_op_test() {
        SimpleSet s1 = gen_random_set(16);
        SimpleSet s2(16);
        assert(s1 != s2);

        s2 = s1;
        assert(s1 == s2);

        SimpleSet s3(16);
        assert(s1 != s3);

        s3 = std::move(s1);
        assert(s3 != s1);
        assert(s3 == s2);

        SimpleSet s4(16);
        assert(s1 == s4);
    }

    static void insert() {
        SimpleSet s2(16);
        s2.insert(0);
        s2.insert(15);
        s2.insert(8);
        assert(s2.inner_set[0]);
        assert(s2.inner_set[15]);
        assert(s2.inner_set[8]);
    }

    static void contains() {
        SimpleSet s2(16);
        s2.insert(0);
        s2.insert(15);
        s2.insert(8);
        assert(s2.contains(0));
        assert(s2.contains(15));
        assert(s2.contains(8));
        assert(!s2.contains(6));
        assert(!s2.contains(66));  // out of bounds chceck
        assert(!s2.contains(-66)); // out of bounds chceck
    }

    static void remove() {
        SimpleSet s2(16);
        s2.insert(0);
        s2.insert(15);
        s2.insert(8);
        assert(s2.contains(0));
        assert(s2.contains(15));
        assert(s2.contains(8));
        s2.remove(0);
        s2.remove(15);
        s2.remove(16); // out of bounds remove

        assert(!s2.contains(0));
        assert(!s2.contains(15));
    }

    static void Union_test() {
        SimpleSet s1(16);
        s1.insert(1);
        s1.insert(4);
        s1.insert(8);

        SimpleSet s2(16);
        s2.insert(4);
        s2.insert(12);
        s2.insert(14);

        auto s3 = s1.Union(s2);
        assert(s3.contains(1));
        assert(s3.contains(4));
        assert(s3.contains(8));
        assert(s3.contains(12));
        assert(s3.contains(14));

        SimpleSet s4(16);
        s4.insert(1);
        s4.insert(4);
        s4.insert(8);
        s4.insert(12);
        s4.insert(14);

        // ensure no other elements changed
        assert(s3 == s4);
    }

    static void intersection_test() {
        SimpleSet s1(16);
        s1.insert(1);
        s1.insert(4);
        s1.insert(8);

        SimpleSet s2(16);
        s2.insert(4);
        s2.insert(12);
        s2.insert(14);

        auto s3 = s1.intersection(s2);
        assert(!s3.contains(1));
        assert(s3.contains(4));
        assert(!s3.contains(8));
        assert(!s3.contains(12));
        assert(!s3.contains(14));

        SimpleSet s4(16);
        s4.insert(4);

        // ensure no other elements changed
        assert(s3 == s4);
    }

    static void symetric_diff_test() {
        SimpleSet s1(16);
        s1.insert(1);
        s1.insert(4);
        s1.insert(8);

        SimpleSet s2(16);
        s2.insert(4);
        s2.insert(12);
        s2.insert(14);

        auto s3 = s1.symetric_diff(s2);
        assert(s3.contains(1));
        assert(!s3.contains(4));
        assert(s3.contains(8));
        assert(s3.contains(12));
        assert(s3.contains(14));

        SimpleSet s4(16);
        s4.insert(1);
        s4.insert(8);
        s4.insert(12);
        s4.insert(14);

        // ensure no other elements changed
        assert(s3 == s4);
    }

    static void is_sub_set_test() {
        SimpleSet s1(16);
        s1.insert(1);
        s1.insert(4);
        s1.insert(8);

        SimpleSet s2 = s1;
        assert(s2.is_sub_set(s1));

        SimpleSet s3(16);
        s3.insert(4);
        assert(s3.is_sub_set(s1));
        s3.insert(12);
        assert(!s3.is_sub_set(s1));
    }
};

auto main() -> int {
    SSTests::eq_test();
    SSTests::size_test();
    SSTests::assign_op_test();
    SSTests::insert();
    SSTests::remove();
    SSTests::contains();
    SSTests::Union_test();
    SSTests::intersection_test();
    SSTests::symetric_diff_test();
    SSTests::is_sub_set_test();

    std::cout << "All tests passed" << "\n";
    return 0;
}
