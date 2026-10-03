#include "Housing.h"

Housing::Housing(){
  m_location = "Earth";
  m_listingStatus = "For Rent";
}// Default constructor

Housing::Housing(string location, string listing){ // Location and Listing Status
  SetLocation(location);
  SetListingStatus(listing);
}
void Housing::Description(){ // Using the member variables, write a description
  cout << "There is housing in " << m_location << " with a " << " status." << endl;

}

string Housing::GetLocation(){        // Getter for m_location
  return m_location;
}

string Housing::GetListingStatus(){   // Getter for m_listingStatus
  return m_listingStatus;
}

void Housing::SetLocation(string location){    // Setter for m_location
  m_location = location;
}

void Housing::SetListingStatus(string listing){ //Setter for m_listingStatus
  m_listingStatus = listing;
}

// Friend function allows user to cout << **housing_object** << endl;
// Overloaded operator <<
// Hint: When implementing this function, it should NOT have Housing::
ostream& operator<<(ostream &out, Housing &myHousing){
  cout << Description();
}
