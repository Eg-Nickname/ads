#include <iostream>

#include "string_set.hpp"

class StringSetTest {
    public:
    static void test_insert_contains() {
        auto ss = StringSet();
        ss.insert("kotek");
        assert(ss.contains("kotek"));
        ss.insert("psotek");
        assert(ss.contains("psotek"));
        assert(!ss.contains("klopotek"));
    }

    static void test_remove() {
        auto ss = StringSet();
        ss.insert("kotek");
        ss.insert("psotek");
        ss.insert("klopotek");
        assert(ss.contains("psotek"));
        ss.remove("psotek");
        assert(!ss.contains("psotek"));
        assert(ss.contains("kotek"));
        assert(ss.contains("klopotek"));
    }

    static void test_duplicates() {
        auto ss = StringSet();
        ss.insert("kotek");
        ss.insert("kotek");
        ss.remove("kotek");
        assert(!ss.contains("kotek"));
        assert(ss.ss.size() == 0);
    }
};

auto main() -> int {
    StringSetTest::test_insert_contains();
    StringSetTest::test_remove();
    StringSetTest::test_duplicates();

    std::cout << "All string set tests passed\n";
    return 0;
}