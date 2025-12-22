// include/file_ops.h
#pragma once
#include <vector>
#include <string>
#include <filesystem>


namespace file_ops
{
#pragma region get_all_clients Documentation
    /*
        Function: get_all_clients

        Description:
            Reads all lines (clients) from a specified .csv file and stores each line as a string in a vector.
            Each line is assumed to represent a distinct client. Reads until the end of the file.

        Parameters:
            - file_path (const std::filesystem::path&): The path to the .csv file containing client data.

        Returns:
            std::vector<std::string>
                - If the file opens successfully:
                    - Returns a vector where each element is a line from the file (each client as a string).
                - If the file can't be opened (doesn't exist, permission error, etc.):
                    - Returns an empty vector {}.
                - On file I/O errors/exceptions (rare, e.g. disk failure):
                    - Returns empty vector {} (since you don't throw/catch exceptions here).
                - If the file is empty:
                    - Returns an empty vector {}.

        Notes:
            - No error message is printed if opening fails (silent error).
            - No CSV parsing is done; lines are not split into columns.
            - Function does not throw exceptions.

        Side Effects:
            - None. Only reads file; does not modify it. Does not modify any global/static state.

        Big O:
            - Time: O(n) where n = number of lines in the file (each line read once).
            - Space: O(n * m), n = number of lines, m = average length of client strings.
            - File opening and closing as single operations (not counted in O).

        Alternatives / Best Practices:
            - Consider parsing each line via a CSV parser if format is more complex (e.g. commas inside names).
            - Could accept std::istream& for more flexible I/O.
            - Print/log error messages if file fails to open, for easier debugging.
            - Use std::filesystem::exists to check existence before attempting to open for stricter validation.

    */
#pragma endregion
    std::vector<std::string> get_all_clients(const std::filesystem::path& file_path);
}