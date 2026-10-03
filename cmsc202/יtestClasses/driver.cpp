#include <iostream>
#include "Rectangle.h"
using namespace std;

int main(){
  Rectangle myRect;
  myRect.SetSides(-10, -10);
  cout << "Area: " << myRect.CalcArea() <<  endl;
  cout << "Perimeter: " << myRect.CalcPerimeter() << endl;
  cout << "Is Square? " << myRect.IsSquare() << endl;
  
  return 0;
}
