\#inlcude "Register.h"

// Name - Register
// Desc - Default constructor initializes order id uses STARTING_ORDER initially
// Preconditions - None
// Postconditions - Register is ready to load a menu and start orders
Register();
// Name - LoadMenu
// Desc - Loads menu items from a CSV file (id,name,price)
// Preconditions - Valid filename; file is accessible
// Postconditions - Menu items loaded into Menu
void LoadMenu(string filename);
// Name - Run
// Desc - Main loop for the register (displays menu and calls functions)
//        1. Prints Menu, 2. Adds Item 3. Removes Item 4. Prints Order
//        5. Manages Checkout 0. Exit
// Preconditions - Menu should be loaded
// Postconditions - Handles user choices until exit
void Run();
