#include "Drink.h"

// Overloaded Constructor
// Hint: Use this constructor in the child classes to set the name (initialization list)
// Preconditions: None
// Postconditions: Sets m_name
Drink::Drink(string name){
  m_name = name;
}

Drink::~Drink(){

}

void Drink::PrintName(){
}

// GetName() - returns Drinks's name
// Preconditions: name is initialized
// Postconditions: None
string Drink::GetName(){

  return m_name;
}
