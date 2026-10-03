#ifndef MENU_ITEM_H //Header Guard
#define MENU_ITEM_H //Header Guard

#include <string>
using namespace std;

// Name - MenuItem
// Desc - Represents a sellable catalog item (id, name, price)
// Preconditions - None
// Postconditions - Stores and exposes basic fields
class MenuItem {
public:
  // Name - MenuItem
  // Desc - Default constructor; zero/empty fields
  // Preconditions - None
  // Postconditions - Item created with default values
  MenuItem();
  // Name - MenuItem
  // Desc - Overloaded constructor
  // Preconditions - Valid id, name, price provided
  // Postconditions - Item initialized with given values
  MenuItem(int id, string name, double price);
  // Name - GetId
  // Desc - Returns the item id
  // Preconditions - None
  // Postconditions - Returns m_id
  int GetId();
  // Name - GetName
  // Desc - Returns the item name
  // Preconditions - None
  // Postconditions - Returns m_name
  string GetName();
  // Name - GetPrice
  // Desc - Returns the item price
  // Preconditions - None
  // Postconditions - Returns m_price
  double GetPrice();
  // Name - SetName
  // Desc - Sets the item name
  // Preconditions - New name provided
  // Postconditions - m_name updated
  void SetName(string name);
  // Name - SetPrice
  // Desc - Sets the item price
  // Preconditions - New price provided
  // Postconditions - m_price updated
  void SetPrice(double price);
private:
  int m_id; // Unique ID for item
  string m_name; // Name of item
  double m_price; // Price of item
};

#endif //Header Guard
