#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "OrderItem.h"
using namespace std;

// Name - Node
// Desc - Singly-linked list node storing an OrderItem
// Preconditions - None
// Postconditions - Supports next pointer and data accessors
class Node {
public:
  // Name - Node
  // Desc - Constructs a node with data and null next
  // Preconditions - OrderItem provided
  // Postconditions - Node created with m_next = nullptr
  Node(const OrderItem& d) : m_data(d), m_next(nullptr) {}
  // Name - GetNext
  // Desc - Returns next pointer
  // Preconditions - None
  // Postconditions - Returns m_next
  Node* GetNext(){return m_next;}
  // Name - SetNext
  // Desc - Sets the next pointer
  // Preconditions - Pointer provided
  // Postconditions - m_next updated
  void SetNext(Node* next){m_next = next;}
  // Name - GetData
  // Desc - Returns a copy of the stored OrderItem
  // Preconditions - None
  // Postconditions - Returns m_data
  OrderItem GetData(){return m_data;}
  // Name - SetData
  // Desc - Replaces the stored OrderItem
  // Preconditions - Valid OrderItem provided
  // Postconditions - m_data updated
  void SetData(OrderItem o){m_data = o;}
private:
  OrderItem m_data; // Holds order data in node
  Node* m_next; // Pointer to next node in linked list
};

#endif
