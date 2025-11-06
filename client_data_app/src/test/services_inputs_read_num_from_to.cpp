// test/services_inputs_read_num_from_to.cpp

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "include/catch.hpp"

#include "../services/inputs/inputs.h"
#include <sstream>



// 1. Valid input in range
TEST_CASE("Input in range returns pass", "[read_num_from_to]") {
    std::istringstream input("42");
    unsigned short out = 0;
    auto result = inputs::read_num_from_to(input, 1, 100, out);
    REQUIRE(result == inputs::enReadResult::pass);
    REQUIRE(out == 42);
}

// 2. Input equals lower bound
TEST_CASE("Input equals lower bound returns pass", "[read_num_from_to]") {
    std::istringstream input("1");
    unsigned short out = 0;
    auto result = inputs::read_num_from_to(input, 1, 100, out);
    REQUIRE(result == inputs::enReadResult::pass);
    REQUIRE(out == 1);
}

// 3. Input equals upper bound
TEST_CASE("Input equals upper bound returns pass", "[read_num_from_to]") {
    std::istringstream input("100");
    unsigned short out = 0;
    auto result = inputs::read_num_from_to(input, 1, 100, out);
    REQUIRE(result == inputs::enReadResult::pass);
    REQUIRE(out == 100);
}

// 4. Input below lower bound
TEST_CASE("Input below lower bound returns Out_of_range", "[read_num_from_to]") {
    std::istringstream input("0");
    unsigned short out = 0;
    auto result = inputs::read_num_from_to(input, 1, 100, out);
    REQUIRE(result == inputs::enReadResult::Out_of_range);
}

// 5. Input above upper bound
TEST_CASE("Input above upper bound returns Out_of_range", "[read_num_from_to]") {
    std::istringstream input("101");
    unsigned short out = 0;
    auto result = inputs::read_num_from_to(input, 1, 100, out);
    REQUIRE(result == inputs::enReadResult::Out_of_range);
}

// 6. Non-numeric input
TEST_CASE("Non-numeric input returns Invalid_input", "[read_num_from_to]") {
    std::istringstream input("hello");
    unsigned short out = 0;
    auto result = inputs::read_num_from_to(input, 1, 100, out);
    REQUIRE(result == inputs::enReadResult::Invalid_input);
}

// 7. Negative number input
TEST_CASE("Negative input returns Invalid_input", "[read_num_from_to]") {
    std::istringstream input("-5");
    unsigned short out = 0;
    auto result = inputs::read_num_from_to(input, 1, 100, out);
    REQUIRE(result == inputs::enReadResult::Out_of_range);
}

// 8. Overflow number (> USHRT_MAX)
TEST_CASE("Input overflow returns Invalid_input", "[read_num_from_to]") {
    std::istringstream input("70000");
    unsigned short out = 0;
    auto result = inputs::read_num_from_to(input, 1, 100, out);
    REQUIRE(result == inputs::enReadResult::Out_of_range);
}

// 9. Empty input (simulates pressing Enter on console)
TEST_CASE("Empty input returns Invalid_input", "[read_num_from_to]") {
    std::istringstream input("");
    unsigned short out = 0;
    auto result = inputs::read_num_from_to(input, 1, 100, out);
    REQUIRE(result == inputs::enReadResult::Invalid_input);
}

