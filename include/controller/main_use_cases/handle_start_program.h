//controller/main_use_cases/handle_start_program.h

#pragma once

#include "infrastructure.h"

namespace start_program_controller
{
#pragma region start_program Documentation
	/**
	 * @brief Initializes the program, ensures data files exist, and displays the main menu with user input validation.
	 *
	 * Retrieves the executable directory path, ensures the data directory and original file exist,
	 * displays the main menu, then repeatedly prompts the user to enter a valid menu option (1-6).
	 * Validates input by type (numeric) and range, displaying appropriate error messages for invalid
	 * or out-of-range entries. Continues looping until a valid choice is received.
	 *
	 * @return menu_options::enMenuOptions
	 *   - menu_options::enMenuOptions::ShowClientList for input 1
	 *   - menu_options::enMenuOptions::AddNewClient for input 2
	 *   - menu_options::enMenuOptions::DeleteClient for input 3
	 *   - menu_options::enMenuOptions::UpdateClientInfo for input 4
	 *   - menu_options::enMenuOptions::FindClient for input 5
	 *   - menu_options::enMenuOptions::Exit for input 6
	 *
	 * @throws std::system_error
	 *   If retrieving the executable directory path fails.
	 * @throws std::runtime_error
	 *   If the original data file cannot be created.
	 * @throws std::filesystem::filesystem_error
	 *   If filesystem operations fail (creating directories, checking file existence).
	 * @throws std::bad_alloc
	 *   If memory allocation fails during path construction or stream operations.
	 *
	 * @note
	 *   - This function blocks until the user enters a valid choice.
	 *   - Uses std::getline for robust input handling, then parses with std::istringstream.
	 *   - Each invalid attempt clears the stream state to prevent cascading errors.
	 */
#pragma endregion
	menu_options::enMenuOptions start_program();
}