#pragma once
#include <string>
#include <string_view>

namespace infrastructure_names {
// DATA_DIR_NAME: name of the folder where data files are stored
// constexpr: evaluated at compile time, no runtime allocation
// std::string_view: just a pointer+length, lives in static memory
constexpr std::string_view DATA_DIR_NAME = "data";

// ORIGINAL_FILE_NAME: filename for the primary CSV data file
// Stored in read-only data segment; no heap or stack use at runtime
constexpr std::string_view ORIGINAL_FILE_NAME = "clients.csv";

// TEMP_FILE_NAME: filename for any temporary CSV operations
constexpr std::string_view TEMP_FILE_NAME = "temp.csv";
} // namespace infrastructure_names

namespace menu_options {
// Strongly typed enum for menu actions; avoids implicit conversions
enum class enMenuOptions {
  show_client_list = 1,   // Display all clients
  add_new_client = 2,     // Prompt to add a new client
  delete_client = 3,      // Remove an existing client
  update_client_info = 4, // Modify client details
  find_client = 5,        // Search for a specific client
  exit = 6,               // Terminate the application
};
} // namespace menu_options

struct stClientData {
  std::string account_number;
  std::string pass_code;
  std::string phone_no;
  std::string name;
  double account_balance;
  bool delete_mark = false;
};
