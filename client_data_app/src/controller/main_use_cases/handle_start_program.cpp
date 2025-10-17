// controller/main_use_cases/handle_start_program.cpp

#include "handle_start_program.h"            // Declaration of start_program() function
#include "controller/helper/h_handle_file_exist.h" // Declaration of handle_file_exist() helper
#include "cli/main_screens/main_screens.h"   // Declaration of show_menu_screen()

namespace start_program
{
    // Entry point for starting the program’s main use case
    menu_options::enMenuOptions start_program()
    {
        // Ensure necessary data directory and original file exist before showing menu
        handle_file_exist::handle_file_exist();
        // Memory: no heap allocations here; local stack frame holds nothing
        // CPU: one function call → pushes return address, jumps to helper

        // Display the main menu and get user’s choice as a scoped enum
        return main_screens::show_menu_screen();
        // Memory: show_menu_screen() builds and prints strings, allocates small buffers for I/O
        // CPU: prints to console, reads input, parses number, casts to enum, then returns
    }
}
