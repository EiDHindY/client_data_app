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

#pragma region read_account_number Documentation
	/*
		Function: read_string

		Description:
			Reads a line of text from standard input (std::cin) safely.
			Handles possible input errors (like stream failing or user interrupt), clears
			error flags, and flushes invalid input before retrying.
			Returns the string entered by the user, or an empty string if input was invalid.

		Parameters:
			None

		Returns:
			std::string
				- On success: returns the user's input as a string
				- On error (input stream bad/fail, user enters an invalid line, Ctrl+D/Z): returns an empty string ("")
				- On exception (rare, e.g. hardware/OS failure): function will not catch unrecoverable exceptions

		Notes:
			- The function clears any errors detected on std::cin, both before and after trying to get input.
			- Displays an error message if input failed.
			- This function does not throw exceptions.
			- Good for data entry scenarios where you want to avoid infinite loops on bad input.

		Side Effects:
			- If input was invalid, will clear stream errors and ignore any leftover characters from std::cin, preventing accidental input loops.
			- Prints an error message to std::cout if std::getline fails.

		Big O:
			- Time: O(n), where n is the number of characters ignored/skipped on error or up to the newline character.
			- Space: O(m), where m is the size of the input string (proportional to the length of a line entered).

		Alternatives:
			- For more robust input (validation, custom prompts), consider adding parameter(s) or using a template or functor.
			- For non-interactive code (reading from files), modify the function to take an std::istream& parameter.

	*/
#pragma endregion
	std::string read_account_number();

}