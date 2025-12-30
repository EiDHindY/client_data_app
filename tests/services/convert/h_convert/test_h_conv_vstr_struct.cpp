// test/services/convert/h_convert/test_ho_conv_vstr_struct.cpp
#include "catch_amalgamated.hpp"
#include "services/convert/h_convert/h_convert.h"
#include <vector>

// 1. Standard Case
TEST_CASE("Convert standard vector to ClientData",
          "[h_conv_struct][h_conv_valid]") {
  // 1. Prepare Data
  std::vector<std::string> vstr = {"1001", "1234", "010101010", "Eid Hindy",
                                   "5000.50"};

  // 2. Call Function
  client_data_structure::stClientData result =
      h_convert::h_conv_vstr_struct(vstr);

  // 3. Verify
  REQUIRE(result.account_number == "1001");
  REQUIRE(result.pass_code == "1234");
  REQUIRE(result.phone_no == "010101010");
  REQUIRE(result.name == "Eid Hindy");
  REQUIRE(result.account_balance == 500.50);
}

// 2. Precision Case
TEST_CASE("Convert vector with high precision balance",
          "[h_conv_struct][h_conv_precision]") {
  std::vector<std::string> vstr = {"1002", "9999", "012345678", "Rich Guy",
                                   "99999.99"};

  auto result = h_convert::h_conv_vstr_struct(vstr);

  REQUIRE(result.account_balance == 99999.99);
}