#include <cassert>
#include <cstddef>
#include <iostream>

#include "custom_set.hpp"

void even_set_test() {
    auto even_set_map = [](size_t x) { return x / 2; };
    auto even_set_validate = [](size_t x) { return x % 2 == 0; };
    auto inverse_fn = [](size_t x) { return x * 2; };

    CustomSet<uint32_t> even_set1(32, even_set_map, even_set_validate);
    CustomSet<uint32_t> even_set2(32, even_set_map, even_set_validate);

    // Inserting
    even_set1.insert(0);
    even_set1.insert(2);
    even_set1.insert(4);
    even_set1.insert(36); // Num bigger then declared N to ensure we are not
                          // just wasting space for "odd" idecies
    even_set2.insert(48);
    even_set2.insert(4);
    even_set2.insert(2);

    // Test insert
    assert(even_set1.contains(0));
    assert(even_set1.contains(2));
    assert(even_set1.contains(4));
    assert(even_set1.contains(36));
    assert(!even_set1.contains(48));
    assert(!even_set1.contains(50));

    // Test Union
    auto even_union = even_set1.Union(even_set2);
    assert(even_union.contains(0));
    assert(even_union.contains(4));
    assert(even_union.contains(48));
    assert(even_union.contains(36));

    // Test Intersection
    auto even_intersect = even_set1.intersection(even_set2);
    assert(even_intersect.contains(2));
    assert(even_intersect.contains(4));
    assert(!even_intersect.contains(48));
    assert(!even_intersect.contains(36));

    // Test Symetric Diff
    auto even_sym_diff = even_set1.symetric_diff(even_set2);
    assert(even_sym_diff.contains(0));
    assert(even_sym_diff.contains(36));
    assert(even_sym_diff.contains(48));
    assert(!even_sym_diff.contains(2));
    assert(!even_sym_diff.contains(4));

    // Test Subset
    assert(even_set1.is_sub_set(even_union));
    assert(even_set2.is_sub_set(even_union));
    assert(!even_set1.is_sub_set(even_sym_diff));
    assert(!even_set2.is_sub_set(even_sym_diff));

    // Test eq
    auto even_set3 = even_set1;
    assert(even_set2 != even_set1);
    assert(even_set3 == even_set1);
}

void odd_set_test() {
    auto odd_set_map = [](size_t x) { return x / 2; };
    auto odd_set_validate = [](size_t x) { return x % 2 == 1; };
    auto inverse_fn = [](size_t x) { return x * 2 + 1; };
    CustomSet<uint32_t> odd_set(32, odd_set_map, odd_set_validate);

    CustomSet<uint32_t> odd_set1(32, odd_set_map, odd_set_validate);
    CustomSet<uint32_t> odd_set2(32, odd_set_map, odd_set_validate);

    // Inserting
    odd_set1.insert(1);
    odd_set1.insert(3);
    odd_set1.insert(5);
    odd_set1.insert(37); // Num bigger then declared N to ensure we are not
                         // just wasting space for "odd" idecies
    odd_set2.insert(39);
    odd_set2.insert(5);
    odd_set2.insert(3);

    // Test insert
    assert(odd_set1.contains(1));
    assert(odd_set1.contains(3));
    assert(odd_set1.contains(5));
    assert(odd_set1.contains(37));
    assert(!odd_set1.contains(39));
    assert(!odd_set1.contains(51));

    // Test Union
    auto odd_union = odd_set1.Union(odd_set2);
    assert(odd_union.contains(1));
    assert(odd_union.contains(5));
    assert(odd_union.contains(39));
    assert(odd_union.contains(37));

    // Test Intersection
    auto odd_intersect = odd_set1.intersection(odd_set2);
    assert(odd_intersect.contains(3));
    assert(odd_intersect.contains(5));
    assert(!odd_intersect.contains(39));
    assert(!odd_intersect.contains(37));

    // Test Symetric Diff
    auto odd_sym_diff = odd_set1.symetric_diff(odd_set2);
    assert(odd_sym_diff.contains(1));
    assert(odd_sym_diff.contains(37));
    assert(odd_sym_diff.contains(39));
    assert(!odd_sym_diff.contains(3));
    assert(!odd_sym_diff.contains(5));

    // Test Subset
    assert(odd_set1.is_sub_set(odd_union));
    assert(odd_set2.is_sub_set(odd_union));
    assert(!odd_set1.is_sub_set(odd_sym_diff));
    assert(!odd_set2.is_sub_set(odd_sym_diff));

    // Test eq
    auto odd_set3 = odd_set1;
    assert(odd_set2 != odd_set1);
    assert(odd_set3 == odd_set1);
}

void char_set_test() {
    auto char_set_map = [](char c) { return static_cast<size_t>(c - 'a'); };
    auto char_set_validate = [](char c) { return c >= 'a' && c <= 'z'; };

    auto inverse_char_set_map = [](int i) {
        return static_cast<size_t>('a' + i);
    };

    CustomSet<uint32_t> char_set1(26, char_set_map, char_set_validate);
    CustomSet<uint32_t> char_set2(26, char_set_map, char_set_validate);

    // Inserting
    char_set1.insert('a');
    char_set1.insert('h');
    char_set1.insert('z');
    char_set1.insert('f'); // Num bigger then declared N to ensure we are not
                           // just wasting space for "odd" idecies
    char_set2.insert('q');
    char_set2.insert('z');
    char_set2.insert('h');

    // Test insert
    assert(char_set1.contains('a'));
    assert(char_set1.contains('h'));
    assert(char_set1.contains('z'));
    assert(char_set1.contains('f'));
    assert(!char_set1.contains('q'));
    assert(!char_set1.contains('k'));

    // Test Union
    auto char_union = char_set1.Union(char_set2);
    assert(char_union.contains('a'));
    assert(char_union.contains('z'));
    assert(char_union.contains('q'));
    assert(char_union.contains('f'));

    // Test Intersection
    auto char_intersect = char_set1.intersection(char_set2);
    assert(char_intersect.contains('h'));
    assert(char_intersect.contains('z'));
    assert(!char_intersect.contains('q'));
    assert(!char_intersect.contains('f'));

    // Test Symetric Diff
    auto char_sym_diff = char_set1.symetric_diff(char_set2);
    assert(char_sym_diff.contains('a'));
    assert(char_sym_diff.contains('f'));
    assert(char_sym_diff.contains('q'));
    assert(!char_sym_diff.contains('h'));
    assert(!char_sym_diff.contains('z'));

    // Test Subset
    assert(char_set1.is_sub_set(char_union));
    assert(char_set2.is_sub_set(char_union));
    assert(!char_set1.is_sub_set(char_sym_diff));
    assert(!char_set2.is_sub_set(char_sym_diff));

    // Test eq
    auto char_set3 = char_set1;
    assert(char_set2 != char_set1);
    assert(char_set3 == char_set1);
}

void two_char_set_test() {
    auto two_char_set_map = [](std::string c) {
        // map first and sectond char to 0-26 and then combine to get one index
        char c0 = c[0] - 'a';
        char c1 = c[1] - 'a';
        return static_cast<size_t>(c0 * 26 + c1);
    };

    auto inverse_two_char_set_map = [](int i) {
        char c1 = i % 26 + 'a';
        char c0 = i / 26 + 'a';

        std::string str = "";
        str.push_back(c0);
        str.push_back(c1);
        return str;
    };

    auto two_char_set_validate = [](std::string c) {
        return c.size() == 2 && c[0] >= 'a' && c[0] <= 'z' && c[1] >= 'a' &&
               c[1] <= 'z';
    };

    CustomSet<std::string> dc1(26 * 26, two_char_set_map,
                               two_char_set_validate);
    // Insert Contains
    std::string s1 = "aa";
    dc1.insert(s1);
    std::string s2 = "zz";
    dc1.insert(s2);
    assert(dc1.contains("aa"));
    assert(dc1.contains("zz"));
    std::string s3 = "az";
    assert(!dc1.contains(s3));

    CustomSet<std::string> dc2(26 * 26, two_char_set_map,
                               two_char_set_validate);
    dc2.insert("aa");
    dc2.insert("bb");
    assert(dc2.contains("aa"));
    assert(dc2.contains("bb"));

    // Union Test
    auto dc_union = dc1.Union(dc2);
    assert(dc_union.contains("aa"));
    assert(dc_union.contains(s2));
    assert(dc_union.contains("bb"));
    assert(!dc_union.contains("az"));

    // Intersection Test
    auto dc_inter = dc1.intersection(dc2);
    assert(dc_inter.contains("aa"));
    assert(!dc_inter.contains(s2));
    assert(!dc_inter.contains("bb"));
    assert(!dc_union.contains("az"));

    // Symdiff Test
    auto dc_symdiff = dc1.symetric_diff(dc2);
    assert(!dc_symdiff.contains("aa"));
    assert(dc_symdiff.contains("zz"));
    assert(dc_symdiff.contains("bb"));
    assert(!dc_symdiff.contains("az"));

    // Eq test
    auto dc3 = dc1;
    assert(dc3 == dc1);
    assert(dc1 != dc_symdiff);

    // Subset test
    assert(dc1.is_sub_set(dc_union));
    assert(dc2.is_sub_set(dc_union));
    assert(!dc2.is_sub_set(dc_symdiff));
}

auto main() -> int {
    even_set_test();
    odd_set_test();
    char_set_test();
    two_char_set_test();

    std::cout << "All tests passed with flying colors" << "\n";
    return 0;
}
