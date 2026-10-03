#ifndef ORDER_H //Header guard
#define ORDER_H //Header guard

#include <string>
#include "OrderItemList.h"
#include "Order.h"
#include "Node.h"
#include "Menu.h"
using namespace std;

//***Constant***
const double TAX_MD = 0.06;

// Name - Order
// Desc - Represents a customer order with items and running totals
// Preconditions - None
// Postconditions - Stores order data and line items
class Order {
public:
  // Name - Order
  // Desc - Default constructor initializes fields
  // Preconditions - None
  // Postconditions - Order ready for use
  Order();
  // Name - GetOrderId
  // Desc - Returns the order number
  // Preconditions - None
  // Postconditions - Returns m_orderId
  int GetOrderId();
  // Name - GetCustomerId
  // Desc - Returns the customer number
  // Preconditions - None
  // Postconditions - Returns m_customerId
  int GetCustomerId();
  // Name - GetSubtotal
  // Desc - Returns subtotal of the order
  // Preconditions - RecomputeTotals has been called for accuracy
  // Postconditions - Returns m_subtotal
  double GetSubtotal();
  // Name - GetTax
  // Desc - Returns computed tax
  // Preconditions - RecomputeTotals has been called for accuracy
  // Postconditions - Returns m_tax
  double GetTax();
  // Name - GetTotal
  // Desc - Returns total (subtotal + tax)
  // Preconditions - RecomputeTotals has been called for accuracy
  // Postconditions - Returns m_total
  double GetTotal();
  // Name - GetItems
  // Desc - Returns the internal list (by value)
  // Preconditions - None
  // Postconditions - Returns copy of m_items
  OrderItemList& GetItems();
  // Name - SetOrderId
  // Desc - Sets order number
  // Preconditions - Valid id provided
  // Postconditions - m_orderId updated
  void SetOrderId(int id);
  // Name - SetCustomerId
  // Desc - Sets customer number
  // Preconditions - Valid id provided
  // Postconditions - m_customerId updated
  void SetCustomerId(int id);
  // Name - AddItem
  // Desc - Adds a prepared OrderItem row
  // Preconditions - Item is valid
  // Postconditions - Item appended to list
  void AddItem(OrderItem row);
  // Name - ClearItems
  // Desc - Removes all line items
  // Preconditions - None
  // Postconditions - List cleared
  void ClearItems();
  // Name - AddItemByMenuId
  // Desc - Looks up price in Menu and appends a line with qty
  // Preconditions - Menu loaded; id exists; qty > 0
  // Postconditions - Line added and true returned; otherwise false
  bool AddItemByMenuId(Menu menu, int id, int qty);
  // Name - At
  // Desc - Returns the OrderItem at zero-based index
  // Preconditions - 0 <= index < Count()
  // Postconditions - Returns a copy (default if out-of-range)
  OrderItem At(int index);
  // Name - RemoveAt
  // Desc - Removes a line item at zero-based index
  // Preconditions - 0 <= index < Count()
  // Postconditions - Returns true if removed
  bool RemoveAt(int index);
  // Name - RecomputeTotals
  // Desc - Refreshes subtotal, tax, and total
  // Preconditions - MD_TAX provided
  // Postconditions - m_subtotal/m_tax/m_total updated
  void RecomputeTotals();
private:
  int m_orderId; // Unique OrderID
  double m_subtotal; // Calcualted subtotal
  double m_tax; // Total calculated tax
  double m_total; // Total calculated value
  OrderItemList m_items; // Linked List of ordered items
};

#endif
