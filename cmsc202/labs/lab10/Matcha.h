// File: Matcha.h
// Desc: This is one of the child classes for lab 10
// Date: 10/27/2025
// Author: Samuel Truong

#ifndef MATCHA_H
#define MATCHA_H
#include "Drink.h"
#include <iostream>
using namespace std;

class Matcha : public Drink {
public:
  // Constructor
  // Preconditions: None
  // Postconditions: None
  Matcha();

  // Overloaded Constructor
  // Preconditions: None
  // Postconditions: Member variables initialized
  Matcha(string name, string ingredient1, string ingredient2);
  
  // Destructor
  // Hint: Nothing is dynamically allocated in Matcha so empty
  // Preconditions: None
  // Postconditions: None
  ~Matcha();

  // DisplayIngredients() - shows Matcha's ingredients
  // Preconditions: has a name and two ingredients
  // Postconditions: None
  virtual void DisplayIngredients();
  
  // FlavorProfiles() - describes Matcha's flavor profiles
  // Preconditions: None
  // Postconditions: None
  virtual void FlavorProfiles();
  
private:
  string m_ingredient1; // Matcha's first power
  string m_ingredient2; // Matcha's second power
};

#endif
