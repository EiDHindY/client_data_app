// platform_ops/paths.cpp

#include "paths.h"
#include "infrastructure.h" // for DATA_DIR_NAME, ORIGINAL_FILE_NAME
#include <filesystem>
#ifdef _WIN32
#include <Windows.h> // for DWORD
#include <vector>
#endif

namespace platform_ops_paths {
std::filesystem::path
get_exe_dir_path() // Returns the directory of the running .exe
{
#ifdef _WIN32
  std::vector<wchar_t> buffer(128);
  // buffer: dynamic array of wchar_t, initially 128 elements; heap‐allocated
  // contiguous memory

  DWORD exe_path_length{0};
  // exe_path_length: 32-bit unsigned, holds characters written by
  // GetModuleFileNameW

  const DWORD MAX_LIMIT = 32767;
  // MAX_LIMIT: maximum TCHAR count per Windows API (longest valid path)

  while (buffer.size() <= MAX_LIMIT)
  // Loop until buffer can hold the full path or exceeds maximum
  {
    exe_path_length = GetModuleFileNameW(
        // Call Win32 to fill buffer with wide‐char path; CPU switches to kernel
        // mode
        nullptr,       // nullptr: hModule = current process’s .exe
        buffer.data(), // .data(): pointer to buffer’s first wchar_t
        static_cast<DWORD>(
            buffer.size()) // cast size_t → DWORD for API parameter
    );

    if (exe_path_length == 0) // 0 indicates failure; no characters written
    {
      std::error_code ce(        // Wrap OS error code into C++ error_code
          GetLastError(),        // Retrieves last Win32 error from thread‐local
                                 // storage
          std::system_category() // system_category: maps to Win32 errors
      );
      throw std::system_error(
          ce, // Throws exception with message; unwinds stack
          "Failed to get exe path");
    }

    if (exe_path_length < buffer.size())
      // Success and no truncation: written chars < buffer capacity
      break; // Exit loop; valid path retrieved

    // Buffer was too small: prepare to grow
    auto new_size = buffer.size() * 2; // Double current capacity
    if (new_size > MAX_LIMIT) // Cap at MAX_LIMIT to avoid infinite growth
      new_size = MAX_LIMIT;
    if (new_size <=
        buffer.size()) // Sanity check: no growth possible → path too long
      throw std::runtime_error( // Throw runtime error; terminate operation
          "exe path length is too long");

    buffer.resize(new_size);
    // Resize vector: may reallocate and move contents in memory
  }

  // Construct filesystem::path from wide string; .parent_path() returns
  // directory component
  return std::filesystem::path(buffer.data())
      .parent_path(); // Extracts directory, e.g. "C:\\Program Files\\MyApp"
#elif defined(__linux__)
  return std::filesystem::read_symlink("/proc/self/exe").parent_path();
#endif
}

std::filesystem::path
get_original_file_path(const std::filesystem::path &exe_dir_path) {
  // exe_dir_path: const reference to an existing path; no copy of the string
  // data occurs here Function returns a new std::filesystem::path built from
  // exe_dir_path plus two components
  return exe_dir_path /
         infrastructure_names::DATA_DIR_NAME // Append DATA_DIR_NAME (likely a
                                             // constexpr string) as a
                                             // subdirectory
         /
         infrastructure_names::ORIGINAL_FILE_NAME; // Append ORIGINAL_FILE_NAME
                                                   // (likely a constexpr
                                                   // string) as the filename
}

bool is_file_exist(const std::filesystem::path &file_path) {
  // file_path: bound as a const reference, so no deep copy of the path’s
  // internal string occurs here Returns true if the given path names a regular
  // (non‐directory, non‐symlink) file
  return std::filesystem::is_regular_file(file_path);
}

} // namespace platform_ops_paths
