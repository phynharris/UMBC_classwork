/*****************************************
 ** File: Order.cpp
 ** Project: CMSC 202 Project 3, Fall 2025
 ** Author: Jaylen Jenkins
 ** Date: 10/27/2025
 ** Section: 20/22
 ** E-mail: fp31977@gl.umbc.edu
 **
 ** This file contains the implementation for the Order class.
 ** Calls functions to set up OrderItems and functions dealing with OrderItemList.
 ** Additionally, calculates the order total, including tax.
 ***********************************************/

#include "Order.h"

// Constants
const int DEFAULT_ORDER_ID = 0;

// OrderItem::Order
// Given nothing — Returns nothing
Order::Order(){
  SetOrderId(DEFAULT_ORDER_ID);
  SetCustomerId(1);
}

// OrderItem::GetOrderId
// Given nothing — Returns the id of an order
int Order::GetOrderId(){

  return m_orderId;
}

// OrderItem::GetCustomerId
// Given nothing — Returns the id of a customer
int Order::GetCustomerId(){
  return 1;
}

// OrderItem::GetSubtotal
// Given nothing — Returns the subtotal of an order
double Order::GetSubtotal(){
  m_subtotal = m_items.ComputeSubtotal();
  return m_subtotal;
}

// OrderItem::GetTax
// Given nothing — Returns the tax of an order
double Order::GetTax(){
  m_tax = TAX_MD * m_subtotal;
  return m_tax;
}

// OrderItem::GetTotal
// Given nothing — Returns the total cost of an order
double Order::GetTotal(){
  m_total = m_tax + m_subtotal;
  return m_total;
}

// OrderItem::GetItems
// Given nothing — Returns a copy of a linked list of ordered items
OrderItemList& Order::GetItems(){

  return m_items;
}

// OrderItem::SetOrderId
// Given an order id — Returns nothing
void Order::SetOrderId(int id){
  // Base Case: id is less than or equal to 0
  if(id <= 0){
    m_orderId = DEFAULT_ORDER_ID;
  }else{
    m_orderId = id;
  }
}

// OrderItem::SetCustomerId
// Given a customer id — Returns nothing
void Order::SetCustomerId(int id){
  if(id <= 0){
    m_orderId = 0;
  }else{
    m_orderId = id;
  }
}

// OrderItem::AddItem
// Given an order item — Returns nothing
void Order::AddItem(OrderItem row){
  m_items.PushBack(row);
}

// OrderItem::ClearItems
// Given nothing — Returns nothing
void Order::ClearItems(){
  m_items.Clear();
}

// OrderItem::AddItemByMenuId
// Given the menu, a menu id and a quantity
// Returns true if item added, else false
bool Order::AddItemByMenuId(Menu menu, int id, int qty){
  MenuItem* menuItem = menu.FindById(id); // Obtains the pointer to a menu item
  
  if(menuItem != nullptr){
    double price = menuItem->GetPrice(); // Price of a menu item
    OrderItem* item = new OrderItem(id, qty, price); // Creates a new OrderItem with an id, quantity, and price

    // Adds OrderItem to OrderItemList
    AddItem(*item);
    
    return true;
  }else{
    return false;
  }
}

// OrderItem::At
// Given the index of an ordered item — Returns the desired order item
OrderItem Order::At(int index){
  // If the given index is out of bounds, then a base index is returned.
  if((index < 0) || (index >= GetItems().Count())){
    return m_items.At(0);
  }else{
    return m_items.At(index);
  }
}

// OrderItem::RemoveAt
// Given a desired index — Returns true if item removed, else false
bool Order::RemoveAt(int index){
  // If the index is out of bounds, no item will be removed
  if((index < 0) || (index > GetItems().Count())){
    return false;
  }else{
    // Calls for the desired item to be removed
    return m_items.RemoveAt(index);
  }
}

// OrderItem::RecomputeTotals
// Given nothing — Returns nothing
void Order::RecomputeTotals(){
  // Gets the subtotal, then tax and adds them up
  m_subtotal = m_items.ComputeSubtotal();
  m_tax = TAX_MD * m_subtotal;
  m_total = m_tax + m_subtotal;
}
