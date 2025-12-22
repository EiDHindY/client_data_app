// platform_ops/create.cpp
#include "create.h"
#include "infrastructure.h" // for DATA_DIR_NAME, ORIGINAL_FILE_NAME
#include <fstream>
#include <stdexcept> // for runtime errors

namespace platform_ops_create {
bool create_data_dir(const std::filesystem::path &exe_file_path) {
  // exe_file_path: const reference to the full path of the executable file; no
  // copy incurred create_directories: creates all non-existing directories in
  // the given path and returns true if any were created
  return std::filesystem::create_directories(
      exe_file_path /
      infrastructure_names::DATA_DIR_NAME // Append data directory name to EXE
                                          // path
  );
}

void create_original_file(const std::filesystem::path &exe_file_path) {
  // exe_file_path: const reference to the directory containing the executable;
  // no deep copy of the path string occurs here
  std::filesystem::path original_file_path =
      exe_file_path /
      infrastructure_names::DATA_DIR_NAME
      // operator/ builds a new path by concatenating exe_file_path and the
      // DATA_DIR_NAME constant
      / infrastructure_names::ORIGINAL_FILE_NAME;
  // then appends ORIGINAL_FILE_NAME, producing the full file path

  // original_file_path now holds something like "C:\\MyApp\\data\\original.csv"

  std::ofstream original_file(original_file_path);
  // Constructs an ofstream and attempts to open (or create) the file at
  // original_file_path Internally, this calls the OS create/open system call,
  // transitioning CPU from user to kernel mode

  if (!original_file.is_open())
    // is_open() checks if the stream has an associated file descriptor; returns
    // false on failure
    throw std::runtime_error("Failed to create the original file: " +
                             original_file_path.string());
  // Throws an exception if the file could not be created or opened

  original_file.close();
  // Closes the file: flushes buffers, releases file descriptor back to OS, and
  // returns CPU control to user mode
}
