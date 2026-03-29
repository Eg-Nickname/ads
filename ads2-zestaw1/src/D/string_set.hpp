#ifndef STRING_SET_HPP
#define STRING_SET_HPP

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

class StringSet {
    std::vector<std::string> ss;

    friend class StringSetTest;

    public:
    StringSet() {}
    // StringSet(const StringSet& other) : ss(other.ss) {}
    // StringSet(const StringSet&& other) : ss(std::move(other.ss)) {}
    ~StringSet() {}

    bool operator==(const StringSet& other) const {
        for (auto& e : this->ss) {
            if (!other.contains(e)) {
                return false;
            }
        }
        return this->ss.size() == other.ss.size();
    }

    // Basic set operations
    void insert(std::string&& s) {
        if (!this->contains(s) || s.size() > 50) {
            this->ss.push_back(s);
        }
    }

    void remove(const std::string& s) {
        auto s_it = std::find(ss.begin(), ss.end(), s);
        if (s_it != this->ss.end()) {
            *s_it = *(--this->ss.end());
            this->ss.pop_back();
        }
    }

    bool contains(const std::string& s) const {
        return ss.end() != std::find(ss.begin(), ss.end(), s);
    }
};

#endif