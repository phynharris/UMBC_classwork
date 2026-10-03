#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H
using namespace std;

// Name - OrderItem
// Desc - Represents a line item in an order (menuId, qty, unitPrice, lineTotal)
// Preconditions - None
// Postconditions - Can compute and store line totals
class OrderItem {
public:
  // Name - OrderItem
  // Desc - Default constructor zeros all fields
  // Preconditions - None
  // Postconditions - Item initialized to defaults
  OrderItem();
  // Name - OrderItem
  // Desc - Parameterized constructor; computes line total
  // Preconditions - menuItemId, qty, unitPrice provided
  // Postconditions - Fields set and line total computed
  OrderItem(int menuItemId, int qty, double unitPrice);
  // Name - GetMenuItemId
  // Desc - Returns associated menu item id
  // Preconditions - None
  // Postconditions - Returns m_menuItemId
  int GetMenuItemId();
  // Name - GetQty
  // Desc - Returns quantity
  // Preconditions - None
  // Postconditions - Returns m_qty
  int GetQty();
  // Name - GetUnitPrice
  // Desc - Returns unit price
  // Preconditions - None
  // Postconditions - Returns m_unitPrice
  double GetUnitPrice();
  // Name - GetLineTotal
  // Desc - Returns computed line total
  // Preconditions - RecomputeLineTotal keeps it in sync
  // Postconditions - Returns m_lineTotal
  double GetLineTotal();
  // Name - SetMenuItemId
  // Desc - Sets menu item id
  // Preconditions - Valid id provided
  // Postconditions - m_menuItemId updated
  void SetMenuItemId(int id);
  // Name - SetQty
  // Desc - Sets quantity and recomputes line total
  // Preconditions - qty provided
  // Postconditions - m_qty updated; line total refreshed
  void SetQty(int qty);
  // Name - SetUnitPrice
  // Desc - Sets unit price and recomputes line total
  // Preconditions - price provided
  // Postconditions - m_unitPrice updated; line total refreshed
  void SetUnitPrice(double price);
  // Name - RecomputeLineTotal
  // Desc - Recalculates line total as qty * unit
  // Preconditions - qty and unit set
  // Postconditions - m_lineTotal updated
  void RecomputeLineTotal();
private:
  int m_menuItemId; // id of items ordered
  int m_qty; // Quantity of items ordered
  double m_unitPrice; // unit price of items ordered
  double m_lineTotal; // line total of items ordered (calculated)
};

#endif
