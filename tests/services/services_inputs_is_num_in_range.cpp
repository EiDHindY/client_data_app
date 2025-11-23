// / test/services_inputs_is_num_in_range.cpp
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "catch_amalgamated.hpp"
#include <limits>
#include "h_inputs.h"





// Test the range function for menu-choice style input (1..6)
TEST_CASE("is_num_in_range: menu range 1 to 6", "[is_num_in_range]") {
    // Lower bound: should reject 0
    REQUIRE(inputs_helper::is_num_in_range(0, 1, 6) == false);

    // In range
    REQUIRE(inputs_helper::is_num_in_range(1, 1, 6) == true);
    REQUIRE(inputs_helper::is_num_in_range(3, 1, 6) == true);
    REQUIRE(inputs_helper::is_num_in_range(6, 1, 6) == true);

    // Above upper bound
    REQUIRE(inputs_helper::is_num_in_range(7, 1, 6) == false);
    REQUIRE(inputs_helper::is_num_in_range(100, 1, 6) == false);

    // Edge cases if someone tries boundaries not intended
    REQUIRE(inputs_helper::is_num_in_range(USHRT_MAX, 1, 6) == false);

    // Changing bounds
    REQUIRE(inputs_helper::is_num_in_range(1, 1, 1) == true);
    REQUIRE(inputs_helper::is_num_in_range(1, 2, 6) == false);
    REQUIRE(inputs_helper::is_num_in_range(6, 1, 6) == true);
    REQUIRE(inputs_helper::is_num_in_range(6, 2, 6) == true);
    REQUIRE(inputs_helper::is_num_in_range(5, 2, 6) == true);

    // Big range: only positive numbers allowed
    REQUIRE(inputs_helper::is_num_in_range(0, 1, USHRT_MAX) == false);
    REQUIRE(inputs_helper::is_num_in_range(1, 1, USHRT_MAX) == true);
    REQUIRE(inputs_helper::is_num_in_range(USHRT_MAX, 1, USHRT_MAX) == true);
    REQUIRE(inputs_helper::is_num_in_range(USHRT_MAX, 2, USHRT_MAX) == true);
    REQUIRE(inputs_helper::is_num_in_range(1, USHRT_MAX, USHRT_MAX) == false);
}