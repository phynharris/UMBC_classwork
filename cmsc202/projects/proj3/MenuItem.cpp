/*****************************************
 ** File: MenuItem.cpp
 ** Project: CMSC 202 Project 3, Fall 2025
 ** Author: Jaylen Jenkins
 ** Date: 10/12/2025
 ** Section: 20/22
 ** E-mail: fp31977@gl.umbc.edu
 **
 ** This file contains the implementation for the MenuItem class.
 ** This file initializes an ID, a name, and a price for a coffee shop menu item.
 ** Additionally, other programs will be able to retrieve that information from this class for a particular menu item.
 ***********************************************/

#include "MenuItem.h"

// Constants
const int DEFAULT_ID = 0;
const string DEFAULT_NAME = "itemName";
const double DEFAULT_PRICE = 77.77;

// MenuItem::MenuItem
// Given nothing — Returns nothing
MenuItem::MenuItem(){
  // Sets id, name, and price to default values
  m_id = DEFAULT_ID;
  SetName(DEFAULT_NAME);
  SetPrice(DEFAULT_PRICE);
}

// MenuItem::MenuItem
// Given the id, name, and price of a menu item — Returns nothing
MenuItem::MenuItem(int id, string name, double price){
  if(id <= 0){
    m_id = DEFAULT_ID; 
  }else{
    m_id = id;
  }

  // Sets item name and price
  SetName(name);
  SetPrice(price);
}

// MenuItem::GetId
// Given nothing — Returns the id of a menu item
int MenuItem::GetId(){

  return m_id;
}

// MenuItem::GetName
// Given nothing — Returns the name of a menu item
string MenuItem::GetName(){

  return m_name;
}

// MenuItem::GetPrice
// Given nothing — Returns the price of a menu item
double MenuItem::GetPrice(){

  return m_price;
}

// MenuItem::SetName
// Given the name of a menu item — Returns nothing
void MenuItem::SetName(string name){
  // Base Case: Name is an empty string
  if(name == ""){
    m_name = DEFAULT_NAME;
  }else{
    m_name = name;
  }
}

// MenuItem::SetPrice
// Given the price of a menu item — Returns nothing
void MenuItem::SetPrice(double price){
  // Base Case: Price is less than or equal to 0
  if(price <= 0){
    m_price = DEFAULT_PRICE;
  }else{
    m_price = price;
  }
}
