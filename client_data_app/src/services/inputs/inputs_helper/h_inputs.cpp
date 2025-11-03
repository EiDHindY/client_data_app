#include "services/inputs/inputs_helper/h_inputs.h"
#include <limits>



namespace inputs_helper {
	bool try_read_num(std::istringstream& input, unsigned short& out_value)
	{
		if (input >> out_value) return true;

		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}

	bool is_num_in_range(unsigned short num, unsigned short from, unsigned short to)
	{
		return (num >= from && num <= to);
	}
} // end inputs_helper