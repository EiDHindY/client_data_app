#pragma once

#include <sstream>

namespace inputs_helper {

#pragma region try_read_num Documentation
	/**
 * @brief Attempts to read an integer value from a string stream and store it as an unsigned short.
 *
 * This function tries to extract a numeric value from the given `std::istringstream`.
 * It first reads the input into a temporary `int` variable to validate that the value is non-negative
 * and fits within the valid range of `unsigned short`. If the input extraction fails
 * or if the value is negative, the stream is cleared and any remaining invalid input is ignored.
 *
 * @param input Reference to an input string stream (`std::istringstream`) containing numeric text.
 * @param out_value Reference to an unsigned short variable where the successfully read value will be stored.
 *
 * @return `true` if a valid non-negative number was successfully read and assigned to `out_value`,
 *         otherwise `false`.
 *
 * @dependencies
 * - Relies on `<sstream>` for `std::istringstream`.
 * - Uses `<limits>` for `std::numeric_limits<std::streamsize>::max()` when discarding invalid input.
 * - Depends on standard stream state handling (`failbit`, `clear()`, and `ignore()`).
 *
 * @note
 * This function does not check for overflow (values larger than `USHRT_MAX` will wrap when cast)
 * **/
#pragma endregion
	bool try_read_num(std::istringstream& input, unsigned short& out_value);
	bool is_num_in_range(unsigned short num, unsigned short from, unsigned short to);
}