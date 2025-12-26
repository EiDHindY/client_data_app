// client_data_app/include/services/convert/h_convert/h_convert.h
#pragma once
#include <string_view>
#include <vector>


namespace h_convert {
#pragma region Detection
    /**
     * @brief Detects all occurrences of a delimiter within a string view.
     * 
     * @details
     * This function performs a linear scan of the `str` looking for the `delim` sequence.
     * It uses a manual sliding comparison logic:
     * 1. Iterates through valid start positions in `str`.
     * 2. Checks if the substring matches `delim` character-by-character.
     * 3. If a match is found, records the index and jumps the iterator by `delim.length()` to avoid checks inside the found delimiter.
     * 4. If no match, advances by one character.
     * 
     * @param str The string to search through.
     * @param delim The delimiter string to look for.
     * @param indexes [Output] Vector to store the starting positions (indices) of found delimiters.
     */
#pragma endregion Detection
    void detect_delim(std::string_view str, std::string_view delim, std::vector<short>& indexes);
} 