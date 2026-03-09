#ifndef SIMPLE_SET_HPP
#include <cstddef>
#include <vector>

class SimpleSet {
    std::vector<bool> inner_set;
    friend class SSTests;

    public:
    SimpleSet() : inner_set(16, false) {}
    SimpleSet(std::size_t N) : inner_set(N, false) {}
    SimpleSet(const SimpleSet& s) { this->inner_set = s.inner_set; }
    SimpleSet(SimpleSet&& s) { this->inner_set = std::move(s.inner_set); }
    ~SimpleSet() {}

    SimpleSet& operator=(const SimpleSet& other);

    SimpleSet& operator=(SimpleSet&& other);

    std::size_t size() const { return this->inner_set.size(); }

    // Set operations
    // Insert element to set
    void insert(std::size_t x);

    // Remove element from set
    void remove(std::size_t x);
    // Contains, check if element is inside set
    bool contains(std::size_t x) const;

    // Inter Set operations
    // Union two sets | O(n) n - size of Omega
    // Returns empty set if not from same Omega
    SimpleSet Union(const SimpleSet& other) const;

    // Intersection | O(n) n - size of Omega
    // Returns empty set if not from same Omega
    SimpleSet intersection(const SimpleSet& other) const;

    // Symetric diff
    SimpleSet symetric_diff(const SimpleSet& other) const;

    // Identity cmp | O(n) - n size of Omega
    bool operator==(const SimpleSet& other) const;

    // Not identity cmp | O(n) - n size of Omega
    bool operator!=(const SimpleSet& other) const;

    // Subset | O(n) - n size of Omega
    bool is_sub_set(const SimpleSet& other) const;
};

#endif