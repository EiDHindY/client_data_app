// controller/helper/h_handle_file_exist.h

#pragma once
#include <filesystem>

namespace h_controller
{
#pragma region handle_file_exist Documentation
	/**
	 * @brief Ensures the original data file exists, creating it and its directory if necessary.
	 *
	 * Constructs the full path to the original file by appending the configured data directory
	 * and file name to the provided executable directory. Checks if the file already exists as
	 * a regular file. If it does, returns immediately; otherwise, creates the data directory
	 * structure and an empty original file.
	 *
	 * @param exe_dir_path  The directory path of the running executable, passed by const reference
	 *                      to avoid unnecessary copying.
	 *
	 * @throws std::system_error
	 *   If retrieving the executable directory path fails (from GetModuleFileNameW).
	 * @throws std::runtime_error
	 *   If the executable path is too long or the original file cannot be created.
	 * @throws std::filesystem::filesystem_error
	 *   If filesystem operations fail (checking file existence, creating directories,
	 *   or accessing paths due to permissions or I/O errors).
	 * @throws std::bad_alloc
	 *   If memory allocation fails while constructing paths or opening the file stream.
	 *
	 * @note
	 *   - This function is idempotent; calling it multiple times is safe.
	 *   - File existence check uses stat() system call (kernel transition).
	 *   - Directory creation issues mkdir system calls for each missing component.
	 *   - File creation opens a new file descriptor with internal stream buffer allocation (~8KB typical).
	 *   - All path objects are passed by const reference to minimize heap allocations.
	 */
#pragma endregion	
	void handle_file_exist(const std::filesystem::path&  exe_dir_path);
}