#include "Rectangle.h"

void Rectangle::SetSides(double length, double width){
  if(length <= 0){
    m_length = 1;
    cout << "Lenght must be a positve number." << endl;
  }else{
    m_length = length;
  }
  
  if(width <= 0){
    m_width = 1;
    cout << "Width must be a positve number." << endl;
  }else{
  m_width = width;
  }
  
  return;
}

double Rectangle::CalcArea(){
  return m_length * m_width;
}

double Rectangle::CalcPerimeter(){
  return 2 * (m_length + m_width);
}

bool Rectangle::IsSquare(){
  return m_length == m_width;
}

void Rectangle::Rotate(){
  double temp = m_length;
  m_length = m_width;
  m_width = temp;
  return;
}
