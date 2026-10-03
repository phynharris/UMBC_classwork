/*
* File: SodaCup.h
* Project: CMSC202 Lab 6, Fall 2025
*/

#ifndef SODACUP_H //Header guards
#define SODACUP_H //Header guards

#include <iostream>
#include <string>
using namespace std;

class SodaCup {
 public:
  SodaCup(); //default constructor

  SodaCup(string name, int type); //overloaded constructor

  // GetName() returns the name of the customer for this cup
  string GetName();

  // GetFlavor() returns a code representing the flavor of the soda
  int GetFlavor();

  // SetName() sets m_name to name
  void SetName(string name);

  // SetFlavor() sets m_flavor to flavor
  void SetFlavor(int flavor);

 private:
  string m_name; // name of the customer
  int m_flavor; // flavor code of the task (e.g. pepsi, drpepper, mountaindew)
};

#endif
