// controller/main_use_cases/handle_start_program.cpp

#include "controller/main_use_cases/handle_start_program.h" // Declaration of start_program() function
#include "cli/main_screens/main_screens.h" // Declaration of show_menu_screen()
#include "controller/helper/h_handle_file_exist.h" // Declaration of handle_file_exist() helper
#include "platform_ops/paths/paths.h"
#include "services/inputs/inputs.h"
#include <iostream>
#include <print>

namespace start_program_controller {
// Entry point for starting the program’s main use case
menu_options::enMenuOptions start_program() {
  // Retrieve the directory containing the running executable.
  // Data type: std::filesystem::path - manages absolute file system paths.
  // Memory: Stack-allocated path object; passed by const reference to avoid
  // copies. CPU: Queries OS for executable location and caches result.
  std::filesystem::path exe_dir = platform_ops_paths::get_exe_dir_path();

  // Ensure the data directory structure and original file exist.
  // Memory: exe_dir passed by const reference to minimize allocations.
  // CPU: System calls (stat, mkdir, open) to check/create filesystem objects.
  h_controller::handle_file_exist(exe_dir);

  // Display the main menu options to the user.
  // Memory: Stack-allocated strings for menu text (const data section).
  // CPU: Outputs directly to stdout via std::print.
  main_screens::show_menu_screen();

  // Variable to store the user's menu choice after validation.
  // Data type: unsigned short - range [0, 65535], sufficient for 1-6 menu
  // options. Memory: Stack-allocated (2 bytes).
  unsigned short operation_number{};

  // String stream for parsing user input line-by-line.
  // Data type: std::istringstream - input stream backed by a std::string.
  // Memory: Initially empty; will hold one line of user input per iteration.
  // CPU: Parses numeric values using operator>> (pattern matching in buffer).
  std::istringstream input{};

  // Stores one line of raw user input from standard input.
  // Data type: std::string - dynamic character buffer.
  // Memory: Heap-allocated; grows/shrinks with user input length.
  // CPU: Reads from stdin until newline encountered.
  std::string line{};

  // Tracks the result of the most recent input validation attempt.
  // Data type: inputs::enReadResult - enumeration (Invalid_input, Out_of_range,
  // pass). Memory: Stack-allocated enum value (typically 1-4 bytes).
  inputs::enReadResult user_choice = inputs::enReadResult::Invalid_input;

  // Prompt the user for menu input.
  std::print("Please choose what operation you want? [1 - 6]\n");

  // Loop until valid input is successfully parsed and validated.
  // CPU: Repeats std::getline calls and input stream parsing until pass
  // condition.
  while (user_choice != inputs::enReadResult::pass) {
    // Read one complete line from standard input, including spaces and special
    // characters. Memory: Allocates/reallocates line string as needed; previous
    // content discarded. CPU: Blocks on I/O until newline encountered.
    std::getline(std::cin, line);

    // Create a new string stream from the current input line.
    // Memory: Constructs fresh istringstream; old input object discarded.
    // CPU: Initializes internal buffer with line content; read position at
    // start.
    input = std::istringstream(line);

    // Attempt to extract and validate a number from [1, 6] from the stream.
    // Data type: inputs::enReadResult - indicates extraction success/failure
    // and range check. Memory: operation_number modified only if extraction
    // succeeds. CPU: Pattern matching within stream buffer for numeric
    // conversion.
    user_choice = inputs::read_num_from_to(input, 1, 6, operation_number);

    // Check if the extraction failed (non-numeric input or stream error).
    if (user_choice == inputs::enReadResult::Invalid_input) {
      // Inform user of invalid input and restart loop.
      std::print("Please enter a valid number from 1 to 6\n\n");
      continue;
    }

    // Check if extraction succeeded but the value is outside the valid range
    // [1, 6].
    if (user_choice == inputs::enReadResult::Out_of_range) {
      // Inform user of out-of-range value and restart loop.
      std::print("Please enter a number within the range 1 to 6\n\n");
      continue;
    }

    // If no error above, mark input as valid and exit loop.
    user_choice = inputs::enReadResult::pass;
  }

  // Cast the validated unsigned short to the corresponding menu option
  // enumeration. Data type: menu_options::enMenuOptions - enum with 6 possible
  // values (1-6 mapped to options). Memory: Stack-allocated; stored temporarily
  // before return. CPU: Direct value cast; no computation required.
  menu_options::enMenuOptions result =
      static_cast<menu_options::enMenuOptions>(operation_number);

  // Return the user's menu selection to the caller.
  // Memory: result transferred to caller; local variables destroyed.
  return result;
}
} // namespace start_program_controller
