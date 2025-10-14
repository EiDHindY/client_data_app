// platform_ops/create.cpp
#include "create.h"
#include "infrastructure/infrastructure.h" // for file and dir names
#include <fstream>
#include <stdexcept> // for runtime errors

namespace platform_ops_create
{
	bool create_data_dir(const std::filesystem::path& exe_file_path)
	{
		return std::filesystem::create_directories(exe_file_path / infrastructure_names::DATA_DIR_NAME);
		// exe_file_path is a filesystem::path type
		// data_dir_name is implicityly casted from string to filesystem::path as well
		// the / combine both in a full path
	}

	bool create_original_file(const std::filesystem::path& exe_file_path)
	{
		std::filesystem::path original_file_path = exe_file_path
			/ infrastructure_names::DATA_DIR_NAME
			/ infrastructure_names::ORIGINAL_FILE_NAME;
		// create the full path of the file dynamically from the infrastructre layer

		std::ofstream original_file(original_file_path);
		// open the file just to create without any input

		if (!original_file.is_open())
			throw std::runtime_error("Failed to create the original file" + original_file_path.string());
		// make sure the file is opened and if not throw a runtime error

		original_file.close();
		// close if the file is opened successfully
		return true; // file created successfully
	}


} //end platform_ops_helper