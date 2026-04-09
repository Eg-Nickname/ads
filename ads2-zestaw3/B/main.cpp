#include "binary_pq.hpp"
#include <iostream>
auto main() -> int {
    std::cout << "Hello pq!" << std::endl;

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

    pq.display();
    std::cout << std::endl;
    while (!pq.empty()) {
        std::cout << pq.pop() << std::endl;
    }

    return 0;
}