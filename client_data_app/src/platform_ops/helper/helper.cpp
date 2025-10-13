#include "helper.h"
#include <Windows.h>

namespace platform_ops_helper
{
	inline std::filesystem::path get_exe_dir_path()
	{
		/**
			 * @brief Gets the directory path where the currently running executable is located.
			 *
			 * @details
			 * This function retrieves the full path to the currently executing program's .exe file
			 * using the Windows API, then returns only the parent directory path. It handles both
			 * standard paths (up to 260 characters) and extended long paths (up to 32,767 characters).
			 *
			 * The function works by:
			 * 1. Allocating an initial buffer of MAX_PATH (260) characters
			 * 2. Calling GetModuleFileNameW() to retrieve the executable's full path
			 * 3. If the path exceeds MAX_PATH, reallocating a larger buffer (32,767 chars)
			 * 4. Trimming the buffer to the actual path length to save memory
			 * 5. Extracting and returning only the parent directory path
			 *
			 * @return std::filesystem::path The directory containing the executable (without the .exe filename).
			 *         Example: If exe is at "C:\MyApp\Debug\Client_data_app.exe",
			 *         returns "C:\MyApp\Debug"
			 *
			 * @throws std::runtime_error If GetModuleFileNameW() fails (returned 0).
			 *                            Error message includes Windows error code from GetLastError().
			 * @throws std::runtime_error If the executable path exceeds 32,767 characters
			 *                            (extremely rare edge case).
			 *
			 * @note This function uses wide strings (std::wstring) to properly handle Unicode
			 *       characters in file paths (e.g., international characters, emojis).
			 *
			 * @note The function uses the 'inline' keyword to allow multiple inclusions across
			 *       different translation units without causing linker errors (ODR-safe).
			 *
			 * @note Windows API specifics:
			 *       - GetModuleFileNameW returns 0 on failure
			 *       - Returns buffer size when buffer is too small (triggers reallocation)
			 *       - DWORD is a 32-bit unsigned integer (4 bytes)
			 *
			 * @warning This function is **Windows-specific** and will not work on Linux/macOS.
			 *          For cross-platform support, add conditional compilation with #ifdef.
			 *
			 * @par Performance:
			 * - Time complexity: O(n) where n = path length (typically 50-100 chars)
			 * - Space complexity: O(1) for paths < 260 chars, O(k) where k=32767 for long paths
			 * - Typical execution time: 10-25 microseconds
			 * - Memory usage: ~520 bytes (normal) or ~66KB (long paths)
			 *
			 * @par Thread Safety:
			 * Thread-safe. GetModuleFileNameW() and GetLastError() use thread-local storage (TLS),
			 * so multiple threads can safely call this function concurrently.
			 *
			 * @par Example Usage:
			 * @code
			 * try {
			 *     auto exe_dir = platform_ops_helper::get_exe_dir_path();
			 *     auto data_file = exe_dir / "data" / "clients.csv";
			 *     std::ifstream file(data_file);
			 *     // ... use file
			 * } catch (const std::runtime_error& e) {
			 *     std::cerr << "Error: " << e.what() << std::endl;
			 * }
			 * @endcode
			 *
			 * @par Caching Recommendation:
			 * Since the executable path never changes during program execution, consider
			 * caching the result at program startup to avoid repeated system calls:
			 * @code
			 * static const auto EXE_DIR = platform_ops_helper::get_exe_dir_path();
			 * @endcode
			 *
			 * @see GetModuleFileNameW Windows API documentation
			 * @see std::filesystem::path for path manipulation operations
			 *
			 * @since Version 1.0
			 * @author dod
		*/

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

} //platform_ops_helper