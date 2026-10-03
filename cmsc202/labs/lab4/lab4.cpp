/*****************************************
 ** File:    lab4.cpp
 ** Project: CMSC 202 Lab 4, Fall 2025
 **
 ** Lab 4 involves passing data to void functions by reference
 ** and by using pointers.
 **
 ***********************************************/
#include<iostream>
using namespace std;

// Four Constants
// (including the number of cups in a gallon and milliliters in a liter)
const double CUPS_TO_ML = 236.59;
const double ML_TO_CUPS =  0.0041667;
const double LITER = 1000.0;
const double GALLON = 15.7725;



// Function Prototypes for two functions described
void toMilliliters(double &volume);

void toCups(double *volume);


int main(){
  double volume = 0.0; // Input for converting
  int choice = 0; // Menu choice

  cout << "Welcome to Volume Conversion tool " << endl << endl;
 
  do {
    cout << "Please select below: " << endl;
    cout << "1. Convert from cups to milliliters" << endl;
    cout << "2. Convert from milliliters to cups" << endl;
    cout << "3. Exit"<< endl;
    cin >> choice; 
    
    // Check for validation
    if (choice < 1 || choice > 3) {
      while (choice < 1 || choice > 3) {
        cout << "\nInvalid selection. Please re-enter: " << endl;
        cin >> choice;
      }
    }
    if (choice == 1){
      cout<<"\nVolume in cups: " ;
      cin >> volume;
      toMilliliters(volume);
      cout << "Volume in milliliters: " << volume << endl;
    }
    
    if (choice == 2){
      cout<<"\nVolume in milliliters: " ;
      cin >> volume;
      toCups(&volume);
      cout << "Volume in cups: " << volume << endl;
    }
    
    cout << endl;
    
  }while(choice != 3);
  
  cout << "Have a good one!" << endl;
  
  return 0;
}

// Write function toMilliliters here
// Convert from cups to milliliters using pass by reference
void toMilliliters(double &volume){
  volume = volume * CUPS_TO_ML;
  
  if(volume > LITER){
    cout << "That's bigger than 1 liter." << endl;
  }
  
  return;
}





// Write function toCups here
// Convert from milliliters to cups using pointers
void toCups(double *volume){
  *volume  = *volume * ML_TO_CUPS;
  
  if(*volume > GALLON){
    cout << " That's bigger than 1 gallon." << endl;
  }

}
