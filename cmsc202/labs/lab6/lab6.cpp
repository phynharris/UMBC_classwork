/*
* File: lab6.cpp
* Assignment: CMSC202 Lab 6, Fall 2025
* Author:
* Date:                    
* Email:
* Makes a todo list using user input, then displays it.
*/

#include "SodaCup.h"
#include <vector>
#include <iostream>
using namespace std;

// sets PEPSI = 0, DRPEPPER = 1, MOUNTAINDEW = 2
enum FLAVOR_CODE { PEPSI, DRPEPPER, MOUNTAINDEW };

// To Do:
// 1. Write SodaCup.cpp and make sure it compiles (make SodaCup.o).
// 2. Write FillSodaOrder below.
// 3. Write DisplayWithoutIterator below.
// 4. Write void DisplayWithIterator below

// Write FillSodaOrder here:
void FillSodaOrder(vector<SodaCup> &sodaOrder) {
  // Declare variables to hold number of customers, flavors, and name

  
  // Ask the user for number of customers
  

  // Clear input buffer
  
  
  // Iterate through number of customers
  // Get customer name and flavor for each customer


  // Clear input buffer

  
  // Create a SodaCup object with the info and push it to the vector.

  
  // You may have to use:
  //   if(cin.peek() == '\n')
  //      cin.ignore(256, '\n');
  // to clear the buffer.
  
} // End of FillSodaOrder


// You may use this code for the DisplayWithoutIterator
// and DisplayWithIterator use this code
/*
  switch (FILL THIS IN) {
  case PEPSI:
    cout << "- Pepsi for ";
    break;
  case DRPEPPER:
    cout << "- DrPepper for ";
    break;
  case MOUNTAINDEW:
    cout << "- MountainDew for ;
    break;
  default:
    cout << "- unknown flavor for ";
    break;
  }
*/

// Please write DisplayWithoutIterator.
// Display the number of soda cups in the order.
// For each bucket, display the flavor and name.
// Use a switch statement to display the flavor (provided).
// Don't forget to display the name as well.
void DisplayWithoutIterator(vector<SodaCup> &sodaOrder) {

}

// Please write DisplayWithIterator.
// This function is the same as the one above, but uses an iterator to display
// the todo list.
void DisplayWithIterator(vector<SodaCup> &sodaOrder) {

}



// Main
// Provided.

int main() {
  vector<SodaCup> sodaOrder; //Creates an empty vector
  FillSodaOrder(sodaOrder); //Populates sodaOrder
  
  cout << "Displaying Soda Order without iterator:" << endl;
  DisplayWithoutIterator(sodaOrder); //Displays information using loop
  cout << endl << "Displaying Soda Order with iterator:" << endl;
  DisplayWithIterator(sodaOrder); //Displays information using iterators

  cout << endl << "Enjoy the drink(s)!" << endl;
  return 0;
}
