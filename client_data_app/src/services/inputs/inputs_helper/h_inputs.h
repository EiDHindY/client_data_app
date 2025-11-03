#pragma once

#include <sstream>

namespace inputs_helper {

	bool try_read_num(std::istringstream& input, unsigned short& out_value);
	bool is_num_in_range(unsigned short num, unsigned short from, unsigned short to);
}