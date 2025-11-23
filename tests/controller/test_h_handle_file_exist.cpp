#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()

#include "catch_amalgamated.hpp"
#include <filesystem>
#include "infrastructure/infrastructure.h"
#include "controller/helper/h_handle_file_exist.h"
#include <fstream>

using namespace h_controller;


// Helper for isolated test env
struct TestPathEnv {
    std::filesystem::path temp_dir;
    std::filesystem::path data_dir;
    std::filesystem::path file_path;

    TestPathEnv(const std::string& subdir) {
        temp_dir = std::filesystem::temp_directory_path() / subdir;
        data_dir = temp_dir / std::string(infrastructure_names::DATA_DIR_NAME);
        file_path = data_dir / std::string(infrastructure_names::ORIGINAL_FILE_NAME);
        std::filesystem::remove_all(temp_dir);
    }
    ~TestPathEnv() { std::filesystem::remove_all(temp_dir); }
};

TEST_CASE("handle_file_exist does nothing if file already exists") {
    TestPathEnv env("handle_file_exist_exists");
    std::filesystem::create_directories(env.data_dir);
    {
        std::ofstream file(env.file_path);
        file << "test data";
    }
    REQUIRE(std::filesystem::exists(env.file_path));

    handle_file_exist(env.temp_dir);

    REQUIRE(std::filesystem::exists(env.data_dir));
    REQUIRE(std::filesystem::exists(env.file_path));
    std::ifstream file(env.file_path);
    std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    REQUIRE(contents == "test data");
}

TEST_CASE("handle_file_exist creates data directory and file if missing") {
    TestPathEnv env("handle_file_exist_creates");
    REQUIRE_FALSE(std::filesystem::exists(env.data_dir));
    REQUIRE_FALSE(std::filesystem::exists(env.file_path));

    handle_file_exist(env.temp_dir);

    REQUIRE(std::filesystem::exists(env.data_dir));
    REQUIRE(std::filesystem::exists(env.file_path));
    std::ifstream file(env.file_path);
    std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    REQUIRE(file_contents.empty());
}

TEST_CASE("handle_file_exist is idempotent if called repeatedly") {
    TestPathEnv env("handle_file_exist_idempotent");

    handle_file_exist(env.temp_dir);
    handle_file_exist(env.temp_dir);

    REQUIRE(std::filesystem::exists(env.data_dir));
    REQUIRE(std::filesystem::exists(env.file_path));
}
