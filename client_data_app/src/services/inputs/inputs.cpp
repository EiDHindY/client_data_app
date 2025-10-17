#include "inputs.h"
#include <print>
#include <iostream>
#include <limits>

namespace inputs
{
	unsigned short read_num_from_to(
		unsigned short from,              // Lower bound (inclusive) for valid input
		unsigned short to,                // Upper bound (inclusive) for valid input
		const std::string& message = "")
		// Optional prompt message (no copy if empty, otherwise binds to caller’s string)

	{
		unsigned short num{};             // Stack variable, zero-initialized; holds the user’s input
		while (true)                      // Loop until a valid number in [from, to] is entered
		{
			if (!message.empty())         // If a prompt was provided...
				std::print("{}", message); // ...print it (formats without heap allocation for plain text)

			std::cin >> num;          // Read numeric input; streams buffer in user space then parse digits
			if (std::cin.fail())          // If extraction failed (non-numeric input)…
			{
				std::print(
					"You didn't enter a valid number, please enter a valid number!\n"); \
					// Notify user of invalid format

					std::cin.clear();        // Reset stream error flags (failbit, badbit)
				std::cin.ignore(         // Discard leftover input up to the next newline
					std::numeric_limits<std::streamsize>::max(), '\n');
				continue;                // Retry input
			}

			if (num < from || num > to)  // If number is outside the allowed range…
			{
				std::print(
					"Please enter a number between {} and {}:\n", from, to);
				// Inform user of valid range
				continue;                // Retry input
			}

			break;                        // Valid number; exit the loop
		}

		return num;                       // Return user’s choice (fits in unsigned short)
	}

}