/*****************************************
** File: Menu.cpp
** Project: CMSC 202 Project 3, Fall 2025
** Author: Jaylen Jenkins
** Date: 10/12/2025
** Section: 20/22
** E-mail: fp31977@gl.umbc.edu
**
** This file contains the implementation for the MenuItem class.
** An ID, a name, and a price for a coffee shop menu item.
** Additionally, other programs will be able to retrieve that information from this class for a particular menu item.
***********************************************/

#include "Menu.h"

// Menu::FindById
// Given the id of a desired menu item — Returns a pointer to the desired menu item if it exists; else nullptr
MenuItem* Menu::FindById(int id){
  // Base Case: If the menu is empty, then a nullptr is returned
  if(int(m_items.size()) == 0){
    cout << "The menu is empty." << endl;
    return nullptr;
  }

  // Iterates through the menu and compares the desired item id to all those in the menu
  // If there is a match, then the pointer to the menu item is returned
  for(int i = 0; i < int(m_items.size()); i++){
    if(id == m_items[i].GetId()){
      return &m_items[i];
    }
  }

  return nullptr;
}

// Menu::LoadMenu
// Given a filename — Returns nothing
void Menu::LoadMenu(string filename){
  int id;             // The id of a menu item
  string idString;    // The id of a menu item as a string
  string name;        // The name of a menu item
  double price;       // The price of a menu item
  string priceString; // The price of a menu item as a string
    

  // Opens a file if a valid name is entered
  if(filename == ""){
    return;
  }else{  
    fstream menuFile(filename);

    // Reads into a text file and does the following, while there is a line to read:
    // Starts by accepting an item id, name, and price
    //   (Stops reading at a comma before accepting further input)
    if(menuFile.is_open()){
      while(getline(menuFile, idString, ',')
	    && getline(menuFile, name, ',')
	    && menuFile >> priceString){
	id = stoi(idString);             // Converts the id to an int	
	price = stod(priceString);       // Converts the price to a double

	// Creates a new MenuItem object and enters it into the end of m_items array
	MenuItem item(id, name, price);
	m_items.push_back(item);

	// Ignores unnecessary new lines from the file extraction
	if(menuFile.peek() == '\n'){
	  menuFile.ignore();
	}
      }
    }
  }
}

// Menu::PrintMenu
// Give nothing — Returns nothing
void Menu::PrintMenu(){
  // If the menu is empty, no items are printed
  if(m_items.size() == 0){
    cout << "The menu is empty." << endl;
    return;
  }else{
    // Prints out each item in the array — styled.
    for(int i = 0; i < int(m_items.size()); i++){
      cout << setw(4) <<  m_items[i].GetId() << setw(20) << m_items[i].GetName()
	   << setw(14) << setprecision(2) << fixed << "$" <<  m_items[i].GetPrice() << endl;
    }
  }
}
