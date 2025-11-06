
#include "main_screens.h"      // Brings in the declaration of show_menu_screen and any related UI functions
#include "services/inputs/inputs.h"    // Declares inputs::read_num_from_to for validated user input
#include <print>                       // Provides std::print (C++23) for formatted console output

namespace main_screens
{
	void()
	{
		std::print("=================================================================\n");
		std::print("                        Main Menu Screen                         \n");
		std::print("=================================================================\n");
		std::print("          [1] Show Client List.\n");
		std::print("          [2] Add New Client.\n");
		std::print("          [3] Delete Client.\n");
		std::print("          [4] Update Client Info.\n");
		std::print("          [5] Find Client.\n");
		std::print("          [6] Exit.\n");
		std::print("=================================================================\n\n");
	}
}