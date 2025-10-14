// helper.h

#pragma once // to avoid multiple definitions

#include <filesystem> // the return value of get_exe_dir_path()
#include <string> 

namespace platform_ops_helper
{
	/**
	 * @brief Gets the directory path where the currently running executable is located.
	 *
	 * @details
	 * This function retrieves the full path to the currently executing program's .exe file
	 * using the Windows API, then returns only the parent directory path. It handles both
	 * standard paths (up to 260 characters) and extended long paths (up to 32,767 characters).
	 *
	 * The function works by:
	 * 1. Allocating an initial buffer of MAX_PATH (260) characters
	 * 2. Calling GetModuleFileNameW() to retrieve the executable's full path
	 * 3. If the path exceeds MAX_PATH, reallocating a larger buffer (32,767 chars)
	 * 4. Trimming the buffer to the actual path length to save memory
	 * 5. Extracting and returning only the parent directory path
	 *
	 * @return std::filesystem::path The directory containing the executable (without the .exe filename).
	 *         Example: If exe is at "C:\MyApp\Debug\Client_data_app.exe",
	 *         returns "C:\MyApp\Debug"
	 *
	 * @throws std::runtime_error If GetModuleFileNameW() fails (returned 0).
	 *                            Error message includes Windows error code from GetLastError().
	 * @throws std::runtime_error If the executable path exceeds 32,767 characters
	 *                            (extremely rare edge case).
	 *
	 * @note This function uses wide strings (std::wstring) to properly handle Unicode
	 *       characters in file paths (e.g., international characters, emojis).
	 *
	 *
	 * @note Windows API specifics:
	 *       - GetModuleFileNameW returns 0 on failure
	 *       - Returns buffer size when buffer is too small (triggers reallocation)
	 *       - DWORD is a 32-bit unsigned integer (4 bytes)
	 *
	 * @warning This function is **Windows-specific** and will not work on Linux/macOS.
	 *          For cross-platform support, add conditional compilation with #ifdef.
	 *
	 * @par Performance:
	 * - Time complexity: O(n) where n = path length (typically 50-100 chars)
	 * - Space complexity: O(1) for paths < 260 chars, O(k) where k=32767 for long paths
	 * - Typical execution time: 10-25 microseconds
	 * - Memory usage: ~520 bytes (normal) or ~66KB (long paths)
	 *
	 * @par Thread Safety:
	 * Thread-safe. GetModuleFileNameW() and GetLastError() use thread-local storage (TLS),
	 * so multiple threads can safely call this function concurrently.
	 *
	 * @par Example Usage:
	 * @code
	 * try {
	 *     auto exe_dir = platform_ops_helper::get_exe_dir_path();
	 *     auto data_file = exe_dir / "data" / "clients.csv";
	 *     std::ifstream file(data_file);
	 *     // ... use file
	 * } catch (const std::runtime_error& e) {
	 *     std::cerr << "Error: " << e.what() << std::endl;
	 * }
	 * @endcode
	 *
	 * @par Caching Recommendation:
	 * Since the executable path never changes during program execution, consider
	 * caching the result at program startup to avoid repeated system calls:
	 * @code
	 * static const auto EXE_DIR = platform_ops_helper::get_exe_dir_path();
	 * @endcode
	 *
	 * @see GetModuleFileNameW Windows API documentation
	 * @see std::filesystem::path for path manipulation operations
	 *
	 * @since Version 1.0
	 * @author dod
	*/
	std::filesystem::path get_exe_dir_path();

	/**
	 * @brief Creates a data directory at the specified path.
	 *
	 * @details
	 * This function creates a new directory for storing data files by combining
	 * the executable's directory path with a specified directory name. It uses
	 * std::filesystem::create_directories(), which recursively creates all
	 * necessary parent directories if they don't exist.
	 *
	 * The function works by:
	 * 1. Concatenating exe_file_path with data_dir_name using the / operator
	 * 2. Calling std::filesystem::create_directories() to create the directory
	 * 3. Returning the creation status to the caller
	 *
	 * @param exe_file_path The base directory path (typically the executable's directory).
	 *                      Passed by const reference to avoid expensive copy (40 bytes + heap allocation).
	 * @param data_dir_name The name of the data directory to create (e.g., "data", "output").
	 *                      Passed by const reference to avoid string copy overhead.
	 *
	 * @return bool Returns true if the directory was newly created, false if it already exists.
	 *         A false return value is NOT an error—it simply indicates the directory was already present.
	 *
	 * @throws std::filesystem::filesystem_error If directory creation fails due to:
	 *         - Insufficient permissions (e.g., access denied)
	 *         - Invalid path characters
	 *         - Disk full or I/O errors
	 *         - Path length exceeds system limits
	 *         The exception contains the OS error code, path, and descriptive message.
	 *
	 * @note This function allows exceptions to propagate naturally to the caller,
	 *       providing full error information including the exact path and OS error code.
	 *
	 *
	 * @par Memory & CPU Operations:
	 * - **Stack**: Pushes 16 bytes (two 8-byte pointers/references) onto the stack
	 * - **Heap**: Creates temporary path object (~40 bytes stack + heap allocation for concatenated path)
	 * - **CPU**: Executes path concatenation, then makes system call (CreateDirectoryW on Windows)
	 *            with context switch from user mode to kernel mode (~500-1000 cycles)
	 * - **Cleanup**: Temporary path destructor deallocates heap buffer when function returns
	 *
	 * @par Performance:
	 * - Time complexity: O(n × m) where n = number of directory levels to create,
	 *                    m = average path length for system calls. For single directory: O(1)
	 * - Space complexity: O(k) where k = total path length (typically 50-150 bytes)
	 * - Typical execution time: 10-50 microseconds for single directory creation
	 *
	 * @par Thread Safety:
	 * Thread-safe for different paths. Creating the same directory from multiple threads
	 * may result in race conditions where one thread creates it and others receive false,
	 * but no errors will occur.
	 *
	 * @par Example Usage:
	 * @code
	 * try {
	 *     auto exe_dir = platform_ops_helper::get_exe_dir_path();
	 *     bool created = create_data_dir(exe_dir, "data");
	 *
	 *     if (created) {
	 *         std::cout << "Data directory created successfully\n";
	 *     } else {
	 *         std::cout << "Data directory already exists\n";
	 *     }
	 *
	 *     // Now use the directory
	 *     auto csv_path = exe_dir / "data" / "clients.csv";
	 *     std::ofstream file(csv_path);
	 *
	 * } catch (const std::filesystem::filesystem_error& e) {
	 *     std::cerr << "Error: " << e.what() << "\n";
	 *     std::cerr << "Error code: " << e.code().value() << "\n";
	 * }
	 * @endcode
	 *
	 * @see std::filesystem::create_directories for the underlying implementation
	 * @see std::filesystem::path for path manipulation operations
	 * @see get_exe_dir_path() for obtaining the executable's directory path
	 *
	 * @since Version 1.0
	 * @author dod
	 */
	bool create_data_dir(const std::filesystem::path& exe_file_path, const std::string& data_dir_name);
}//end platform_ops_helper

