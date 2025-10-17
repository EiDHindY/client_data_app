// controller/helper/h_handle_file_exist.h

#pragma once

namespace handle_file_exist
{
#pragma region handle_file_exist Documentation
	/**
	 * @brief Ensures the original data file exists, creating it if necessary.
	 *
	 * Checks for the existence of the original data file. If the file already exists,
	 * the function returns immediately. If the file does not exist, creates the data
	 * directory structure and an empty original file.
	 *
	 * @throws std::system_error
	 *   If retrieving the executable directory path fails (from GetModuleFileNameW).
	 * @throws std::runtime_error
	 *   If the executable path is too long or the original file cannot be created.
	 * @throws std::filesystem::filesystem_error
	 *   If filesystem operations fail (checking file existence, creating directories,
	 *   or accessing paths due to permissions or I/O errors).
	 * @throws std::bad_alloc
	 *   If memory allocation fails while constructing paths.
	 *
	 * @note
	 *   This function is idempotent; calling it multiple times has the same effect
	 *   as calling it once when the file already exists.
	 */
#pragma endregion
	void handle_file_exist();
}