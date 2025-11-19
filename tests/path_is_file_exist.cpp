

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()

#include "catch_amalgamated.hpp"
#include <filesystem>
#include <fstream>

// Helper to create and destroy a test file
void create_test_file(const std::string& filename) {
    std::ofstream file(filename);
    file << "some content";
}

void remove_test_file(const std::string& filename) {
    std::filesystem::remove(filename);
}

bool is_file_exist(const std::filesystem::path& file_path)
{
    return std::filesystem::is_regular_file(file_path);
}

TEST_CASE("is_file_exist returns true for existing regular file") {
    const std::string filename = "test_file_exist.txt";
    create_test_file(filename);

    REQUIRE(is_file_exist(filename) == true);

    remove_test_file(filename);
}

TEST_CASE("is_file_exist returns false for non-existent file") {
    const std::string filename = "some_missing_file.txt";
    REQUIRE(is_file_exist(filename) == false);
}

TEST_CASE("is_file_exist returns false for directory") {
    const std::filesystem::path dir = std::filesystem::temp_directory_path(); // uses system temp dir
    REQUIRE(is_file_exist(dir) == false);
}

