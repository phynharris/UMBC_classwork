/***************************************************************
** Topic: Lab 5
** File: Bakery.h
** Description: This file contains the Bakery class declaration
***************************************************************/

#ifndef BAKERY_H //Header Guards
#define BAKERY_H //Header Guards

#include <iostream>
#include <string>
using namespace std;


// Declare the Bakery class here
// Make sure to include a generic constructor,
// getters and setters for all member variables,
// and the functions described in the document

class Bakery {
public:
  //Constructor for Bakery (implementation provided)
  void Bakery();

  //Getters
  //Getter for cakes Available (implementation provided)
  int GetCakes();

  //Getter for total bread Available
  int GetBread();

  //Getter for Cake Price
  double GetCakePrice();

  //Getter for Bread Price
  double GetBreadPrice();

  //Getter for Revenue
  double GetRevenue();

  
  //Setters
  //Sets Number of Cakes Available (implementation provided)
  void SetCakeCount(int cakes);

  //Sets Number of Bread Available
  void SetBreadCount(int bread);

  //Sets Cake Price
  void SetCakePrice(double cakePrice);

  //Sets Bread Price
  void SetBreadPrice(double breadPrice);

   //Sets Total Revenue
  void SetRevenue(double revenue);

  
  //Other
  //Sell a Cake
  //Implement SellCake here
  void SellCake();

  //Sell a Bread
  void SellBread();

  //Sell All (implementation provided)
  void SellAll();

  
//Declare five member variables
//(cake count, bread count, cake price, bread price, revenue)
//Hint: You can get the correct names from the Bakery.cpp file or lab doc
private:
  double m_revenue = 0; // money made so far
  int m_cakes = 0; // cakes available
  double m_cakePrice = 0; // price for a single cake
  int m_bread = 0; // number of bread available
  double m_breadPrice = 0; // price for a single bread




};

#endif //End of Header Guards
