#include <iostream>
using namespace std;

int foo(double num1, double num2, double num3);
void foo(double &num1, double &num2);

int main(){
  double num1 = 5;
  double num2 = 4;
  foo(num1, num2);
  num1 = foo(num1, num2, 3);
  cout << num1 << endl;

  return 0;
}

void foo(double &num1, double &num2){
  num2 += num1;
}

int foo(double num1, double num2, double num3){
  return (num1 * num2)/num3;
}
