#define CATCH_CONFIG_MAIN // This tells Catch to provide a main()

#include "catch_amalgamated.hpp"
#include "platform_ops/paths/paths.h"
#include <filesystem>

using namespace platform_ops_paths;

TEST_CASE(
    "get_original_file_path creates expected path from simple exe directory") {
  std::filesystem::path base = "C:/MyApp";
  std::filesystem::path expected = "C:/MyApp/data/clients.csv";
  REQUIRE(get_original_file_path(base) == expected);
}

TEST_CASE("get_original_file_path works for relative exe directory") {
  std::filesystem::path base = "bin";
  std::filesystem::path expected = "bin/data/clients.csv";
  REQUIRE(get_original_file_path(base) == expected);
}

TEST_CASE("get_original_file_path works for path with trailing separator") {
  std::filesystem::path base = "C:/MyApp/";
  std::filesystem::path expected = "C:/MyApp/data/clients.csv";
  REQUIRE(get_original_file_path(base) == expected);
}

TEST_CASE("get_original_file_path works for root directory") {
  std::filesystem::path base = "/";
  std::filesystem::path expected = "/data/clients.csv";
  REQUIRE(get_original_file_path(base) == expected);
}

TEST_CASE("get_original_file_path works for empty exe directory path") {
  std::filesystem::path base; // empty
  std::filesystem::path expected = "data/clients.csv";
  REQUIRE(get_original_file_path(base) == expected);
}

TEST_CASE("get_original_file_path works for Windows-style path") {
  std::filesystem::path base = std::filesystem::path("C:") / "ProgramFiles";
  std::filesystem::path expected = base / "data" / "clients.csv";
  // Compare parent_path() if needed, or use .lexically_normal() for
  // normalization
  REQUIRE(get_original_file_path(base).lexically_normal() ==
          expected.lexically_normal());
}