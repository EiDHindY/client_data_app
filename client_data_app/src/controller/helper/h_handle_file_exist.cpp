// controller/helper/handle_file_exist.cpp

#include "platform_ops/paths/paths.h"
#include "platform_ops/create/create.h"


namespace handle_file_exist
{
	void handle_file_exist()
	{
		// Get the directory path where the executable is located
		std::filesystem::path EXE_DIR_PATH = platform_ops_paths::get_exe_dir_path();
		// Data type: std::filesystem::path - a container for pathname strings; internally stores a platform-native string
		// Memory: Creates a local variable on the stack, but the actual string data is heap-allocated
		// CPU: Calls get_exe_dir_path() which queries the OS for executable location (system call, kernel transition)

		// Build the full path to the original file by combining executable directory + data folder + filename
		std::filesystem::path ORIGINAL_FILE_PATH = platform_ops_paths::get_original_file_path(EXE_DIR_PATH);
		// Data type: std::filesystem::path - another path object holding the complete file path
		// Memory: EXE_DIR_PATH is passed by const reference (no copy), but the returned path is a new object with heap-allocated string
		// CPU: Performs string concatenation using operator/ to build "exe_dir/data/original.csv"

		// Check if the file exists and is a regular file (not a directory or symlink)
		bool is_file_exist = platform_ops_paths::is_file_exist(ORIGINAL_FILE_PATH);
		// Data type: bool - single byte storing true/false
		// Memory: Stack-allocated boolean (1 byte)
		// CPU: Makes a stat() system call (kernel transition) to query file metadata from the filesystem

		if (is_file_exist)
			return; // File already exists, nothing to do; function ends and stack variables are destroyed
		else
		{
			// File doesn't exist, so create the directory structure first
			platform_ops_create::create_data_dir(EXE_DIR_PATH);
			// CPU: Issues mkdir system calls (kernel mode) for each missing directory component
			// Memory: Path passed by const reference to avoid copying

			// Then create the actual empty file
			platform_ops_create::create_original_file(EXE_DIR_PATH);
			// CPU: Issues create/open system call (kernel mode) to create new file descriptor
			// Memory: Opens file stream with internal buffer allocation (~8KB typical)
		}
	}

}// handle_file_exist