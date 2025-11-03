// services/inputs/inputs.h

#pragma once
#include <sstream>

namespace inputs
{
#pragma region

	unsigned short read_num_from_to(std::istringstream& input,
		unsigned short from,
		unsigned short to);

}