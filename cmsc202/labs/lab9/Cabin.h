/*
* Cabin.h - 
* Implement Cabin.cpp
* Child class of Housing
*/

#ifndef CABIN_H //Header Guard
#define CABIN_H //Header Guard
#include "Housing.h" //Parent class
#include <iostream>
#include <string>
using namespace std;

class Cabin : public Housing {
public:
  Cabin(); // Default constructor
  Cabin(string, string, string);// Location, Listing Status, and Material
  void Description(); // Using m_material, displays Cabin desc
                      //   to match the sample output
                      // Replacing parent class function
  string GetMaterial();     // Getter for m_material
  void SetMaterial(string); // Setter for m_material
private:
  string m_material; // String holds material of the cabin
};
#endif
