#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()


#include "platform_ops/create/create.h"
#include <catch2/catch.hpp>
#include "infrastructure/infrastructure.h" // For DATA_DIR_NAME and ORIGINAL_FILE_NAME
#include <filesystem>
#include <fstream>

using namespace platform_ops_create;


TEST_CASE("create_original_file creates the file in expected location", "[create_original_file]") {
    std::filesystem::path base = std::filesystem::temp_directory_path() / "create_file_test_real";
    std::filesystem::remove_all(base);

    // First create the data dir to ensure it exists before creating the file.
    std::filesystem::create_directories(base / std::string(infrastructure_names::DATA_DIR_NAME));

    REQUIRE_NOTHROW(create_original_file(base));

    std::filesystem::path expected =
        base / std::string(infrastructure_names::DATA_DIR_NAME) / std::string(infrastructure_names::ORIGINAL_FILE_NAME);

    REQUIRE(std::filesystem::exists(expected));
    REQUIRE(std::filesystem::is_regular_file(expected));

    std::filesystem::remove_all(base);
}

TEST_CASE("create_original_file throws if data directory does not exist", "[create_original_file]") {
    std::filesystem::path base = std::filesystem::temp_directory_path() / "missing_dir_create_file_test";
    std::filesystem::remove_all(base);

    // Do not create directory; function should throw
    REQUIRE_THROWS_AS(create_original_file(base), std::runtime_error);

    std::filesystem::remove_all(base);
}

TEST_CASE("create_original_file can overwrite existing file with same name", "[create_original_file]") {
    std::filesystem::path base = std::filesystem::temp_directory_path() / "overwrite_create_file_test";
    std::filesystem::remove_all(base);
    std::filesystem::create_directories(base / std::string(infrastructure_names::DATA_DIR_NAME));

    std::filesystem::path file_path =
        base / std::string(infrastructure_names::DATA_DIR_NAME) / std::string(infrastructure_names::ORIGINAL_FILE_NAME);

    // Create the file first
    {
        std::ofstream test_file(file_path);
        test_file << "Old content";
    }
    // Should not throw, should overwrite
    REQUIRE_NOTHROW(create_original_file(base));

    // File should still exist after overwrite
    REQUIRE(std::filesystem::exists(file_path));
    std::filesystem::remove_all(base);
}


