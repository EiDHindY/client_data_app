// platform_ops/path.h

#pragma once
// to avoid multiple definitions

#include <filesystem>



namespace platform_ops_paths
{
#pragma region get_exe_dir_path Docs
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
#pragma endregion
	auto get_exe_dir_path();

#pragma region get_original_file_path_docs
	/**
		 * @brief Constructs the full path to the original data file.
		 *
		 * @details
		 * Combines the executable’s directory (exe_file_path) with the
		 * infrastructure_names::DATA_DIR_NAME and
		 * infrastructure_names::ORIGINAL_FILE_NAME constants. No filesystem I/O
		 * is performed; this function only composes and returns the path string.
		 *
		 * @param exe_file_path
		 *   The directory where the executable resides, passed by const reference.
		 *
		 * @return std::filesystem::path
		 *   The full path: exe_file_path / DATA_DIR_NAME / ORIGINAL_FILE_NAME.
		 *
		 * @note
		 *   Call platform_ops_helper::create_data_dir(exe_file_path, DATA_DIR_NAME)
		 *   first to ensure the parent directory exists, and use
		 *   file_ops_helper::create_file_if_not_exists() to guarantee the file
		 *   does not already exist before creating it.
		 *
		 * @par Complexity
		 *   - Time:  O(1) — single path concatenation
		 *   - Space: O(k) — storage for the combined path string, where k is its length
		 *
		 * @par Thread Safety
		 *   This function is thread-safe; it has no side effects or shared state.
		 */
#pragma endregion
	auto get_original_file_path(const std::filesystem::path& exe_file_path);


}// platform_ops_paths

