#include <cassert>
#include <cstddef>
#include <iostream>
#include <random>

#include "list_set.hpp"

class LSTests {
    public:
    static ListSet gen_random_set(std::size_t N) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::size_t> dist(-0, N - 1);
        ListSet ls{};

        for (std::size_t i = 0; i < N / 2; i++) {
            ls.insert(dist(gen));
        }

        return ls;
    }

    static void size_test() {
        ListSet s1{};
        assert(s1.size() == 0);
        s1.insert(10);
        assert(s1.size() == 1);
    }

    static void eq_test() {
        ListSet s1{};
        ListSet s2{};

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
        ListSet s1 = gen_random_set(16);
        ListSet s2{};
        assert(s1 != s2);

        s2 = s1;
        assert(s1 == s2);

        ListSet s3{};
        assert(s1 != s3);

        s3 = std::move(s1);
        assert(s3 != s1);
        assert(s3 == s2);

        ListSet s4{};
        assert(s1 == s4);
    }

    static void insert() {
        ListSet s2{};
        s2.insert(0);
        s2.insert(15);
        s2.insert(8);
        assert(s2.contains(0));
        assert(s2.contains(15));
        assert(s2.contains(8));
    }

    static void contains() {
        ListSet s2{};
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
        ListSet s2{};
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
        ListSet s1{};
        s1.insert(1);
        s1.insert(4);
        s1.insert(8);

        ListSet s2{};
        s2.insert(4);
        s2.insert(12);
        s2.insert(14);

        auto s3 = s1.Union(s2);
        assert(s3.contains(1));
        assert(s3.contains(4));
        assert(s3.contains(8));
        assert(s3.contains(12));
        assert(s3.contains(14));

        ListSet s4{};
        s4.insert(1);
        s4.insert(4);
        s4.insert(8);
        s4.insert(12);
        s4.insert(14);

        // ensure no other elements changed
        assert(s3 == s4);
    }

    static void intersection_test() {
        ListSet s1{};
        s1.insert(1);
        s1.insert(4);
        s1.insert(8);

        ListSet s2{};
        s2.insert(4);
        s2.insert(12);
        s2.insert(14);

        auto s3 = s1.intersection(s2);
        assert(!s3.contains(1));
        assert(s3.contains(4));
        assert(!s3.contains(8));
        assert(!s3.contains(12));
        assert(!s3.contains(14));

        ListSet s4{};
        s4.insert(4);

        // ensure no other elements changed
        assert(s3 == s4);
    }

    static void symetric_diff_test() {
        ListSet s1{};
        s1.insert(1);
        s1.insert(4);
        s1.insert(8);

        ListSet s2{};
        s2.insert(4);
        s2.insert(12);
        s2.insert(14);

        auto s3 = s1.symetric_diff(s2);
        assert(s3.contains(1));
        assert(!s3.contains(4));
        assert(s3.contains(8));
        assert(s3.contains(12));
        assert(s3.contains(14));

        ListSet s4{};
        s4.insert(1);
        s4.insert(8);
        s4.insert(12);
        s4.insert(14);

        // ensure no other elements changed
        assert(s3 == s4);
    }

    static void is_sub_set_test() {
        ListSet s1{};
        s1.insert(1);
        s1.insert(4);
        s1.insert(8);

        ListSet s2 = s1;
        assert(s2.is_sub_set(s1));

        ListSet s3{};
        s3.insert(4);
        assert(s3.is_sub_set(s1));
        s3.insert(12);
        assert(!s3.is_sub_set(s1));
    }

    static void subtract_test() {
        ListSet s1{};
        s1.insert(1);
        s1.insert(4);
        s1.insert(8);

        ListSet s2{};
        s2.insert(1);
        s2.insert(8);

        ListSet s3{};
        s3.insert(4);

        auto s4 = s1.subtract(s2);
        assert(s4 == s3);
    }
};

auto main() -> int {
    LSTests::eq_test();
    LSTests::size_test();
    LSTests::assign_op_test();
    LSTests::insert();
    LSTests::remove();
    LSTests::contains();
    LSTests::Union_test();
    LSTests::intersection_test();
    LSTests::symetric_diff_test();
    LSTests::subtract_test();
    LSTests::is_sub_set_test();
    std::cout << "All tests passed" << "\n";
    return 0;
}
