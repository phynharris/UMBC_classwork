/*
* Housing.h - 
* Implement Housing.cpp
*/

#ifndef HOUSING_H //Header guard
#define HOUSING_H //Header guard
#include <iostream>
#include <string>
using namespace std;

class Housing {
public:
  Housing(); // Default constructor
  Housing(string, string); // Location and Listing Status
  void Description(); // Using the member variables, write a description
  string GetLocation();        // Getter for m_location
  string GetListingStatus();   // Getter for m_listingStatus
  void SetLocation(string);    // Setter for m_location
  void SetListingStatus(string); //Setter for m_listingStatus
  // Friend function allows user to cout << **housing_object** << endl;
  // Overloaded operator <<
  // Hint: When implementing this function, it should NOT have Housing::
  friend ostream& operator<<(ostream &out, Housing &myHousing);
private:
  string m_location;      //Housing's location 
  string m_listingStatus; //Housing Listing Status
};

#endif //Header guard
