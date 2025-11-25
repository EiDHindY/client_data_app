#include "services/inputs/h_inputs.h"
#include <climits>



namespace inputs_helper {
    bool try_read_num(std::istringstream& input, unsigned short& out_value)
    {
        int temp{};            // Temporary variable to read input as signed int for validation.
        bool result = true;    // Flag indicating success or failure of reading operation.

        // Attempt to extract an integer from the input stream.
        // If extraction fails (bad input), set result to false.
        if (!(input >> temp))
            result = false;
     

        // If all check passed, assign value safely to the output variable.
        if (result)
            out_value = static_cast<unsigned short>(temp);

        // Return success status to caller.
        return result;
    }

	bool is_num_in_range(unsigned short num, unsigned short from, unsigned short to)
	{
        return (num >= from) && (num <= to) && (num > 0) && (num <= USHRT_MAX);
    }
} // end inputs_helper