#include "SodaCup.h"

/*
string m_name; // name of the customer
  int m_flavor;
 */

SodaCup(){

}

SodaCup(string name, int type){ //overloaded constructor
  GetName(name);
  GetFlavor(type);
}

// GetName() returns the name of the customer for this cup
string GetName(){

  return m_name;
  
}

// GetFlavor() returns a code representing the flavor of the soda
int GetFlavor(){

  return m_flavor;
}

// SetName() sets m_name to name
void SetName(string name){
  m_name = name;
}

// SetFlavor() sets m_flavor to flavor
void SetFlavor(int flavor){
  m_flavor = flavor;
}
