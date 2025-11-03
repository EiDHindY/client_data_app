#include "h_inputs.h"
#include <limits>



namespace inputs_helper {
    bool try_read_num(std::istringstream& input, unsigned short& out_value)
    {
        int temp{};            // Temporary variable to read input as signed int for validation.
        bool result = true;    // Flag indicating success or failure of reading operation.

        // Attempt to extract an integer from the input stream.
        // If extraction fails (bad input), set result to false.
        if (!(input >> temp))
            result = false;

        // Reject negative numbers, as they cannot be represented in unsigned short.
        if (temp < 0)
            result = false;

        // If extraction failed or number invalid, reset stream state and discard bad input.
        if (!result)
        {
            input.clear(); // Clear error flags (failbit, badbit, etc.)
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to next line.
        }

        // If all checks passed, assign value safely to the output variable.
        if (result)
            out_value = static_cast<unsigned short>(temp);

        // Return success status to caller.
        return result;
    }

	bool is_num_in_range(unsigned short num, unsigned short from, unsigned short to)
	{
		return (num >= from && num <= to);
	}
} // end inputs_helper