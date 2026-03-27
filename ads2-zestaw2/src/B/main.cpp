#include <cassert>
#include <iostream>

#include "set_hashed.hpp"

class SetHashedTests {
    public:
    void test_insert() {
        auto sh = SetHashed<4>();
        sh.insert(0);
        sh.insert(4);
        sh.insert(8);
        sh.insert(1);
        sh.insert(5);
        sh.insert(2);
        sh.insert(6);
        // Check if items were inserted into correct buckets
        assert(sh.buckets[0].contains(0));
        assert(sh.buckets[0].contains(0));
        assert(sh.buckets[1].contains(1));
        assert(sh.buckets[1].contains(5));
        assert(sh.buckets[2].contains(2));
        assert(sh.buckets[2].contains(6));
    }

    void test_contains() {
        auto sh = SetHashed<4>();
        sh.insert(0);
        sh.insert(4);
        sh.insert(8);
        sh.insert(1);
        sh.insert(5);
        sh.insert(2);
        sh.insert(6);

        assert(sh.contains(0));
        assert(sh.contains(4));
        assert(sh.contains(8));
        assert(sh.contains(1));
        assert(sh.contains(5));
        assert(sh.contains(2));
        assert(!sh.contains(9));
        assert(!sh.contains(11));
        assert(!sh.contains(3));
        assert(!sh.contains(12));
    }
    void test_remove() {
        auto sh = SetHashed<4>();
        sh.insert(0);
        sh.insert(4);
        sh.insert(8);
        sh.insert(1);
        sh.insert(5);
        sh.insert(2);
        sh.insert(6);

        assert(sh.contains(0));
        assert(sh.contains(4));
        assert(sh.contains(8));
        assert(sh.contains(1));
        assert(sh.contains(5));
        assert(sh.contains(2));
        assert(sh.contains(6));

        sh.remove(0);
        sh.remove(1);
        sh.remove(6);

        assert(!sh.contains(0));
        assert(sh.contains(4));
        assert(sh.contains(8));
        assert(!sh.contains(1));
        assert(sh.contains(5));
        assert(sh.contains(2));
        assert(!sh.contains(6));
    }

    void test_union() {
        auto sh1 = SetHashed<4>();
        auto sh2 = SetHashed<4>();
        sh1.insert(0);
        sh1.insert(4);
        sh1.insert(8);
        sh2.insert(1);
        sh2.insert(5);
        sh2.insert(2);
        sh2.insert(6);
        // Union
        auto sh_union = sh1.Union(sh2);
        assert(sh_union.contains(0));
        assert(sh_union.contains(4));
        assert(sh_union.contains(8));
        assert(sh_union.contains(1));
        assert(sh_union.contains(5));
        assert(sh_union.contains(2));
        assert(sh_union.contains(6));
    }

    void test_intersection() {
        auto sh1 = SetHashed<4>();
        auto sh2 = SetHashed<4>();
        sh1.insert(0);
        sh1.insert(2);
        sh1.insert(5);
        sh1.insert(8);
        sh2.insert(0);
        sh2.insert(2);
        sh2.insert(6);
        sh2.insert(9);

        // Intersection
        auto sh_inter = sh1.intersection(sh2);
        assert(sh_inter.contains(0));
        assert(sh_inter.contains(2));
        assert(!sh_inter.contains(5));
        assert(!sh_inter.contains(8));
        assert(!sh_inter.contains(6));
        assert(!sh_inter.contains(9));
    }

    void test_subtract() {
        auto sh1 = SetHashed<4>();
        auto sh2 = SetHashed<4>();
        sh1.insert(0);
        sh1.insert(2);
        sh1.insert(5);
        sh1.insert(8);
        sh2.insert(0);
        sh2.insert(2);
        sh2.insert(6);
        sh2.insert(9);

        auto sh_sub = sh1.subtract(sh2);
        assert(!sh_sub.contains(0));
        assert(!sh_sub.contains(2));
        assert(sh_sub.contains(5));
        assert(sh_sub.contains(8));
        assert(!sh_sub.contains(6));
        assert(!sh_sub.contains(9));
    }
};

auto main() -> int {
    auto set_tests = SetHashedTests();
    set_tests.test_insert();
    set_tests.test_contains();
    set_tests.test_remove();
    set_tests.test_union();
    set_tests.test_intersection();
    set_tests.test_subtract();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}