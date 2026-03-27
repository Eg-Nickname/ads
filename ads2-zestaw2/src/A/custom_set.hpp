#include <functional>
#ifndef CUSTOM_SET_HPP
#include "simple_set.hpp"
#include <cstddef>

template <typename T>
class CustomSet {
    SimpleSet inner_set;
    // Function that maps T to size_t so we can store it in our set. Should
    // always provide correct size_t for given input. validate_fn ensures it
    // gets correct input
    std::function<size_t(const T&)> map_fn;
    // Function that checks if passed T is valid for mapping
    std::function<bool(const T&)> validate_fn;
    // friend class SSTests;

    CustomSet(SimpleSet&& s, std::function<size_t(T)> map_fun,
              std::function<size_t(T)> cmp_fun)
        : inner_set(std::move(s)), map_fn(map_fun), validate_fn(cmp_fun) {}

    public:
    CustomSet(std::function<size_t(T)> map_fun,
              std::function<size_t(T)> cmp_fun)
        : inner_set(16), map_fn(map_fun), validate_fn(cmp_fun) {}

    CustomSet(std::size_t N, std::function<size_t(T)> map_fun,
              std::function<size_t(T)> cmp_fun)
        : inner_set(N), map_fn(map_fun), validate_fn(cmp_fun) {}

    CustomSet(const CustomSet& s) {
        this->inner_set = s.inner_set;
        this->map_fn = s.map_fn;
        this->validate_fn = s.validate_fn;
    }
    CustomSet(CustomSet&& s) {
        this->inner_set = std::move(s.inner_set);
        this->map_fn = std::move(s.map_fn);
        this->validate_fn = std::move(s.validate_fn);
    }
    ~CustomSet() {}

    CustomSet& operator=(const CustomSet& other) {
        if (this != &other) {
            this->inner_set = other.inner_set;
        }
        return *this;
    }

    CustomSet& operator=(CustomSet&& other) {
        if (this != &other) {
            this->inner_set = std::move(other.inner_set);
        }
        return *this;
    }

    std::size_t size() const { return this->inner_set.size(); }

    // Set operations
    // Insert element to set
    void insert(T x) {
        if (validate_fn(x)) {
            this->inner_set.insert(map_fn(x));
        }
    }

    // Remove element from set
    void remove(T x) { this->inner_set.remove(map_fn(x)); }
    // Contains, check if element is inside set
    bool contains(T x) const {
        if (validate_fn(x)) {
            return this->inner_set.contains(map_fn(x));
        }
        return false;
    }

    // Inter Set operations
    // Union two sets | O(n) n - size of Omega
    // Returns empty set if not from same Omega
    CustomSet Union(const CustomSet& other) const {
        return CustomSet(this->inner_set.Union(other.inner_set), this->map_fn,
                         this->validate_fn);
    }

    // Intersection | O(n) n - size of Omega
    // Returns empty set if not from same Omega
    CustomSet intersection(const CustomSet& other) const {
        return CustomSet(this->inner_set.intersection(other.inner_set),
                         this->map_fn, this->validate_fn);
    }

    CustomSet symetric_diff(const CustomSet& other) const {
        return CustomSet(this->inner_set.symetric_diff(other.inner_set),
                         this->map_fn, this->validate_fn);
    }

    bool operator==(const CustomSet& other) const {
        return this->inner_set == other.inner_set;
    }

    bool operator!=(const CustomSet& other) const {
        return this->inner_set != other.inner_set;
    }

    bool is_sub_set(const CustomSet& other) const {
        return this->inner_set.is_sub_set(other.inner_set);
    }
};

#endif