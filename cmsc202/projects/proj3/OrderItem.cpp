/*****************************************
 ** File: OrderItem.cpp
 ** Project: CMSC 202 Project 3, Fall 2025
 ** Author: Jaylen Jenkins
 ** Date: 10/27/2025
 ** Section: 20/22
 ** E-mail: fp31977@gl.umbc.edu
 **
 ** This file contains the implementation for the OrderItem class.
 ** Stats are set up for a order item, including an item's id, price, and quantity.
 ** The gathering of order line total and recomputation of total price are performed here.
 ***********************************************/

#include "OrderItem.h"

// Constant
const int DEFAULT_ID = 0;
const int DEFAULT_QTY = 1;
const double DEFAULT_PRICE = 77.77; 

// OrderItem::OrderItem
// Given nothing — Returns nothing
OrderItem::OrderItem(){
  SetMenuItemId(DEFAULT_ID);
  SetQty(DEFAULT_QTY);
  SetUnitPrice(DEFAULT_PRICE);
}

// OrderItem::OrderItem
// Given the id of a menu item, the desired quantity, and its price
// Returns nothing
OrderItem::OrderItem(int menuItemId, int qty, double unitPrice){
  SetMenuItemId(menuItemId);
  SetQty(qty);
  SetUnitPrice(unitPrice);
}

// OrderItem::GetMenuItemid
// Given nothing — Returns the id of a menu item
int OrderItem::GetMenuItemId(){

  return m_menuItemId;
}

// OrderItem::GetQty
// Given nothing — Returns the quantity of an ordered item
int OrderItem::GetQty(){

  return m_qty;
}

// OrderItem::GetUnitPrice
// Given nothing — Returns the price of an ordered item
double OrderItem::GetUnitPrice(){

  return m_unitPrice;
}

// OrderItem::GetLineTotal
// Given nothing — Returns the total num of lines in an order
double OrderItem::GetLineTotal(){
  m_lineTotal = m_qty * m_unitPrice;
  return m_lineTotal;
}

// OrderItem::SetMenuItemId
// Given an id — Returns nothing
void OrderItem::SetMenuItemId(int id){
  // Base Case: id is less than or equal to 0
  if(id <= 0){
    m_menuItemId = DEFAULT_ID;
  }else{
    m_menuItemId = id;
  }
}

// OrderItem::SetQty
// Given the quantity of an ordred item — Returns nothing
void OrderItem::SetQty(int qty){
  // Base Case: qty is less than or equal to 0
  if(qty <= 0){
    m_qty = DEFAULT_QTY;
  }else{
    m_qty = qty;
  }
}

// OrderItem::SetUnitPrice
// Given the price of an individual item — Returns nothing
void OrderItem::SetUnitPrice(double price){
  // Base case: price is less than or equal to 0
  if(price <= 0){
    m_unitPrice = DEFAULT_PRICE;
  }else{
    m_unitPrice = price;
  }
}

// OrderItem::RecomputeLineTotal
// Given nothing — Returns nothing
void OrderItem::RecomputeLineTotal(){
  m_lineTotal = m_unitPrice * m_qty;
}
