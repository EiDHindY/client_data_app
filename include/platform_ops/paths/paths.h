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
	 */
#pragma endregion
	std::filesystem::path get_exe_dir_path();

#pragma region get_original_file_path Documentation
	/**
	 * @brief Constructs the path to the original data file.
	 *
	 * Combines the executable directory path with the configured data directory
	 * and original file name constants.
	 *
	 * @param exe_dir_path  The directory path of the running executable.
	 * @return std::filesystem::path
	 *   The full path: exe_dir_path / DATA_DIR_NAME / ORIGINAL_FILE_NAME.
	 *
	 * @throws std::bad_alloc
	 *   If memory allocation for building the path strings fails.
	 */
#pragma endregion
	std::filesystem::path get_original_file_path(const std::filesystem::path& exe_dir_path);

#pragma region is_file_exist Documentation
	/**
	 * @brief Checks whether the given path corresponds to an existing regular file.
	 * @param file_path The filesystem path to check.
	 * @return bool True if the path exists and is a regular file; false if the path does not exist or is not a regular file.
	 * @throws std::filesystem::filesystem_error If an error occurs while querying the filesystem (e.g., permission denied, path too long, I/O error).
	 */
#pragma endregion
	bool is_file_exist(const std::filesystem::path& file_path);

}// platform_ops_paths

