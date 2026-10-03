#include "Bakery.h"

/*************************************************************** 
** File: Bakery.cpp
** Description: This file contains the Bakery class function definitions
***************************************************************/

//Constructor - Already implemented for you
Bakery::Bakery() {
  cout << "It is your first day managing the UMBC Bakery.\n";
  cout << "Time to sell some food!\n";
  m_revenue = 0; // money made so far
  m_cakes = 0; // cakes available
  m_cakePrice = 0; // price for a single cake
  m_bread = 0; // number of bread available
  m_breadPrice = 0; // price for a single bread
}

//Implement Getters here (get bread count, cake price, bread price, revenue)
int Bakery::GetBreadCount(){
  return m_bread;
}

double Bakery::GetCakePrice(){
  return m_cakePrice;
}

double Bakery::GetBreadPrice(){
  return m_breadPrice;
}

double Bakery::GetRevenue(){
  return m_revenue;
}

//Getter for m_cakes already implemented for you
int Bakery::GetCakeCount(){
  return m_cakes;
}

//Implement Setters here (set bread count, cake price, bread price, revenue)
void Bakery::SetBreadCount(double bread){
  m_bread = bread;
}

void Bakery::SetCakePrice(double cakePrice){
  m_breadPrice = cakePrice;
}

void Bakery::SetBreadPrice(double breadPrice){
  m_breadPrice = breadPrice;
}

void Bakery::Revenue(double revenue){
  m_revenue = revenue;
}

//Setter for m_cakes already implemented for you
void Bakery::SetCakeCount(int cakes){
  m_cakes = cakes;
}

//Implement SellCake here
void Bakery::SellCake(){
  if(m_cakes > 0){
    m_cakes -= 1;
    m_revenue += m_cakePrice;
  }
}




//Implement SellBread here
void Bakery::SellBread(){
  if(m_bread > 0){
    m_bread -= 1;
    m_revenue += m_breadPrice;
  }
}




//SellAll already implemented for you
void Bakery::SellAll(){
  double revenue = m_cakes * m_cakePrice + m_bread * m_breadPrice;
  m_revenue += revenue;
  m_cakes = 0;
  m_bread = 0;
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  cout << "You just sold merch with a total value of: $" << revenue << endl;
}

