// File: Coffee.h
// Desc: This is one of the child classes for lab 10
// Date: 10/27/2025
// Author: Samuel Truong

#ifndef COFFEE_H
#define COFFEE_H
#include "Drink.h"
#include <iostream>
using namespace std;

class Coffee : public Drink {
public:
  // Constructor
  // Preconditions: None
  // Postconditions: None
  Coffee();

  // Overloaded Constructor
  // Preconditions: None
  // Postconditions: Member variables initialized
  Coffee(string name, string ingredient1, string ingredient2);
  
  // Destructor
  // Hint: Nothing is dynamically allocated in Coffee so empty
  // Preconditions: None
  // Postconditions: None
  ~Coffee();
  
  // DisplayIngredients() - shows Coffee's Ingredients
  // Preconditions: has a name and two Ingredients
  // Postconditions: None
  void DisplayIngredients();
  
  // FlavorProfiles() - describes Coffee flavor profiles
  // Preconditions: None
  // Postconditions: None
  void FlavorProfiles();
private:
  string m_ingredient1; // Coffee's first ingredient
  string m_ingredient2; // Coffee's second ingredient
};

#endif

