//platform_ops/path.cpp

#include "paths.h"
#include "infrastructure/infrastructure.h"  // for DATA_DIR_NAME, ORIGINAL_FILE_NAME
#include <Windows.h>
#include <stdexcept> // for runtime errors
#include <vector> 
#include <libloaderapi.h> 
#include <system_error> 
#include <errhandlingapi.h> 
#include <filesystem> 


namespace platform_ops_paths
{
	std::filesystem::path get_exe_dir_path()  // Returns the directory of the running .exe 
	{
		std::vector<wchar_t> buffer(128);
		// buffer: dynamic array of wchar_t, initially 128 elements; heap‐allocated contiguous memory 

		DWORD exe_path_length{ 0 };
		// exe_path_length: 32-bit unsigned, holds characters written by GetModuleFileNameW 

		const DWORD MAX_LIMIT = 32767;
		// MAX_LIMIT: maximum TCHAR count per Windows API (longest valid path) 

		while (buffer.size() <= MAX_LIMIT)
			// Loop until buffer can hold the full path or exceeds maximum 
		{
			exe_path_length = GetModuleFileNameW(
				// Call Win32 to fill buffer with wide‐char path; CPU switches to kernel mode 
				nullptr,                          // nullptr: hModule = current process’s .exe 
				buffer.data(),                   // .data(): pointer to buffer’s first wchar_t 
				static_cast<DWORD>(buffer.size())// cast size_t → DWORD for API parameter
			);

			if (exe_path_length == 0)           // 0 indicates failure; no characters written 
			{
				std::error_code ce(            // Wrap OS error code into C++ error_code 
					GetLastError(),            // Retrieves last Win32 error from thread‐local storage 
					std::system_category()     // system_category: maps to Win32 errors 
				);
				throw std::system_error(ce,    // Throws exception with message; unwinds stack 
					"Failed to get exe path"
				);
			}

			if (exe_path_length < buffer.size())
				// Success and no truncation: written chars < buffer capacity 
				break;                           // Exit loop; valid path retrieved

			// Buffer was too small: prepare to grow
			auto new_size = buffer.size() * 2;   // Double current capacity
			if (new_size > MAX_LIMIT)            // Cap at MAX_LIMIT to avoid infinite growth 
				new_size = MAX_LIMIT;
			if (new_size <= buffer.size())       // Sanity check: no growth possible → path too long
				throw std::runtime_error(        // Throw runtime error; terminate operation 
					"exe path length is too long"
				);

			buffer.resize(new_size);
			// Resize vector: may reallocate and move contents in memory 
		}

		// Construct filesystem::path from wide string; .parent_path() returns directory component
		return std::filesystem::path(buffer.data())
			.parent_path();                    // Extracts directory, e.g. "C:\\Program Files\\MyApp" 
	}


	std::filesystem::path get_original_file_path(const std::filesystem::path& exe_file_path)
	{
		std::filesystem::path original_file_path = std::filesystem::path(
			exe_file_path
			/ infrastructure_names::DATA_DIR_NAME
			/ infrastructure_names::ORIGINAL_FILE_NAME);

		return original_file_path;
	}

	bool is_file_exist(const std::filesystem::path& file_path)
	{
		return std::filesystem::is_regular_file(file_path);
	}
}