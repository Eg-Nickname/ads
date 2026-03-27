#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class StringSet {
    std::vector<std::string> ss;

    public:
    StringSet() {}
    StringSet(const StringSet& other) : ss(other.ss) {}
    StringSet(const StringSet&& other) : ss(std::move(other.ss)) {}
    ~StringSet() {}

    // Basic set operations
    void insert(std::string&& s) {
        if (!this->contains(s)) {
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

auto main() -> int {
    std::cout << "Hello string set\n";
    return 0;
}