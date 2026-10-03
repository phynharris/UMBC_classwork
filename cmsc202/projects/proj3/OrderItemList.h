#ifndef ORDER_ITEM_LIST_H
#define ORDER_ITEM_LIST_H

#include "OrderItem.h"
#include "Node.h"
using namespace std;

// Name - OrderItemList
// Desc - Singly-linked list wrapper that stores OrderItem rows
// Preconditions - None
// Postconditions - Manages dynamic nodes for order line items
class OrderItemList {
public:
  // Name - OrderItemList
  // Desc - Default constructor; initializes empty list
  // Preconditions - None
  // Postconditions - Empty list is created
  OrderItemList();
  // Name - ~OrderItemList
  // Desc - Destructor; clears all nodes
  // Preconditions - List may contain nodes
  // Postconditions - Frees all nodes; list becomes empty
  ~OrderItemList();
  // Name - PushBack
  // Desc - Appends an OrderItem to the end of the list
  // Preconditions - Valid OrderItem provided
  // Postconditions - Size increases by one
  void PushBack(OrderItem item);
  // Name - IsEmpty
  // Desc - Indicates if the list has no nodes
  // Preconditions - None
  // Postconditions - Returns true if size is zero
  bool IsEmpty();
  // Name - Count
  // Desc - Returns number of items in the list
  // Preconditions - None
  // Postconditions - Returns m_size
  int Count();
  // Name - ComputeSubtotal
  // Desc - Sums all line totals in the list
  // Preconditions - Items may exist with valid line totals
  // Postconditions - Returns sum as double
  double ComputeSubtotal();
  // Name - Clear
  // Desc - Deletes all nodes and resets size
  // Preconditions - None
  // Postconditions - List becomes empty
  void Clear();
  // Name - At
  // Desc - Returns the OrderItem at zero-based index
  // Preconditions - 0 <= index < Count()
  // Postconditions - Returns a copy of the item; undefined if out of range
  OrderItem At(int index);
  // Name - RemoveAt
  // Desc - Removes node at zero-based index
  // Preconditions - 0 <= index < Count()
  // Postconditions - Returns true if removed; size decreases by one
  bool RemoveAt(int index);
private:
  Node* m_head; // First node in linked list
  Node* m_tail; // Last node in linked list
  int m_size; // Number of nodes in linked list
};

#endif
