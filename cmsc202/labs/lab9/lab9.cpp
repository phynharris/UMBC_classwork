#include "Housing.h" //Parent class
#include "Apartment.h" //Child class 1
#include "Cabin.h" //Child class 2
#include <time.h> //For seeding random number
#include <cstdlib> //For srand and rand
#include <iostream> //For cout
using namespace std;

int main() {
  srand(time(NULL)); //Seeds random number generator
  
  //Parent class example
  cout << "Parent Class Example" << endl;
  Housing myHousing("Dallas", "For Sale"); //Creates housing
  cout << myHousing; //Calls overloaded operator
  cout << "****END****" << endl << endl;

  //Child class example 1	
  cout << "Child Class Example (Apartment)" << endl;
  Apartment myApartment("New York City", "For Rent");
  myApartment.Description(); //Calls parent class function (use)
  myApartment.Visit(); //Calls child class function (extend)
  cout << "****END****" << endl << endl;

  //Child class example 2
  cout << "Child Class Example (Cabin)" << endl;
  Cabin myCabin("Maine", "Sold", "Brick");
  myCabin.Description(); //Calls child class function (replace)
  myCabin.Housing::Description(); //calls parent class function (use)
  cout << "****END****" << endl << endl;
  
  return 0;
}


