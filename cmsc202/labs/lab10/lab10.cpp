// File: lab10.cpp
// Desc: This is a lab illustrating polymorphism in C++
// Date: 10/27/2025
// Author: Samuel Truong

#include "Drink.h"
#include "Coffee.h"
#include "Matcha.h"
#include <iostream>
#include <string>
using namespace std;

int main() {

  // Drink Pointers to child objects (Polymorphism)
  Drink* coffee = new Coffee ("Caramel Machiatto", "Coffee Beans", "Caramel Drizzle");
  Drink* matcha = new Matcha ("Strawberry Matcha Latte", "Matcha Powder", "Strawberry Puree");
  
  // Coffee functions calls
  coffee->PrintName();
  coffee->DisplayIngredients();
  coffee->FlavorProfiles();
  
  cout << endl;
  
  // Matcha function calls
  matcha->PrintName();
  matcha->DisplayIngredients();
  matcha->FlavorProfiles();

  // Deallocating dynamically allocated coffee and matcha
  delete coffee;
  coffee = nullptr;

  delete matcha;
  matcha = nullptr;
  return 0;

}

