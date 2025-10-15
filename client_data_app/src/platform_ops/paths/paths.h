// platform_ops/path.h

#pragma once
// to avoid multiple definitions

#include <filesystem>



namespace platform_ops_paths
{
#pragma region get_exe_dir_path Documentation
	/**
	 * @brief Retrieves the directory path containing the running executable.
	 *
	 * Uses the Win32 API GetModuleFileNameW to obtain the full path of the executable,
	 * dynamically resizing the buffer up to a maximum of 32,767 wide characters.
	 *
	 * @return std::filesystem::path
	 *   The parent directory of the executable’s full path.
	 *
	 * @throws std::system_error
	 *   If GetModuleFileNameW returns zero.  The exception’s error_code wraps
	 *   the result of GetLastError().
	 * @throws std::runtime_error
	 *   If the executable path length exceeds the supported maximum or buffer resizing fails.
	 *
	 * @note
	 *   Maximum allowed buffer size is capped at 32,767 characters (Windows limit
	 *   for wide-character paths).
	 */
#pragma endregion
	std::filesystem::path get_exe_dir_path();

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
	std::filesystem::path get_original_file_path(const std::filesystem::path& exe_file_path);

	bool is_file_exist(const std::filesystem::path& file_path);
}// platform_ops_paths

