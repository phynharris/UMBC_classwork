//Comments
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <iostream>
using namespace std;

class Rectangle{
 public:
  void SetSides(double height, double width);
  double CalcArea();
  double CalcPerimeter();
  bool IsSquare();
  void Rotate();

 private:
  double m_width;
  double m_length;



};

#endif
