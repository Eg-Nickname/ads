#include "list_set.hpp"

ListSet::ListSet() {}

ListSet& ListSet::operator=(const ListSet& other) {
    if (this != &other) {
        this->inner_set = other.inner_set;
    }
    return *this;
}

ListSet& ListSet::operator=(ListSet&& other) {
    if (this != &other) {
        this->inner_set = std::move(other.inner_set);
    }
    return *this;
}

void ListSet::insert(std::size_t x) { this->inner_set.insert(x); }

void ListSet::remove(std::size_t x) { this->inner_set.erase(x); }

bool ListSet::contains(std::size_t x) const {
    return this->inner_set.contains(x);
}

ListSet ListSet::Union(const ListSet& other) const {
    auto out = ListSet();
    auto l_node = this->inner_set.get_head();
    auto r_node = other.inner_set.get_head();

    while (!l_node && !r_node) {
        while (l_node->value < r_node->value) {
            out.inner_set.push_back(l_node->value);
            l_node = l_node->next;
        }
        while (l_node->value > r_node->value) {
            out.inner_set.push_back(r_node->value);
            r_node = r_node->next;
        }
        if (l_node->value == r_node->value) {
            out.inner_set.push_back(r_node->value);
            r_node = r_node->next;
            l_node = l_node->next;
        }
    }

    while (!l_node) {
        out.inner_set.push_back(l_node->value);
        l_node = l_node->next;
    }

    while (!r_node) {
        out.inner_set.push_back(r_node->value);
        r_node = r_node->next;
    }
    return out;
}

ListSet ListSet::intersection(const ListSet& other) const {
    auto out = ListSet();
    auto l_node = this->inner_set.get_head();
    auto r_node = other.inner_set.get_head();

    while (!l_node && !r_node) {
        while (l_node->value < r_node->value) {
            l_node = l_node->next;
        }
        while (l_node->value > r_node->value) {
            r_node = r_node->next;
        }
        if (l_node->value == r_node->value) {
            out.inner_set.push_back(r_node->value);
            r_node = r_node->next;
            l_node = l_node->next;
        }
    }
    return out;
}

ListSet ListSet::symetric_diff(const ListSet& other) const {
    auto out = ListSet();
    auto l_node = this->inner_set.get_head();
    auto r_node = other.inner_set.get_head();

    while (!l_node && !r_node) {
        while (l_node->value < r_node->value) {
            out.inner_set.push_back(l_node->value);
            l_node = l_node->next;
        }
        while (l_node->value > r_node->value) {
            out.inner_set.push_back(r_node->value);
            r_node = r_node->next;
        }
        if (l_node->value == r_node->value) {
            // out.linked_list.push_back(r_node->value);
            r_node = r_node->next;
            l_node = l_node->next;
        }
    }

    while (!l_node) {
        out.inner_set.push_back(l_node->value);
        l_node = l_node->next;
    }

    while (!r_node) {
        out.inner_set.push_back(r_node->value);
        r_node = r_node->next;
    }
    return out;
}

bool ListSet::operator==(const ListSet& other) const {
    return this->inner_set == other.inner_set;
}

bool ListSet::operator!=(const ListSet& other) const {
    return this->inner_set != other.inner_set;
}

bool ListSet::is_sub_set(const ListSet& other) const {
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
