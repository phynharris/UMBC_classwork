/************************************************************************
** File: lab5.cpp
** Description: Uses a Bakery to demonstrate how classes work in C++

*** You should go through the lab document as you complete this lab ***

************************************************************************/

#include "Bakery.h"
#include <iostream>
#include <string>

using namespace std;

// Declare DisplayInfo here (provided)
void DisplayInfo(Bakery myBakery);

int main() {
  // Creates Bakery object
  Bakery myBakery;

  // Constant for number of cakes and bread
  const int NUM_CAKES = 15;
  const int NUM_BREAD = 25;
  const double PRICE_CAKE = 29.99;
  const double PRICE_BREAD = 8.99;

  // Use setters to populate member variables of the Bakery
  // Make 15 cakes with a price of $29.99 a cake using constants
  myBakery.SetCakeCount(NUM_CAKES);
  myBakery.SetCakePrice(PRICE_CAKE);

  // Make 25 bread with a price of $8.99 a bread using constants
  myBakery.SetBreadCount(NUM_BREAD);
  myBakery.SetBreadPrice(PRICE_BREAD);
  
  // Displays inventory at the giftshop
  DisplayInfo(myBakery);

  // Sell a single cake
  cout << "Selling a copy of CAKE: THE LIE!" << endl;
  myBakery.SellCake();
  DisplayInfo(myBakery);

  // Sell a single bread
  cout << "Selling a copy of BREAD: FRENCH BAGUETTE!" << endl;
  myBakery.SellBread();
  DisplayInfo(myBakery);

  // Sells the rest of the items and displays overall revenue
  cout << "Selling all our inventory!" << endl;
  myBakery.SellAll();

  // Displays the total revenue after selling all of the items
  cout << "\nToday's Revenue: $" << myBakery.GetRevenue() << "\n" << endl;
  
  return 0;
}

//Implement displayInfo here
void Bakery::DisplayInfo(Bakery myBakery){
  myBakery.GetCakes();
  myBakery.GetBread();
  myBakery.GetCakePrice();
  myBakery.GetBreadPrice();
  myBakery.GetRevenue();
}
//Displays cakes and bread available (Getters)
//Displays cake and bread cost per item (Getters)
//Displays current revenue at store (Getter)
//Hint use precision or setprecision and fixed to show currency

