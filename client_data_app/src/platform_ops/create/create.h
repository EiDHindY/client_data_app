// platform_ops/create.h

#pragma once // to avoid multiple definitions

#include <filesystem> // the return value of get_exe_dir_path()


namespace platform_ops_create
{

#pragma region create_data_dir_docs
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
		 *
		 * it takes the data dir name from the infrastrucre layer
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
		 **/
#pragma endregion
	bool create_data_dir(const std::filesystem::path& exe_file_path);

#pragma region  create_original_file_docs
	/**
 * @brief Creates the “original” data file in the data directory.
 *
 * @details
 * Constructs the full path by appending
 * infrastructure_names::DATA_DIR_NAME and
 * infrastructure_names::ORIGINAL_FILE_NAME to exe_file_path.
 * This function **must** be called only after:
 * - platform_ops_create::create_data_dir(exe_file_path)
 *   to ensure the parent directory exists.
 * - file_ops_path::is_original_file_exist(exe_file_path)
 *   to ensure the file does not already exist.
 * Internally, it opens an std::ofstream on the resulting path to create
 * an empty 0-byte file, then immediately closes it.
 *
 * @param exe_file_path
 *   The base directory path (where the executable resides),
 *   passed by const reference to avoid copying.
 *
 * @return bool
 *   Returns true if the file was newly created.
 *
 * @throws std::runtime_error
 *   Thrown if opening the std::ofstream fails (e.g., permission denied,
 *   invalid path, disk full).
 *
 */
#pragma endregion
	bool create_original_file(const std::filesystem::path& exe_file_path);
}//end platform_ops_create

