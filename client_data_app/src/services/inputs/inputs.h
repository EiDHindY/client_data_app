#pragma once
#include <string>

namespace inputs
{
#pragma region read_num_from_to Documentation
	/**
	 * @brief Prompts the user to enter an unsigned short within a specified range.
	 *
	 * Repeatedly prints an optional message, reads input into an unsigned short,
	 * and validates both correct numeric entry and that the value lies between
	 * @p from and @p to (inclusive). Invalid input (non-numeric or out of range)
	 * is cleared and retried until a valid number is received.
	 *
	 * @param from     Lower bound (inclusive) of the acceptable range.
	 * @param to       Upper bound (inclusive) of the acceptable range.
	 * @param message  Optional prompt displayed before each input attempt.
	 *                 If empty, no prompt is printed.
	 *
	 * @return unsigned short
	 *   A valid number in the range [@p from, @p to].
	 *
	 * @pre @p from <= @p to; otherwise the loop will never terminate.
	 *
	 * @note
	 *   - If extraction from std::cin fails (e.g. non-numeric input), the stream’s
	 *     error state is cleared and remaining input up to the next newline is discarded.
	 *   - Does not throw exceptions under normal operation.
	 */
#pragma endregion
	unsigned short read_num_from_to(
		unsigned short from,
		unsigned short to,
		const std::string& message = "");
}