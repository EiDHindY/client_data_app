// services/inputs/inputs.cpp
#include "inputs.h"
#include <sstream>
#include <limits>
#include "h_inputs.h"



namespace inputs
{

	enReadResult read_num_from_to(
		std::istringstream& input,
		unsigned short from,              
		unsigned short to,
		unsigned short& out_value)                
		
	{
		if (!inputs_helper::try_read_num(input, out_value)) {
			input.clear(); // Clear error flags (failbit, badbit, etc.)
			input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to next line.
			return enReadResult::Invalid_input;
		}



		if (!inputs_helper::is_num_in_range(out_value, from, to)) {
			input.clear(); // Clear error flags (failbit, badbit, etc.)
			input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to next line.
			return enReadResult::Out_of_range;
			}

		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return enReadResult::pass;                       
	}

}