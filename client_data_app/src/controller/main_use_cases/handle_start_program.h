//controller/main_use_cases/handle_start_program.h

#pragma once

#include "infrastructure/infrastructure.h"

namespace start_program
{
#pragma region start_program Documentation
	/**
	 * @brief Ensures required data files exist, then displays the main menu.
	 *
	 * Invokes the file-existence handler to create the data directory and original file if missing,
	 * and then calls the main menu screen to present options and capture the user's choice.
	 *
	 * @return menu_options::enMenuOptions
	 *   The menu option selected by the user, as returned by `main_screens::show_menu_screen`.
	 *
	 * @throws std::system_error
	 *   If obtaining the executable directory path fails.
	 * @throws std::runtime_error
	 *   If the executable path is unexpectedly long or the original file cannot be created.
	 * @throws std::filesystem::filesystem_error
	 *   If any filesystem operation (directory check/creation, file existence test) fails due to I/O or permission issues.
	 * @throws std::bad_alloc
	 *   If memory allocation fails while constructing paths or during I/O.
	 *
	 * @note
	 *   This function blocks until both the filesystem setup is complete and the user selects a menu option.
	 */
#pragma endregion
	menu_options::enMenuOptions start_program();
}