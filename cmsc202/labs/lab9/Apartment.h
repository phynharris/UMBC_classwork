/*
* Apartment.h - 
* Implement Apartment.cpp
* Child class of Housing
*/

#ifndef APARTMENT_H //Header Guard
#define APARTMENT_H //Header Guard
#include "Housing.h" //Parent class
#include <iostream>
#include <string>
using namespace std;

//constants
const int LAYOUT_SIZE = 3; // Number of possible layouts in Apartment
const string LAYOUTS[LAYOUT_SIZE] = {"Studio", "Duplex", "Penthouse"};

class Apartment : public Housing {
public:
  Apartment(); // Default constructor and calls RandLayout
  Apartment(string, string); //Location, Listing Status and calls RandLayout
  void RandLayout();       // Randomly assigns one LAYOUT to m_layout
  string GetLayout();      // Getter for m_layout (extending parent)
  void SetLayout(string);  // Setter for m_layout (extending parent)
  void Visit();            // The apartment is visited (extending parent)
private:
  string m_layout;         // Random layout assigned
};

#endif
