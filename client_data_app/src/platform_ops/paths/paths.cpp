//platform_ops/path.cpp

#include "paths.h"
#include <Windows.h>


namespace platform_ops_paths
{
	std::filesystem::path get_exe_dir_path()
	{

		std::wstring exe_path(MAX_PATH, L'\0');
		// string -> char -> 1byte. / wstring ->wchar_t -> 2bytes
		//Create a wide string with MAX_PATH characters (260), all initialized to null character \0.

		DWORD exe_path_length = GetModuleFileNameW(nullptr, exe_path.data(), MAX_PATH);
		// DWORD: A Windows type meaning "Double Word" - a 32-bit unsigned long (4 bytes). Used for sizes and lengths.​
		// Windows API function that retrieves the full path of the executable file.​
		// nullptr: First parameter is module handle. When NULL/nullptr, the function returns the path of the current process's executable. If you passed a DLL handle, it would return that DLL's path.​
		// exe_path.data(): Returns a raw pointer (wchar_t*) to the internal buffer of the std::wstring. This is where GetModuleFileNameW will write the path.​
		// MAX_PATH: Tells the function the buffer size in characters (not bytes).​

		if (exe_path_length == 0)
		{
			DWORD last_error = GetLastError();
			throw std::runtime_error(std::string("failed to get the exe path. error code: ") + std::to_string(last_error));

		}

		if (exe_path_length >= MAX_PATH) // create a bigger buffer
		{
			exe_path = std::wstring(32767, L'\0'); // maximum of the windows path length
			exe_path_length = GetModuleFileNameW(nullptr, exe_path.data(), 32767);
			// call the API again to write on the bigger buffer

			if (exe_path_length == 0)
			{
				DWORD last_error = GetLastError();
				throw std::runtime_error(std::string("Failed to get exe path with extended buffer. error code: ") + std::to_string(last_error));
			}

			if (exe_path_length >= 32767)
			{
				throw std::runtime_error("exe path length is too long");
			}
		}
		exe_path.resize(exe_path_length); // trim to the actual length to save memory
		return std::filesystem::path(exe_path).parent_path(); // return the parent dir of the .exe file
	}

}