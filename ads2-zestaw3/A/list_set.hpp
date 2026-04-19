#ifndef LIST_SET_HPP
#define LIST_SET_HPP
#include <cstddef>

#include <cassert>
#include <concepts>
#include <cstddef>

// Ensure our inner type is comparable
#include "ordered_ll.hpp"

template <typename Q, typename U>
class SetPq;

template <typename T>
class ListSet {
    OrderedList<T> inner_set;

    template <typename Q, typename U>
    friend class SetPq;
    // friend void run_benchmarks();

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
    void insert(T x);

    // Remove element from set
    void remove(T x);
    // Contains, check if element is inside set
    bool contains(T x) const;

    // Inter Set operations
    // Union two sets | O(n) n - size of Omega
    // Returns empty set if not from same Omega
    ListSet<T> Union(const ListSet<T>& other) const;

    // Intersection | O(n) n - size of Omega
    // Returns empty set if not from same Omega
    ListSet<T> intersection(const ListSet<T>& other) const;

    ListSet<T> subtract(const ListSet<T>& other) const;

    // Symetric diff
    ListSet<T> symetric_diff(const ListSet<T>& other) const;

    // Identity cmp | O(n) - n size of Omega
    bool operator==(const ListSet<T>& other) const;

    // Not identity cmp | O(n) - n size of Omega
    bool operator!=(const ListSet<T>& other) const;

    // Subset | O(n) - n size of Omega
    bool is_sub_set(const ListSet<T>& other) const;
};

// #include "list_set.hpp"

template <typename T>
ListSet<T>::ListSet() {}

template <typename T>
ListSet<T>& ListSet<T>::operator=(const ListSet<T>& other) {
    if (this != &other) {
        this->inner_set = other.inner_set;
    }
    return *this;
}

template <typename T>
ListSet<T>& ListSet<T>::operator=(ListSet<T>&& other) {
    if (this != &other) {
        this->inner_set = std::move(other.inner_set);
    }
    return *this;
}

template <typename T>
void ListSet<T>::insert(T x) {
    if (this->contains(x)) {
        return;
    }
    this->inner_set.insert(x);
}

template <typename T>
void ListSet<T>::remove(T x) {
    this->inner_set.erase(x);
}

template <typename T>
bool ListSet<T>::contains(T x) const {
    return this->inner_set.contains(x);
}

template <typename T>
ListSet<T> ListSet<T>::Union(const ListSet<T>& other) const {
    auto out = ListSet();
    auto l_node = this->inner_set.get_head();
    auto r_node = other.inner_set.get_head();

    while (l_node != nullptr && r_node != nullptr) {
        while (l_node != nullptr && l_node->value < r_node->value) {
            out.inner_set.push_back(l_node->value);
            l_node = l_node->next;
        }

        if (l_node == nullptr || r_node == nullptr)
            break;

        while (r_node != nullptr && l_node->value > r_node->value) {
            out.inner_set.push_back(r_node->value);
            r_node = r_node->next;
        }

        if (l_node == nullptr || r_node == nullptr)
            break;

        if (l_node->value == r_node->value) {
            out.inner_set.push_back(r_node->value);
            r_node = r_node->next;
            l_node = l_node->next;
        }
    }

    while (l_node != nullptr) {
        out.inner_set.push_back(l_node->value);
        l_node = l_node->next;
    }

    while (r_node != nullptr) {
        out.inner_set.push_back(r_node->value);
        r_node = r_node->next;
    }
    return out;
}

template <typename T>
ListSet<T> ListSet<T>::intersection(const ListSet<T>& other) const {
    auto out = ListSet();
    auto l_node = this->inner_set.get_head();
    auto r_node = other.inner_set.get_head();

    while (l_node != nullptr && r_node != nullptr) {
        while (l_node != nullptr && l_node->value < r_node->value) {
            l_node = l_node->next;
        }

        if (l_node == nullptr || r_node == nullptr)
            break;

        while (r_node != nullptr && l_node->value > r_node->value) {
            r_node = r_node->next;
        }

        if (l_node == nullptr || r_node == nullptr)
            break;

        if (l_node->value == r_node->value) {
            out.inner_set.push_back(r_node->value);
            r_node = r_node->next;
            l_node = l_node->next;
        }
    }
    return out;
}

template <typename T>
ListSet<T> ListSet<T>::subtract(const ListSet<T>& other) const {
    auto out = ListSet();
    auto l_node = this->inner_set.get_head();
    auto r_node = other.inner_set.get_head();
    while (l_node != nullptr && r_node != nullptr) {
        while (l_node != nullptr && l_node->value < r_node->value) {
            out.inner_set.push_back(l_node->value);
            l_node = l_node->next;
        }

        if (l_node == nullptr || r_node == nullptr)
            break;

        while (r_node != nullptr && l_node->value > r_node->value) {
            r_node = r_node->next;
        }

        if (l_node == nullptr || r_node == nullptr)
            break;

        if (l_node->value == r_node->value) {
            r_node = r_node->next;
            l_node = l_node->next;
        }
    }

    while (l_node != nullptr) {
        out.inner_set.push_back(l_node->value);
        l_node = l_node->next;
    }
    return out;
}

template <typename T>
ListSet<T> ListSet<T>::symetric_diff(const ListSet<T>& other) const {
    auto out = ListSet();
    auto l_node = this->inner_set.get_head();
    auto r_node = other.inner_set.get_head();

    while (l_node != nullptr && r_node != nullptr) {
        while (l_node != nullptr && l_node->value < r_node->value) {
            out.inner_set.push_back(l_node->value);
            l_node = l_node->next;
        }

        if (l_node == nullptr || r_node == nullptr)
            break;

        while (r_node != nullptr && l_node->value > r_node->value) {
            out.inner_set.push_back(r_node->value);
            r_node = r_node->next;
        }

        if (l_node == nullptr || r_node == nullptr)
            break;

        if (l_node->value == r_node->value) {
            // out.linked_list.push_back(r_node->value);
            r_node = r_node->next;
            l_node = l_node->next;
        }
    }

    while (l_node != nullptr) {
        out.inner_set.push_back(l_node->value);
        l_node = l_node->next;
    }

    while (r_node != nullptr) {
        out.inner_set.push_back(r_node->value);
        r_node = r_node->next;
    }
    return out;
}

template <typename T>
bool ListSet<T>::operator==(const ListSet<T>& other) const {
    return this->inner_set == other.inner_set;
}

template <typename T>
bool ListSet<T>::operator!=(const ListSet<T>& other) const {
    return this->inner_set != other.inner_set;
}

template <typename T>
bool ListSet<T>::is_sub_set(const ListSet<T>& other) const {
    if (this->size() > other.size()) {
        return false;
    }
    auto l_node = this->inner_set.get_head();
    auto r_node = other.inner_set.get_head();

    while (l_node != nullptr) {
        // Move to correct r set node
        while (r_node != nullptr && l_node->value > r_node->value) {
            r_node = r_node->next;
        }
        // We run out of elements in r set
        if (!r_node) {
            return false;
        }

        // We should prev stopped at this value if subset
        if (l_node->value != r_node->value) {
            return false;
        }
        l_node = l_node->next;
    }

    return true;
}

#endif