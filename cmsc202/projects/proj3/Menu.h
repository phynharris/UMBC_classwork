#ifndef MENU_H //Header Guard
#define MENU_H //Header Guard

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "MenuItem.h"
using namespace std;

//***Constants***
const int WID_ID = 5; // Width for id column
const int WID_NAME = 20; // Width for name column
const int WID_PRICE = 10; // Width for price column

// Name - Menu
// Desc - Stores a simple list of MenuItem entries and supports lookups
// Preconditions - None
// Postconditions - Can load/print menu and find items by id
class Menu {
public:
  // Name - FindById
  // Desc - Returns pointer to MenuItem with matching id or nullptr
  // Preconditions - Menu loaded; id provided
  // Postconditions - Pointer returned or nullptr if not found
  MenuItem* FindById(int id); // nullptr if not found
  // Name - LoadMenu
  // Desc - Loads items from a file (id,name,price)
  // Preconditions - Valid filename provided
  // Postconditions - Items appended to menu
  void LoadMenu(string filename);
  // Name - PrintMenu
  // Desc - Prints all menu items as a table
  // Preconditions - Items may exist
  // Postconditions - Outputs menu
  void PrintMenu();
private:
  vector<MenuItem> m_items; //vector of all items in input file
};

#endif
