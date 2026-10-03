/*****************************************
 ** File: Register.cpp
 ** Project: CMSC 202 Project 3, Fall 2025
 ** Author: Jaylen Jenkins
 ** Date: 10/27/2025
 ** Section: 20/22
 ** E-mail: fp31977@gl.umbc.edu
 **
 ** This file contains the implementation for the Register class.
 ** After loading a menu, allows the user to display said menu, order an item,
 ** remove an ordered item, display their order, anc checkout.
 ** Calls functions to set up OrderItems and functions dealing with OrderItemList.
 ** Additionally, calculates the order total, including tax.
 ***********************************************/

#include "Register.h"

// Register::Register
// Given nothing — Returns nothing
Register::Register(){
  m_nextOrderId = STARTING_ORDER;
  m_order.SetOrderId(m_nextOrderId);
}

// Register::LoadMenu
// Given a filename — Returns nothing
void Register::LoadMenu(string filename){
  // Will not load a file if entry is blank
  if(filename == ""){
    cout << "Invalid filename." << endl;
  }else{
    m_menu.LoadMenu(filename);
  }
}

// Register::Run
// Given nothing — Returns nothing
void Register::Run(){
  int choice = 0; // What the user does with the register menu

  // While choice is not equal to 0 (quit), run
  do{
    // Displays the register menu
    ShowRegisterMenu();

    // Player inputs their choice
    cin >> choice;

    // The six options that the player can choose from
    switch(choice){
    case 0:
      cout << "Auf Wiedersehen" << endl;
      break;
    case 1:
      m_menu.PrintMenu();
      break;
    case 2:
      AddItemFlow();
      break;
    case 3:
      RemoveItemFlow();
      break;
    case 4:
      PrintOrder();
      break;
    case 5:
      CheckoutFlow();
      break;
    default:
      cout << "Invalid Option Selected." << endl;
      break;
    }
  }while(choice != 0);
  // Clears the LL before terminating
  m_order.ClearItems();
}

// Register::StartNewOrder
// Given nothing — Returns nothing
void Register::StartNewOrder(){
  // Clears the LL for a new order
  m_order.ClearItems();

  // Sets new Id for new order
  m_order.SetOrderId(m_nextOrderId);
  cout << "New order started" << endl;
}

// Register::ShowRegisterMenu
// Given nothing — Returns nothing
void Register::ShowRegisterMenu() {
  cout << "\n== REGISTER ==\n"
       << "1) Show menu\n"
       << "2) Add item\n"
       << "3) Remove item\n"
       << "4) View current order\n"
       << "5) Checkout\n"
       << "0) Exit\n"
       << "Choice: ";
}

// Register::PrintOrder
// Given nothing — Returns nothing
void Register::PrintOrder() {
  cout << "\n== CURRENT ORDER #" << m_order.GetOrderId() << " ==\n";
  if (m_order.GetItems().IsEmpty()) {
    cout << "(no items)\n";
    return;
  }

  cout << left << setw(4) << "#"
       << left << setw(20) << "Item"
       << right << setw(6) << "Qty"
       << right << setw(10) << "Unit"
       << right << setw(12) << "Line Total" << "\n";
  cout << string(52, '-') << "\n";

  for (int i = 0; i < m_order.GetItems().Count(); i++) {
    OrderItem it = m_order.At(i);
    MenuItem* mi = m_menu.FindById(it.GetMenuItemId());
    string name = mi ? mi->GetName() : string("(unknown)");

    cout << left << setw(4) << (i + 1)
	 << left << setw(20) << name
	 << right << setw(6) << it.GetQty()
	 << right << setw(10) << fixed << setprecision(2)
	 << it.GetUnitPrice()
	 << right << setw(12) << fixed << setprecision(2)
	 << it.GetLineTotal()
	 << "\n";
  }

  cout << string(52, '-') << "\n";
  cout << right << setw(30) << "Subtotal:"
       << right << setw(22) << fixed << setprecision(2)
       << m_order.GetSubtotal() << "\n";
  cout << right << setw(30) << "Tax:"
       << right << setw(22) << fixed << setprecision(2)
       << m_order.GetTax() << "\n";
  cout << right << setw(30) << "Total:"
       << right << setw(22) << fixed << setprecision(2)
       << m_order.GetTotal() << "\n";
}

// Register::AddItemFlow
// Given nothing — Returns nothing
void Register::AddItemFlow(){
  int id;                 // The id for a menu item
  int qty;                // The quantity of a menu item
  bool itemAdded = false; // If an item was added or not

  // Prints the menu and prompts the user to select an item and quantity
  m_menu.PrintMenu();
  cout << "Please enter a menu id: ";
  cin >> id;

  cout << "How much of that item would you like? ";
  cin >> qty;
  cout << endl;

  // Checks if an item was added to the LL
  itemAdded = m_order.AddItemByMenuId(m_menu, id, qty); 
  if(itemAdded == true){
    cout << "Item added" << endl;
  }else{
    cout << "Item not added" << endl;
  }  
}

// Register::RemoveItemFlow
// Given nothing — Returns nothing
void Register::RemoveItemFlow(){
  int index; // The index for an item the user wants to remove

  // If the LL is not empty, allows the user to remove an item
  if(m_order.GetItems().IsEmpty() == false){
    PrintOrder();
    cout << "Enter an item to remove: ";
    cin >> index;

    // Checks if the item was removed
    if(m_order.RemoveAt(index)){
      cout << "Removed item" << endl;
    }else{
      cout << "Item not removed" << endl;
    }
  }else{
    cout << "Order is empty" << endl;
  }
}

// Register::RecomputeTotals
// Given nothing — Returns nothing
void Register::RecomputeTotals(){
  // Recomputes the order total
  m_order.RecomputeTotals();
}

// Register::CheckoutFlow
// Given nothing — Returns nothing
void Register::CheckoutFlow(){
  // If the order is populated:
  // total is obtained, order is printed, and a new order is started
  if(m_order.GetItems().IsEmpty() == false){
    m_order.RecomputeTotals();
    PrintOrder();
    ++m_nextOrderId;
    StartNewOrder();
  }
}
