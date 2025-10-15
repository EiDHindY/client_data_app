// platform_ops/create.h

#pragma once // to avoid multiple definitions

#include <filesystem> // the return value of get_exe_dir_path()


namespace platform_ops_create
{

#pragma region create_data_dir Documentation
	/**
	 * @brief Creates the data directory under the executable’s directory.
	 *
	 * Appends the configured data directory name to the given executable path
	 * and attempts to create that directory and any missing parent directories.
	 *
	 * @param exe_file_path  The directory path of the running executable.
	 * @return bool
	 *   True if the data directory was created.
	 *   False if it already existed.
	 *
	 * @throws std::filesystem::filesystem_error
	 *   If creation fails due to permissions, invalid path, or other filesystem errors.
	 */
#pragma endregion
	bool create_data_dir(const std::filesystem::path& exe_file_path);

#pragma region create_original_file Documentation
	/**
	 * @brief Creates an empty original data file in the data directory.
	 *
	 * Constructs the full path by appending DATA_DIR_NAME and ORIGINAL_FILE_NAME
	 * to the executable directory path, then opens the file for writing to create it.
	 *
	 * @param exe_file_path  The directory path of the running executable.
	 *
	 * @throws std::runtime_error
	 *   If the file cannot be created or opened. The error message includes the
	 *   attempted file path.
	 *
	 * @note
	 *   Uses the default std::ofstream mode, which truncates existing files
	 *   and creates a new file if none exists.
	 */
#pragma endregion
	void create_original_file(const std::filesystem::path& exe_file_path);
}//end platform_ops_create

