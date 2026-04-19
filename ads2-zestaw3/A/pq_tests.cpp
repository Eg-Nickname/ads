#include <cassert>
#include <exception>
#include <iostream>
#include <string>

#include "set_pq.hpp"

class SetPqTests {
    public:
    void insert_test() {
        auto priority = [](const uint32_t n) { return n; };
        auto pq = SetPq<uint32_t, decltype(priority)>(priority);

        pq.insert(12);
        pq.insert(10);
        pq.insert(8);
        assert(pq.ls.contains(QueueElement<uint32_t>(12, 12)));
        assert(pq.ls.contains(QueueElement<uint32_t>(8, 8)));
        assert(pq.ls.contains(QueueElement<uint32_t>(10, 10)));
    }
    void pop_test() {
        auto priority = [](const std::string str) { return str.size(); };
        auto pq = SetPq<std::string, decltype(priority)>(priority);

        pq.insert("cart");
        pq.insert("cat");
        pq.insert("Carter");
        assert(pq.pop() == "cat");
        assert(pq.pop() == "cart");
        assert(pq.pop() == "Carter");
    }

    void same_priority_test() {
        auto priority = [](const std::string str) { return str.size(); };
        auto pq = SetPq<std::string, decltype(priority)>(priority);

        pq.insert("fat");
        pq.insert("cat");
        pq.insert("ft");
        pq.insert("rat");
        pq.insert("bat");
        pq.insert("fluke");
        assert(pq.pop() == "ft");
        assert(pq.pop() == "fat");
        assert(pq.pop() == "cat");
        assert(pq.pop() == "rat");
        assert(pq.pop() == "bat");
        assert(pq.pop() == "fluke");
    }

    void duplicates_test() {
        auto priority = [](const std::string str) { return str.size(); };
        auto pq = SetPq<std::string, decltype(priority)>(priority);

        pq.insert("fat");
        pq.insert("cat");
        pq.insert("cat");
        pq.insert("cat");
        pq.insert("fluke");
        assert(pq.pop() == "fat");
        assert(pq.pop() == "cat");
        // Only one cat as we use set under the hood. same pririty and content
        // is just duplicate
        assert(pq.pop() == "fluke");
        assert(pq.size() == 0);
    }

    void empty_pop() {
        auto priority = [](const std::string str) { return str.size(); };
        auto pq = SetPq<std::string, decltype(priority)>(priority);
        bool correct = true;
        try {
            auto _ = pq.pop();
            correct = false;
        } catch (std::exception _) {
            // Do smoething
            correct = true;
        }
        assert(correct);
    }
};

auto main() -> int {
    SetPqTests t{};

    t.insert_test();
    t.pop_test();
    t.same_priority_test();
    t.duplicates_test();
    t.empty_pop();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}