#pragma once

#include <sstream>

namespace inputs_helper {

#pragma region try_read_num Documentation
	/**
	 * @brief Attempts to extract an unsigned short integer from an input string stream.
	 *
	 * Reads an integer from the provided string stream into a temporary signed int,
	 * validates successful extraction, then casts and stores the result in the output parameter.
	 * Uses an intermediate int to allow proper stream extraction behavior before narrowing to
	 * unsigned short.
	 *
	 * @param input       The input string stream from which to extract the number.
	 * @param out_value   Reference to an unsigned short where the extracted value will be stored
	 *                    if extraction succeeds.
	 *
	 * @return bool
	 *   - true if extraction succeeded and @p out_value contains the extracted number.
	 *   - false if extraction failed (e.g., non-numeric input, stream already in fail/eof state,
	 *     or stream exhausted).
	 *
	 * @note
	 *   - On failure, @p out_value remains unchanged.
	 *   - The function does not validate that the extracted integer fits within the unsigned short
	 *     range [0, 65535]; values outside this range will be truncated during static_cast.
	 *   - The stream's state is modified by the extraction attempt. If extraction fails, the
	 *     stream's fail bit remains set and the invalid input stays in the stream buffer.
	 *   - Does not throw exceptions under default stream settings (exceptions disabled).
	 */
#pragma endregion
	bool try_read_num(std::istringstream& input, unsigned short& out_value);

#pragma region is_num_in_range Documentation
	/**
	 * @brief Checks whether a number lies within a specified inclusive range.
	 *
	 * Validates that the given number is at least @p from, at most @p to,
	 * greater than zero, and within the unsigned short type's maximum value.
	 *
	 * @param num   The number to validate.
	 * @param from  Lower bound (inclusive) of the acceptable range.
	 * @param to    Upper bound (inclusive) of the acceptable range.
	 *
	 * @return bool
	 *   - true if all*/
#pragma endregion
	bool is_num_in_range(unsigned short num, unsigned short from, unsigned short to);
}