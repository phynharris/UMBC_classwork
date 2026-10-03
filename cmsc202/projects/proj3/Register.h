#ifndef REGISTER_H
#define REGISTER_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Menu.h"
#include "Order.h"
using namespace std;

//***Constants***
const int STARTING_ORDER = 1001;

// Name - Register
// Desc - Simple point-of-sale register that manages menu and current order
// Preconditions - Menu file present when loading
// Postconditions - Allows adding/removing items, viewing order, and checkout
class Register {
 public:
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
 private:
  // Name - StartNewOrder
  // Desc - Clears current item list and then initializes a new order (and id)
  //        Recomputes total based on empty order
  // Preconditions - None
  // Postconditions - New empty order with id set
  void StartNewOrder();
  // Name - ShowRegisterMenu
  // Desc - Displays the register command list (1-5 and 0)
  // Preconditions - None
  // Postconditions - Outputs menu of choices to console
  void ShowRegisterMenu();
  // Name - PrintOrder
  // Desc - Prints the current order as a receipt-style list with totals
  // Preconditions - Order may have zero or more items
  // Postconditions - Outputs order lines and totals to console
  void PrintOrder();
  // Name - AddItemFlow
  // Desc - Prompts for a menu id and quantity, then adds to order
  // Preconditions - Menu must contain loaded items
  // Postconditions - Adds line item when input is valid
  void AddItemFlow();
  // Name - RemoveItemFlow
  // Desc - Shows current order and removes a selected line by index
  // Preconditions - Order has at least one item
  // Postconditions - Removes selected line item when valid index entered
  void RemoveItemFlow();
  // Name - RecomputeTotals
  // Desc - Recalculates totals by calling the order's RecomputeTotal
  // Preconditions - None
  // Postconditions - Order totals updated
  void RecomputeTotals();
  // Name - CheckoutFlow
  // Desc - If order is not empty, prints final receipt, increments m_nextOrderId
  //        calls StartNewOrder
  // Preconditions - Any state of order allowed
  // Postconditions - Current order closed; new order started
  void CheckoutFlow();
 private:
  Menu m_menu; // Manages menu for use in register
  Order m_order; // Current order (only one order at a time)
  int m_nextOrderId; // Used to keep track of next order id
};

#endif
