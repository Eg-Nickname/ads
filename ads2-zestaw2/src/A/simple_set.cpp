#include "simple_set.hpp"

SimpleSet& SimpleSet::operator=(const SimpleSet& other) {
    if (this != &other) {
        this->inner_set = other.inner_set;
    }
    return *this;
}

SimpleSet& SimpleSet::operator=(SimpleSet&& other) {
    if (this != &other) {
        this->inner_set = std::move(other.inner_set);
        other.inner_set.resize(this->inner_set.size(), false);
    }
    return *this;
}

void SimpleSet::insert(std::size_t x) {
    // Adjust set sizesize_t
    if (this->inner_set.size() < x) {
        // this->inner_set.resize(x + 1, false);
        return;
    }
    this->inner_set[x] = true;
}

void SimpleSet::remove(std::size_t x) {
    if (this->inner_set.size() > x) {
        this->inner_set[x] = false;
    }
}

bool SimpleSet::contains(std::size_t x) const {
    if (this->inner_set.size() > x) {
        return this->inner_set[x];
    }
    return false;
}

SimpleSet SimpleSet::Union(const SimpleSet& other) const {
    if (this->inner_set.size() != other.inner_set.size()) {
        return {};
    }

    std::size_t new_set_size = this->inner_set.size();
    SimpleSet new_set(new_set_size);
    for (std::size_t i = 0; i < this->inner_set.size(); i++) {
        new_set.inner_set[i] = this->inner_set[i] || other.inner_set[i];
    }
    return new_set;
}

SimpleSet SimpleSet::intersection(const SimpleSet& other) const {
    if (this->inner_set.size() != other.inner_set.size()) {
        return {};
    }

    std::size_t new_set_size = this->inner_set.size();
    SimpleSet new_set(new_set_size);
    for (std::size_t i = 0; i < new_set_size; i++) {
        new_set.inner_set[i] = this->inner_set[i] && other.inner_set[i];
    }
    return new_set;
}

SimpleSet SimpleSet::symetric_diff(const SimpleSet& other) const {
    if (this->inner_set.size() != other.inner_set.size()) {
        return {};
    }

    std::size_t new_set_size = this->inner_set.size();
    SimpleSet new_set(new_set_size);
    for (std::size_t i = 0; i < new_set_size; i++) {
        new_set.inner_set[i] = this->inner_set[i] ^ other.inner_set[i];
    }

    return new_set;
}

bool SimpleSet::operator==(const SimpleSet& other) const {
    if (this->inner_set.size() != other.inner_set.size()) {
        return false;
    } else {
        std::size_t set_size = this->inner_set.size();
        for (std::size_t i = 0; i < set_size; i++) {
            if (this->inner_set[i] != other.inner_set[i]) {
                return false;
            }
        }
        return true;
    }
}

bool SimpleSet::operator!=(const SimpleSet& other) const {
    return !(*this == other);
}

bool SimpleSet::is_sub_set(const SimpleSet& other) const {
    if (this->inner_set.size() != other.inner_set.size()) {
        return false;
    } else {
        std::size_t set_size = this->inner_set.size();
        for (std::size_t i = 0; i < set_size; i++) {
            //  if elemenet in other is false and in this is true, this
            //  means it is not usbset so we and xor with neg of this
            if (this->inner_set[i] ^ other.inner_set[i] &&
                !other.inner_set[i]) {
                return false;
            }
        }
        return true;
    }
}