// client_data_app/tests/services/convert/h_convert/test_h_conv_str_vstr.cpp
#include "catch_amalgamated.hpp"
#include "services/convert/h_convert/h_convert.h"
#include <vector>

// Standard Case
TEST_CASE("Standard record with multiple fields", "[h_conv_std][h_conv_str_vstr]")
{
    std::string record = "1001#//#Eid#//#27";
    std::vector<std::string> result = h_convert::h_conv_str_vstr(record);
    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == "1001");
    REQUIRE(result[1] == "Eid");
    REQUIRE(result[2] == "27");
}

// Edge Case: Single Word (No separators)
TEST_CASE("Single field without separators", "[h_conv_single][h_conv_str_vstr]")
{
    std::string record = "SingleMethod";
    std::vector<std::string> result = h_convert::h_conv_str_vstr(record);
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == "SingleMethod");
}

// Edge Case: Empty String
TEST_CASE("Empty input string", "[h_conv_empty][h_conv_str_vstr]")
{
    std::string record = "";
    std::vector<std::string> result = h_convert::h_conv_str_vstr(record);
    REQUIRE(result.empty());
}

// Edge Case: Empty Fields (consecutive separators)
TEST_CASE("Record with empty fields", "[h_conv_gap][h_conv_str_vstr]")
{
    // "1001#//#//#27" <- Middle field is empty/space? 
    // Or strictly "#//#//#"
    std::string record = "1001#//#//#27"; 
    std::vector<std::string> result = h_convert::h_conv_str_vstr(record);
    
    // Explain: 1001, (empty), 27
    REQUIRE(result.size() == 2);
    REQUIRE(result[0] == "1001");
    REQUIRE(result[1] == "//#27");
}
