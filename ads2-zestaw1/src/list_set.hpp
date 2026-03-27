#ifndef LIST_SET_HPP
#define LIST_SET_HPP
#include <cstddef>

#include "ordered_ll.hpp"

class ListSet {
    OrderedList<int32_t> inner_set;
    friend class LSTests;

    public:
    ListSet();
    ListSet(const ListSet& s) { this->inner_set = s.inner_set; }
    ListSet(ListSet&& s) { this->inner_set = std::move(s.inner_set); }
    ~ListSet() {}

    ListSet& operator=(const ListSet& other);

    ListSet& operator=(ListSet&& other);

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
    ListSet Union(const ListSet& other) const;

    // Intersection | O(n) n - size of Omega
    // Returns empty set if not from same Omega
    ListSet intersection(const ListSet& other) const;

    // Symetric diff
    ListSet symetric_diff(const ListSet& other) const;

    // Identity cmp | O(n) - n size of Omega
    bool operator==(const ListSet& other) const;

    // Not identity cmp | O(n) - n size of Omega
    bool operator!=(const ListSet& other) const;

    // Subset | O(n) - n size of Omega
    bool is_sub_set(const ListSet& other) const;
};

#endif