// platform_ops/create.cpp
#include "create.h"

namespace platform_ops_create
{
	bool create_data_dir(const std::filesystem::path& exe_file_path, const std::string& data_dir_name)
	{
		return std::filesystem::create_directories(exe_file_path / data_dir_name);
		// exe_file_path is a filesystem::path type
		// data_dir_name is implicityly casted from string to filesystem::path as well
		// the / combine both in a full path
	}

} //end platform_ops_helper