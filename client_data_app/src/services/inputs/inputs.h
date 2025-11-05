// services/inputs/inputs.h

#pragma once
#include <sstream>



namespace inputs
{
	enum class enReadResult
	{
		Invalid_input,
		Out_of_range,
		End_of_file,
		pass
	};

#pragma region read_num_from_to Documentation
	/**
	 * @brief Attempts to read and validate an unsigned short from a string stream within a range.
	 *
	 * Extracts a number from the input stream, validates that extraction succeeded, checks
	 * that the value lies within the specified range, and clears the stream state regardless
	 * of the outcome. Stream error flags and remaining buffer content are always cleared.
	 *
	 * @param input      The input string stream from which to extract the number.
	 * @param from       Lower bound (inclusive) of the acceptable range.
	 * @param to         Upper bound (inclusive) of the acceptable range.
	 * @param out_value  Reference to an unsigned short where the extracted value is stored
	 *                   if validation succeeds.
	 *
	 * @return enReadResult
	 *   - enReadResult::pass if extraction succeeded and the value is within [@p from, @p to].
	 *     @p out_value contains the valid number.
	 *   - enReadResult::Invalid_input if extraction from the stream failed (non-numeric input
	 *     or stream in fail/eof state).
	 *   - enReadResult::Out_of_range if extraction succeeded but the value falls outside the
	 *     range [@p from, @p to].
	 *
	 * @note
	 *   - On Invalid_input or Out_of_range, @p out_value is not modified.
	 *   - The stream's fail/bad bits are cleared and remaining characters up to the next newline
	 *     are discarded in all cases (success or failure).
	 *   - Does not throw exceptions under default stream settings.
	 */
#pragma endregion
	enReadResult read_num_from_to(std::istringstream& input,
		unsigned short from,
		unsigned short to,
		unsigned short& out_value);

}