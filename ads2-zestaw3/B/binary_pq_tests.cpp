#include "binary_pq.hpp"
#include <cassert>
#include <iostream>

class BinaryPqTests {
    public:
    void insert_test() {
        auto priority = [](const std::string& lhs, const std::string& rhs) {
            return lhs.size() > rhs.size();
        };
        auto pq = BinaryPq<std::string, decltype(priority)>(priority);

        pq.insert("cart");
        pq.insert("cat");
        pq.insert("Carter");
        pq.insert("Cartographer");
        assert(pq.heap[0] == "cat");
        assert(pq.heap[1] == "cart");
        assert(pq.heap[2] == "Carter");
        assert(pq.heap[3] == "Cartographer");

        auto cmp = [](const uint32_t& lhs, const uint32_t& rhs) {
            return lhs > rhs;
        };

        BinaryPq<uint32_t, decltype(cmp)> int_pq(cmp);
        int_pq.insert(1);
        int_pq.insert(5);
        int_pq.insert(3);
        int_pq.insert(2);

        assert(int_pq.heap[0] == 1);
        assert(int_pq.heap[1] == 2);
        assert(int_pq.heap[2] == 3);
        assert(int_pq.heap[3] == 5);
    }

    void pop_test() {
        auto priority = [](const std::string& lhs, const std::string& rhs) {
            return lhs.size() > rhs.size();
        };
        auto pq = BinaryPq<std::string, decltype(priority)>(priority);

        pq.insert("cart");
        pq.insert("cat");
        pq.insert("Carter");
        pq.insert("Cartographer");
        assert(pq.pop() == "cat");
        assert(pq.pop() == "cart");
        assert(pq.pop() == "Carter");
        assert(pq.pop() == "Cartographer");

        auto cmp = [](const uint32_t& lhs, const uint32_t& rhs) {
            return lhs > rhs;
        };

        BinaryPq<uint32_t, decltype(cmp)> int_pq(cmp);
        int_pq.insert(1);
        int_pq.insert(2);
        int_pq.insert(12);
        int_pq.insert(9);
        assert(int_pq.pop() == 1);
        assert(int_pq.pop() == 2);
        assert(int_pq.pop() == 9);
        assert(int_pq.pop() == 12);
    }

    void order_test() {
        auto cmp = [](const uint32_t& lhs, const uint32_t& rhs) {
            return lhs > rhs;
        };

        BinaryPq<uint32_t, decltype(cmp)> pq(cmp);
        pq.insert(2);
        pq.insert(1);
        pq.insert(5);
        pq.insert(3);
        pq.insert(4);
        pq.insert(9);
        pq.insert(12);
        pq.insert(4);

        assert(pq.pop() == 1);
        assert(pq.pop() == 2);
        assert(pq.pop() == 3);
        assert(pq.pop() == 4);
        assert(pq.pop() == 4);
        assert(pq.pop() == 5);
        assert(pq.pop() == 9);
        assert(pq.pop() == 12);
    }

    void duplicates_test() {
        auto priority = [](const std::string& lhs, const std::string& rhs) {
            return lhs.size() > rhs.size();
        };
        auto pq = BinaryPq<std::string, decltype(priority)>(priority);

        pq.insert("fat");
        pq.insert("cat");
        pq.insert("cat");
        assert(pq.pop() == "fat");
        assert(pq.pop() == "cat");
        assert(pq.pop() == "cat");

        auto cmp = [](const uint32_t& lhs, const uint32_t& rhs) {
            return lhs > rhs;
        };

        BinaryPq<uint32_t, decltype(cmp)> int_pq(cmp);
        int_pq.insert(1);
        int_pq.insert(2);
        int_pq.insert(1);
        int_pq.insert(2);
        assert(int_pq.pop() == 1);
        assert(int_pq.pop() == 1);
        assert(int_pq.pop() == 2);
        assert(int_pq.pop() == 2);
    }
};

auto main() -> int {
    // std::cout << "Hello pq!" << std::endl;

    // auto cmp = [](const uint32_t& lhs, const uint32_t& rhs) {
    //     return lhs > rhs;
    // };

    // BinaryPq<uint32_t, decltype(cmp)> pq(cmp);
    // pq.insert(2);
    // pq.insert(1);
    // pq.insert(5);
    // pq.insert(3);
    // pq.insert(4);
    // pq.insert(9);
    // pq.insert(12);
    // pq.insert(4);

    // pq.display();
    // std::cout << std::endl;
    // while (!pq.empty()) {
    //     std::cout << pq.pop() << std::endl;
    // }

    auto t = BinaryPqTests();
    t.insert_test();
    t.pop_test();
    t.order_test();
    t.duplicates_test();

    std::cout << "All BinaryPq tests passed!" << std::endl;
    return 0;
}