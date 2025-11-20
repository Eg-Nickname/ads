#include <cassert>
#include <iostream>
#include <stack>
#include <string>

// Algorithm implementation
std::string bignum_add(std::string n1, std::string n2);
std::stack<char> build_digit_stack(std::string s);
// Algorithm tests
void add_even_len_without_carry();
void add_even_len_with_carry();
void add_uneven_without_carry();
void add_uneven_with_carry();

auto main() -> int {
    add_even_len_without_carry();
    add_even_len_with_carry();
    add_uneven_without_carry();
    add_uneven_with_carry();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

std::stack<char> build_digit_stack(std::string s) {
    std::stack<char> stack{};
    // TODO remove zeros from begining of num
    for (auto c : s) {
        assert(c >= '0' && c <= '9'); // check if ourstring has only didgits
        stack.push(c);
    }
    return stack;
}

std::string bignum_add(std::string n1, std::string n2) {
    std::stack<char> n1_stack{}, n2_stack{}, output_stack{};
    n1_stack = build_digit_stack(n1);
    n2_stack = build_digit_stack(n2);

    // Add all matching digits
    char carry = 0;
    while (!n1_stack.empty() && !n2_stack.empty()) {
        char lhs = n1_stack.top() - '0';
        n1_stack.pop();

        char rhs = n2_stack.top() - '0';
        n2_stack.pop();

        char sum = rhs + lhs + carry;
        carry = sum / 10;

        output_stack.push(sum % 10 + '0');
    }

    // Add rest of digits from n1 with carry
    while (!n1_stack.empty()) {
        char lhs = n1_stack.top() - '0';
        n1_stack.pop();

        char sum = lhs + carry;
        carry = sum / 10;
        output_stack.push(sum % 10 + '0');
    }

    // Add rest of digits from n2 with carry
    while (!n2_stack.empty()) {
        char lhs = n2_stack.top() - '0';
        n2_stack.pop();

        char sum = lhs + carry;
        carry = sum / 10;
        output_stack.push(sum % 10 + '0');
    }

    // Add leftover carry digit
    if (carry > 0) {
        output_stack.push(carry + '0');
    }

    // put digits into string
    std::string output_str = std::string();
    output_str.reserve(output_stack.size());

    while (!output_stack.empty()) {
        char c = output_stack.top();
        output_str += c;
        output_stack.pop();
    }

    return output_str;
}

void add_even_len_without_carry() {
    assert(bignum_add("1", "2") == "3");
    assert(bignum_add("12", "21") == "33");
    assert(bignum_add("12", "77") == "89");
    assert(bignum_add("10000000000000000000000", "18888888800000000000000") ==
           "28888888800000000000000");
    assert(bignum_add("12345678", "87654321") == "99999999");
}

void add_even_len_with_carry() {
    assert(bignum_add("22", "19") == "41");
    assert(bignum_add("333", "199") == "532");
    assert(bignum_add("3000000000000000000000000000033",
                      "1000000000000000000000000000099") ==
           "4000000000000000000000000000132");
    assert(bignum_add("99", "11") == "110");
    assert(bignum_add("99999999999", "10000000002") == "110000000001");
    assert(bignum_add("512742825481643", "638561937592299") ==
           "1151304763073942");
}

void add_uneven_without_carry() {
    assert(bignum_add("11", "2") == "13");
    assert(bignum_add("2", "11") == "13");
    assert(bignum_add("30001", "10008") == "40009");
    assert(bignum_add("1000000000000", "4000000000099") == "5000000000099");
    // assert(bignum_add("1", "2") == "3");
    // assert(bignum_add("1", "2") == "3");
}

void add_uneven_with_carry() {
    assert(bignum_add("11", "9") == "20");
    assert(bignum_add("9", "12") == "21");
    assert(bignum_add("111", "9") == "120");
    assert(bignum_add("11", "999") == "1010");
}
