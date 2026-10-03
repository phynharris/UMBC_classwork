// File: Superhero.h
// Desc: This is the parent class for lab 10
// Date: 10/27/2025
// Author: Samuel Truong

#ifndef DRINK_H
#define DRINK_H
#include <iostream>
using namespace std;

class Drink {
public:
  // Overloaded Constructor
  // Hint: Use this constructor in the child classes to set the name (initialization list)
  // Preconditions: None
  // Postconditions: Sets m_name
  Drink(string name);
  
  // Destructor (virtual)
  // Preconditions: None
  // Postconditions: Calls child destructor (if it exists)
  virtual ~Drink();
  
  // PrintName() - Prints Drink's name
  // Preconditions: Child class exists (Drink is abstract)
  // Postconditions: Child class name is printed
  virtual void PrintName();
  
  // GetName() - returns Drinks's name
  // Preconditions: name is initialized
  // Postconditions: None
  string GetName();
  
  // DisplayIngredients() - shows drink's ingredients
  // Preconditions: Function MUST be implemented in every child class
  // Postconditions: None
  virtual void DisplayIngredients() = 0; // <- Declares as purely virtual function
  
  // FlavorProfiles() - describes flavor profiles
  // Preconditions: Function MUST be implemented in every child class
  // Postconditions: None
  virtual void FlavorProfiles() = 0; // <- Declares as purely virtual function
  
private:
  string m_name; // Name of the Drink
};

#endif
