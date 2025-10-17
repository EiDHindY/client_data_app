#pragma once

#include "infrastructure/infrastructure.h"

namespace main_screens
{
#pragma region show_menu_screen Documentation
	/**
	 * @brief Displays the main menu and returns the user's selection.
	 *
	 * Renders the main menu options to standard output, then prompts the user
	 * to choose an option between 1 and 6 inclusive. Input is validated by
	 * `inputs::read_num_from_to`, ensuring a valid choice.
	 *
	 * @return menu_options::enMenuOptions
	 *   - menu_options::enMenuOptions::ShowClientList when the user enters 1
	 *   - menu_options::enMenuOptions::AddNewClient when the user enters 2
	 *   - menu_options::enMenuOptions::DeleteClient when the user enters 3
	 *   - menu_options::enMenuOptions::UpdateClientInfo when the user enters 4
	 *   - menu_options::enMenuOptions::FindClient when the user enters 5
	 *   - menu_options::enMenuOptions::Exit when the user enters 6
	 *
	 * *
	* @note
	*   This function performs console I/O and blocks until valid input is received.
	*/
#pragma endregion
	menu_options::enMenuOptions show_menu_screen();
}