#ifndef SET_HASHED_HPP
#define SET_HASHED_HPP

#include <cstddef>
#include <iostream>
#include <vector>

#include "list_set.hpp"

/// N - number of buckets in set
template <size_t N>
class SetHashed {
    std::vector<ListSet> buckets;
    friend class SetHashedTests;

    public:
    // Constructor
    SetHashed() : buckets(N) {}

    // Set operations
    void insert(std::size_t x);
    void remove(std::size_t x);
    bool contains(std::size_t x) const;
    SetHashed Union(const SetHashed& other) const;
    SetHashed intersection(const SetHashed& other) const;
    SetHashed subtract(const SetHashed& other) const;
    bool operator==(const SetHashed& other) const;
    bool operator!=(const SetHashed& other) const;
    bool is_sub_set(const SetHashed& other) const;
};

template <size_t N>
void SetHashed<N>::insert(std::size_t x) {
    if (this->contains(x)) {
        return;
    }
    auto& bucket = this->buckets[x % N];
    bucket.insert(x);
}

template <size_t N>
void SetHashed<N>::remove(std::size_t x) {
    auto& bucket = this->buckets[x % N];
    bucket.remove(x);
}

template <size_t N>
bool SetHashed<N>::contains(std::size_t x) const {
    auto& bucket = this->buckets[x % N];
    return bucket.contains(x);
}

template <size_t N>
SetHashed<N> SetHashed<N>::Union(const SetHashed& other) const {
    auto new_set = SetHashed<N>();
    for (size_t i = 0; i < N; i++) {
        // auto out = new_set.buckets[i];
        auto& l_set = this->buckets[i];
        auto& r_set = other.buckets[i];
        new_set.buckets[i] = l_set.Union(r_set);
    }
    return new_set;
}

template <size_t N>
SetHashed<N> SetHashed<N>::intersection(const SetHashed& other) const {
    auto new_set = SetHashed<N>();
    for (size_t i = 0; i < N; i++) {
        auto& l_set = this->buckets[i];
        auto& r_set = other.buckets[i];
        new_set.buckets[i] = l_set.intersection(r_set);
    }
    return new_set;
}

template <size_t N>
SetHashed<N> SetHashed<N>::subtract(const SetHashed& other) const {
    auto new_set = SetHashed<N>();
    for (size_t i = 0; i < N; i++) {
        // auto& out = new_set.buckets[i];
        auto& l_set = this->buckets[i];
        auto& r_set = other.buckets[i];
        new_set.buckets[i] = l_set.subtract(r_set);
    }
    return new_set;
}

template <size_t N>
bool SetHashed<N>::operator==(const SetHashed& other) const {
    for (size_t i = 0; i < N; i++) {
        // auto& out = new_set.buckets[i];
        auto l_set = this->buckets[i];
        auto r_set = other.buckets[i];
        if (l_set != r_set) {
            return false;
        }
    }
    return true;
}

template <size_t N>
bool SetHashed<N>::operator!=(const SetHashed& other) const {
    return !(this == other);
}

#endif