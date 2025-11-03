// services/inputs/inputs.cpp
#include "inputs.h"
#include <print>
#include <sstream>
#include "inputs_helper/h_inputs.h"

namespace inputs
{



	unsigned short read_num_from_to(
		std::istringstream& input,
		unsigned short from,              // Lower bound (inclusive) for valid input
		unsigned short to)                // Upper bound (inclusive) for valid input
		
	{
		unsigned short num{};
		while (true)
		{
			if (!inputs_helper::try_read_num(input, num))
			{
				std::print("Please enter a valid number!\n\n");
				continue;
			}

			if (!inputs_helper::is_num_in_range(num, from, to))
			{
				std::print("Please enter a number between {} and {}\n\n", from, to);
				continue;
			}
			break;
		}

		return num;                       
	}

}