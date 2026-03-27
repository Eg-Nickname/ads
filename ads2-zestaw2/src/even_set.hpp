#ifndef EVEN_SET_HPP
#include "simple_set.hpp"
#include <cstddef>

class EvenSet {
    SimpleSet inner_set;
    // friend class SSTests;

    EvenSet(SimpleSet&& s) : inner_set(std::move(s)) {}

    public:
    EvenSet() : inner_set(16) {}
    EvenSet(std::size_t N) : inner_set(N) {}
    EvenSet(const EvenSet& s) { this->inner_set = s.inner_set; }
    EvenSet(EvenSet&& s) { this->inner_set = std::move(s.inner_set); }
    ~EvenSet() {}

    EvenSet& operator=(const EvenSet& other) {
        if (this != &other) {
            this->inner_set = other.inner_set;
        }
        return *this;
    }

    EvenSet& operator=(EvenSet&& other) {
        if (this != &other) {
            this->inner_set = std::move(other.inner_set);
        }
        return *this;
    }

    std::size_t size() const { return this->inner_set.size(); }

    // Set operations
    // Insert element to set
    void insert(std::size_t x) {
        if (x % 2 == 0) {
            this->inner_set.insert(x / 2);
        }
    }

    // Remove element from set
    void remove(std::size_t x) {
        if (x % 2 == 0) {
            this->inner_set.remove(x / 2);
        }
    }
    // Contains, check if element is inside set
    bool contains(std::size_t x) const {
        if (x % 2 == 0) {
            return this->inner_set.contains(x / 2);
        }
        return false;
    }

    // Inter Set operations
    // Union two sets | O(n) n - size of Omega
    // Returns empty set if not from same Omega
    EvenSet Union(const EvenSet& other) const {
        return this->inner_set.Union(other.inner_set);
    }

    // Intersection | O(n) n - size of Omega
    // Returns empty set if not from same Omega
    EvenSet intersection(const EvenSet& other) const {
        return this->inner_set.intersection(other.inner_set);
    }

    // Symetric diff
    EvenSet symetric_diff(const EvenSet& other) const {
        return this->inner_set.symetric_diff(other.inner_set);
    }

    // Identity cmp | O(n) - n size of Omega
    bool operator==(const EvenSet& other) const {
        return this->inner_set == other.inner_set;
    }

    // Not identity cmp | O(n) - n size of Omega
    bool operator!=(const EvenSet& other) const {
        return this->inner_set == other.inner_set;
    }

    // Subset | O(n) - n size of Omega
    bool is_sub_set(const EvenSet& other) const {
        return this->inner_set.is_sub_set(other.inner_set);
    }
};

#endif