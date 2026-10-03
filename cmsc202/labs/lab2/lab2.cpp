#include <iostream>
#include <cmath>

using namespace std;

double doubleRemainder();
void greaterThanTwenty(double);

int main(){
   greaterThanTwenty(doubleRemainder());

  return 0;
}


double doubleRemainder(){
  double  dividend = 0;
  double  divisor = 1;
  double modulo = 0;
  
  cout << "Enter the dividend: " << endl;
  cin >> dividend;
  cout << "Enter the divisor: " << endl;
  cin >> divisor;

  modulo = fmod (dividend, divisor);

  cout << "Moduluo is: " << modulo << endl;
   
  return modulo;
}

void greaterThanTwenty(double num){
  const double LIMIT = 20;

  if(num > LIMIT){
    cout << "The number is greater than 20." << endl;
  }else{
    cout << "The number is less than 20. " << endl;
  }

  return;
}
