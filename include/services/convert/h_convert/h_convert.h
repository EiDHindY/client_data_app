// client_data_app/include/services/convert/h_convert/h_convert.h
#pragma once
#include "infrastructure.h"
#include <string_view>
#include <vector>

namespace h_convert {
#pragma region Detection
/**
 * @brief Detects all occurrences of a delimiter within a string view.
 *
 * @details
 * This function performs a linear scan of the `str` looking for the `delim`
 * sequence. It uses a manual sliding comparison logic:
 * 1. Iterates through valid start positions in `str`.
 * 2. Checks if the substring matches `delim` character-by-character.
 * 3. If a match is found, records the index and jumps the iterator by
 * `delim.length()` to avoid checks inside the found delimiter.
 * 4. If no match, advances by one character.
 *
 * @param str The string to search through.
 * @param delim The delimiter string to look for.
 * @param indexes [Output] Vector to store the starting positions (indices) of
 * found delimiters.
 */
#pragma endregion Detection
void detect_delim(std::string_view str, std::string_view delim,
                  std::vector<size_t> &indexes);

#pragma region Conversion (String -> Vector)
/**
 * @brief Splits a single string record into a vector of fields.
 *
 * @details
 * This function takes a raw string (e.g., "1001#//#Eid#//#5000") and breaks it
 * into individual components based on the standard application delimiter (e.g.,
 * "#//#").
 *
 * The Algorithm (Anchor Strategy):
 * 1. Finds all delimiter locations first using `detect_delim`.
 * 2. Iterates through these known locations, copying characters between them.
 * 3. Handles the final segment after the last delimiter.
 *
 * @param str_record The raw input line from the file.
 * @return std::vector<std::string> A list of strings, where each element is a
 * field (e.g., {"1001", "Eid", "5000"}). Returns an empty vector if the input
 * string is empty.
 */
#pragma endregion Conversion(String->Vector)
std::vector<std::string> h_conv_str_vstr(std::string_view str_record);

client_data_structure::stClientData
h_conv_vstr_struct(std::vector<std::string> vstr);
} // namespace h_convert