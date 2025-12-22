// tests/file_ops/test_get_all_clients.cpp
#include "catch_amalgamated.hpp"
#include "file_ops/file_ops.h"
#include <filesystem> // For std::filesystem functions
#include <fstream>    // For file creation/manipulation
#include <string>
#include <vector>

using namespace file_ops;
// Include your get_all_clients function here
// #include "your_header.hpp"

TEST_CASE("File with multiple client lines") {
  std::string tempFileName = "clients_multi.txt";
  {
    std::ofstream out(tempFileName);
    out << "Alice\nBob\nCharlie\n";
  }
  auto result = get_all_clients(tempFileName);
  REQUIRE(result.size() == 3);
  REQUIRE(result[0] == "Alice");
  REQUIRE(result[1] == "Bob");
  REQUIRE(result[2] == "Charlie");
  std::filesystem::remove(tempFileName);
}

TEST_CASE("File with single client line") {
  std::string tempFileName = "clients_single.txt";
  {
    std::ofstream out(tempFileName);
    out << "Alice\n";
  }
  auto result = get_all_clients(tempFileName);
  REQUIRE(result.size() == 1);
  REQUIRE(result[0] == "Alice");
  std::filesystem::remove(tempFileName);
}

TEST_CASE("File is empty") {
  std::string tempFileName = "clients_empty.txt";
  {
    std::ofstream out(tempFileName);
    // No write, file is empty
  }
  auto result = get_all_clients(tempFileName);
  REQUIRE(result.empty());
  std::filesystem::remove(tempFileName);
}

TEST_CASE("File does not exist") {
  std::string badPath = "no_such_file.txt";
  auto result = get_all_clients(badPath);
  REQUIRE(result.empty());
}

TEST_CASE("Access denied file (might fail on test setup)") {
  // NOTE: This path is for demonstration. It needs to be inaccessible on your
  // system. On Windows, "C:\\Windows\\System32\\config\\SAM" is usually locked.
  std::string lockedFile = "C:\\Windows\\System32\\config\\SAM";
  auto result = get_all_clients(lockedFile);
  REQUIRE(result.empty());
}

TEST_CASE("File with special characters and blank lines") {
  std::string tempFileName = "clients_special.txt";
  {
    std::ofstream out(tempFileName);
    out << "A!@#\n \nBob\t\nCharlie\n";
  }
  auto result = get_all_clients(tempFileName);
  REQUIRE(result.size() == 4);
  REQUIRE(result[0] == "A!@#");
  REQUIRE(result[1] == " ");
  REQUIRE(result[2] == "Bob\t");
  REQUIRE(result[3] == "Charlie");
  std::filesystem::remove(tempFileName);
}

TEST_CASE("Very large client file") {
  std::string tempFileName = "clients_large.txt";
  int numLines = 10000;
  {
    std::ofstream out(tempFileName);
    for (int i = 0; i < numLines; ++i) {
      out << "Client" << i << "\n";
    }
  }
  auto result = get_all_clients(tempFileName);
  REQUIRE(result.size() == numLines);
  REQUIRE(result[0] == "Client0");
  REQUIRE(result[numLines - 1] == "Client9999");
  std::filesystem::remove(tempFileName);
}

TEST_CASE("File with no newline at end") {
  std::string tempFileName = "clients_nonl.txt";
  {
    std::ofstream out(tempFileName);
    out << "Alice";
    // No trailing newline
  }
  auto result = get_all_clients(tempFileName);
  REQUIRE(result.size() == 1);
  REQUIRE(result[0] == "Alice");
  std::filesystem::remove(tempFileName);
}
