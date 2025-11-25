// test/services_inputs_try_read_num_test.cpp
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "catch_amalgamated.hpp"
#include <sstream>
#include "services/inputs/h_inputs.h"

TEST_CASE("try_read_num: valid positive integer", "[try_read_num]") {
    std::istringstream input("123");
    unsigned short value = 0;
    bool result = inputs_helper::try_read_num(input, value);
    REQUIRE(result == true);
    REQUIRE(value == 123);
}

TEST_CASE("try_read_num: zero is valid", "[try_read_num]") {
    std::istringstream input("0");
    unsigned short value = 42; // nonzero start to check assignment
    bool result = inputs_helper::try_read_num(input, value);
    REQUIRE(result == true);
    REQUIRE(value == 0);
}


TEST_CASE("try_read_num: non-numeric input is rejected", "[try_read_num]") {
    std::istringstream input("abc");
    unsigned short value = 99;
    bool result = inputs_helper::try_read_num(input, value);
    REQUIRE(result == false);
}

TEST_CASE("try_read_num: empty string is rejected", "[try_read_num]") {
    std::istringstream input("");
    unsigned short value = 99;
    bool result = inputs_helper::try_read_num(input, value);
    REQUIRE(result == false);
}

TEST_CASE("try_read_num: leading/trailing whitespace", "[try_read_num]") {
    std::istringstream input("   47   ");
    unsigned short value = 0;
    bool result = inputs_helper::try_read_num(input, value);
    REQUIRE(result == true);
    REQUIRE(value == 47);
}