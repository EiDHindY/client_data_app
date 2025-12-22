#define CATCH_CONFIG_MAIN // This tells Catch to provide a main()

#include "catch_amalgamated.hpp"
#include "paths.h"
#include <filesystem>
#include <string>

using namespace platform_ops_paths;

// You must run these where you know your exe path -- cannot mock
// GetModuleFileNameW in standard C++.

// Helper to check if path ends with expected directory (for basic real-world
// verification)
bool path_ends_with(const std::filesystem::path &actual,
                    const std::filesystem::path &expected_tail) {
  auto actual_iter = actual.end();
  auto expected_iter = expected_tail.end();

  // Walk backwards for comparison
  while (expected_iter != expected_tail.begin()) {
    if (actual_iter == actual.begin() || *--actual_iter != *--expected_iter)
      return false;
  }
  return true;
}

TEST_CASE("get_exe_dir_path returns a valid directory") {
  auto exe_dir = get_exe_dir_path();
  REQUIRE(std::filesystem::exists(exe_dir));
  REQUIRE(std::filesystem::is_directory(exe_dir));
}

TEST_CASE("get_exe_dir_path contains the running exe", "[integration]") {
  auto exe_dir = get_exe_dir_path();
  // Test if running exe is inside directory returned
  // Note: You'd need GetModuleFileNameW to get exe name too; here, check some
  // known file in dir.
  std::string expected_file = "Client_data_app.exe";
  bool found = false;
  for (const auto &entry : std::filesystem::directory_iterator(exe_dir)) {
    if (entry.path().filename() == expected_file)
      found = true;
  }
  REQUIRE(found); // Should find our exe in its own directory (works if exe is
                  // unchanged)
}

TEST_CASE("get_exe_dir_path does not throw under normal conditions") {
  REQUIRE_NOTHROW(get_exe_dir_path());
}

// Edge case: validate tail part
TEST_CASE("get_exe_dir_path matches expected tail directory", "[integration]") {
  auto exe_dir = get_exe_dir_path();
  // Assuming in development/build folder "Client_data_app"
  std::filesystem::path expected_tail = "Debug";
  REQUIRE(path_ends_with(exe_dir, expected_tail));
}

// Manual/Visual test for output (run to view actual value; must confirm output
// by inspection)
TEST_CASE("get_exe_dir_path prints path for inspection", "[visual]") {
  auto exe_dir = get_exe_dir_path();
  INFO("Exe directory: " << exe_dir.string());
  SUCCEED(); // You inspect output manually
}
