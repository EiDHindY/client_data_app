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

#pragma region create_original_file_docs
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

