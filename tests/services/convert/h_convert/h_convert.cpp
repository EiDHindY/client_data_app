#include "catch_amalgamated.hpp"
#include <string_view>
#include <vector>
#include "services/convert/h_convert/h_convert.h"

TEST_CASE("detect_delim basic functionality", "[h_convert]") {
    std::string_view delim = "#//#";
    std::vector<short> indexes;

    SECTION("Finds multiple delimiters in standard string") {
        // 01234567890
        // A#//#B#//#C
        std::string_view str = "A#//#B#//#C";
        h_convert::detect_delim(str, delim, indexes);
        
        REQUIRE(indexes.size() == 2);
        REQUIRE(indexes[0] == 1);
        REQUIRE(indexes[1] == 6);
    }
}

TEST_CASE("detect_delim edge cases", "[h_convert]") {
    std::string_view delim = "#//#";
    std::vector<short> indexes;

    SECTION("No delimiters present") {
        h_convert::detect_delim("HelloWorld", delim, indexes);
        REQUIRE(indexes.empty());
    }

    SECTION("Empty string") {
        h_convert::detect_delim("", delim, indexes);
        REQUIRE(indexes.empty());
    }
    
    SECTION("Delimiter at the very start") {
        // 012345678
        // #//#Start
        h_convert::detect_delim("#//#Start", delim, indexes);
        REQUIRE(indexes.size() == 1);
        REQUIRE(indexes[0] == 0);
    }

    SECTION("Delimiter at the very end") {
        // 01234567
        // End#//#
        h_convert::detect_delim("End#//#", delim, indexes);
        REQUIRE(indexes.size() == 1);
        REQUIRE(indexes[0] == 3);
    }

    SECTION("Consecutive delimiters") {
        // 01234567
        // #//#//#
        h_convert::detect_delim("#//#//#", delim, indexes);
        REQUIRE(indexes.size() == 1);
        REQUIRE(indexes[0] == 0);
    }
}
