/*****************************************
 ** File: OrderItemList.cpp
 ** Project: CMSC 202 Project 3, Fall 2025
 ** Author: Jaylen Jenkins
 ** Date: 10/27/2025
 ** Section: 20/22
 ** E-mail: fp31977@gl.umbc.edu
 **
 ** This file contains the implementation for the OrderItemList class.
 ** Linked list that holds Orders.
 ** Orders can be appended to the end, removed, and located.
 ** Additionally, a whole list of orders can be cleared.
 ***********************************************/

#include "OrderItemList.h"

// Menu::OrderItemList::OrderItemList
// Given nothing — Returns nothing
OrderItemList::OrderItemList(){
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Menu::OrderItemList::~OrderItemList
// Given nothing — Returns nothing
OrderItemList::~OrderItemList(){
  Node* curr = m_head; // Creates a temporary node that starts at m_head

  // While curr is not a nullptr, m_head and curr iterate through the list
  // until all nodes are freed
  while(curr != nullptr){
    m_head = curr;
    curr = curr->GetNext();
    delete m_head;
  }

  // Resets the linked list
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Menu::OrderItemList::Pushback
// Given an order item — Returns nothing
void OrderItemList::PushBack(OrderItem item){
  Node* entry = new Node(item); // A new item is entered into the list
  // If there are no items in the linked list, m_head and m_tail are set to the entry
  // and the LL size is incremented by 1
  if(m_head == nullptr){
    m_head = entry;
    m_tail = entry;
    ++m_size;
  }else{
    // m_tail points to the next entry
    // then m_tail is set to the next entry
    // size of the list is incremented by 1
    m_tail->SetNext(entry);
    m_tail = entry;
    ++m_size;
    return;
  }
}

// Menu::OrderItemList::IsEmpty
// Given nothing — Returns true if LL is empty, false if not empty
bool OrderItemList::IsEmpty(){
  if(m_size == 0){
    return true;
  }else{
    return false;
  }
}

// Menu::OrderItemList::Count
// Given nothing — Returns the size of the LL
int OrderItemList::Count(){
  return m_size;
}

// Menu::OrderItemList::ComputeSubtotal
// Given nothing — Returns the (untaxed) subtotal based on an item's [price] * [quantity]
double OrderItemList::ComputeSubtotal(){
  Node* curr = m_head;   // Creates a temporary node to traverse the LL
  double subtotal = 0;   // The subtotal of the order

  // While curr is not a nullptr, curr iterates through the LL
  // An item's price and quantity are obtained
  // Subtotal equals the product of a price and item's quantity
  while(curr != nullptr){
    double price = curr->GetData().GetUnitPrice(); // Price of an item
    int qty = curr->GetData().GetQty();            // Quantity of an item
    
    subtotal += price * qty;
    curr = curr->GetNext();
    
  }
  
  return subtotal;
}

// Menu::OrderItemList::Clear
// Given nothing — Returns nothing
void OrderItemList::Clear(){
  Node* curr = m_head; //Creates a temporary node to traverse the LL

  // While m_head is not a nullptr, m_head and curr iterate through the LL
  // curr is deleted
  while(m_head != nullptr){
    m_head = (*m_head).GetNext();
    delete curr;
    curr = m_head;
  }

  // Reset linked list
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Menu::OrderItemList::At
// Given the desired index of an ordered item — Returns the desired order item
OrderItem OrderItemList::At(int index){
  Node* curr = m_head;  // Creates a temporary node, curr, to traverse the LL
  int counter = 0;      // Counter to compare index to

  // While curr is not a nullptr and until counter equals the index
  // counter will increase, and once they're equal
  // the desired data is returned
  while(curr != nullptr){
    if(counter == index) {
      return curr->GetData();
    }
    ++counter;
    curr = curr->GetNext();
  }
  return OrderItem();
}

// Menu::OrderItemList::RemoveAt
// Given the desired index of an ordered item — Returns true if item removed, else false
bool OrderItemList::RemoveAt(int index){
  Node* curr = m_head; // Creates a temporary node, curr, to traverse the LL
  Node* prev = m_head; // Creates a temporary node, prev, to traverse the LL behind curr

  // Base Case: If list is empty, return false
  if(m_size == 0){
    return false;
  }
  // Base Case: If index is OOB, return false
  else if((index <= 0) || (index > m_size)){
    return false;
  }
  // Remove the only item in the list:
  else if(m_size == 1){
    delete curr;
    m_head = nullptr;
    m_tail = nullptr;
    --m_size;
    return true;
  }
  // Remove the first item in the index
  else if(index == 1){
    m_head = m_head->GetNext();
    delete curr;
    --m_size;
    return true;
  }
  // Else: Cycle through the list until counter is one less than index
  else{
    int counter = 0;
    while(counter != (index - 1)){
      prev = curr;
      curr = curr->GetNext();
      ++counter;
    }

    // Prev's next points to the second node after it
    prev->SetNext(curr->GetNext());

    // If curr equals m_tail, then m_tail is set to the new last node, prev
    if(curr == m_tail){
      m_tail = prev;
    }
    
    delete curr;
    --m_size;
    return true;
  }
} 
