/* Title: lab11a.cpp
   Course: CMSC 202 - Fall 2025
   Description: This introduces templated functions.
*/
#include <iostream>
#include <string>
using namespace std;

// COMPLETE THESE TWO FUNCTIONS
// Write a templated function named addValues that adds two values of type T
// and returns the result
template <class T>
T addValues(const T& a, const T& b){
  return a + b;
}

template <class T>
T subtractValues(const T& a, const T& b){
  return a - b;
}

// Write a templated function named subtractValues that subtracts two values of
//  type T and returns the result


// Main is provided.
int main() {
  cout << "Adding integers: " << addValues(5, 10) << endl;
  cout << "Adding doubles: " << addValues(2.5, 3.5) << endl;
  cout << "Adding chars (as ASCII): " << addValues('!', ')') << endl;
  cout << "Adding strings: " << addValues(string("Hello "), string("World!")) << endl;

  cout << endl;
  cout << "Subtracting integers: " << subtractValues(10, 5) << endl;
  cout << "Subtracting doubles: " << subtractValues(7.5, 2.5) << endl;
  cout << "Subtracting chars (as ASCII): " << subtractValues('x', '6') << endl;

  return 0;
}
