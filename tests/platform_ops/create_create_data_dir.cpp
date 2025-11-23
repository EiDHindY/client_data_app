#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()

#include "create.h"
#include "catch_amalgamated.hpp"
#include "infrastructure.h"

using namespace platform_ops_create;


TEST_CASE("create_data_dir creates the data directory if missing") {
    std::filesystem::path base = std::filesystem::temp_directory_path() / "dir_creation_test_real";
    std::filesystem::remove_all(base); // clean start

    REQUIRE(create_data_dir(base) == true);

    std::filesystem::path expected = base / std::string(infrastructure_names::DATA_DIR_NAME);
    REQUIRE(std::filesystem::exists(expected));
    REQUIRE(std::filesystem::is_directory(expected));

    std::filesystem::remove_all(base); // cleanup
}

TEST_CASE("create_data_dir returns false if directory already exists") {
    std::filesystem::path base = std::filesystem::temp_directory_path() / "dir_exists_test_real";
    std::filesystem::path dir = base / std::string(infrastructure_names::DATA_DIR_NAME);
    std::filesystem::create_directories(dir);

    REQUIRE(create_data_dir(base) == false);

    std::filesystem::remove_all(base); // cleanup
}

TEST_CASE("create_data_dir successfully creates nested directories") {
    std::filesystem::path base = std::filesystem::temp_directory_path() / "dir_nested_test_real" / "nested1" / "nested2";
    std::filesystem::remove_all(base);
    REQUIRE(create_data_dir(base) == true);

    auto expected = base / std::string(infrastructure_names::DATA_DIR_NAME);
    REQUIRE(std::filesystem::exists(expected));
    REQUIRE(std::filesystem::is_directory(expected));
    std::filesystem::remove_all(std::filesystem::temp_directory_path() / "dir_nested_test_real"); // Clean up all
}



