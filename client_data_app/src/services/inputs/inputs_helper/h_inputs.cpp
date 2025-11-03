#include "h_inputs.h"
#include <limits>



namespace inputs_helper {
	bool try_read_num(std::istringstream& input, unsigned short& out_value)
	{
		int temp{};
		bool result = true;
		if (!(input >> temp)) result = false;

		if (temp < 0) result = false;

		if (!result)
		{
			input.clear();
			input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (result) out_value = static_cast<unsigned short>(temp);

		return result;
	}

	bool is_num_in_range(unsigned short num, unsigned short from, unsigned short to)
	{
		return (num >= from && num <= to);
	}
} // end inputs_helper