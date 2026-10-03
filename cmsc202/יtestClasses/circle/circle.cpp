#include <iostream>
#include <cmath>
using namespace std;

class Circle{
public:
  void SetRadius(double radius);
  double CalcArea();

 private:
  double m_radius; //member variable

};


int main(){
  Circle myCircle;
  myCircle.SetRadius(10);
  cout << myCircle.CalcArea() << endl;
  
  return 0;
}

void Circle::SetRadius(double radius){
  if(radius <= 0){
    radius = 1;
    cout << "Radius must be a positive number. " << endl;
  }else{
    m_radius = radius;
  }
}

double Circle::CalcArea(){

  return M_PI * m_radius * m_radius;
}
