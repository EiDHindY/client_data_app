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

#pragma region

	enReadResult read_num_from_to(std::istringstream& input,
		unsigned short from,
		unsigned short to,
		unsigned short& out_value);

}