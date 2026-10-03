#include <iostream>
using namespace std;

void displayResults(double myArray[]);

int main(){
  double myArray[6] = {2, 3, 4, 5, 6, 7};
  cout << sizeof(myArray) << endl;
  displayResults(myArray);
  
  
  return 0;
}

void displayResults(double myArray[]){
  int sum = 0;
  double product = 1;

  int size = sizeof(myArray);
  cout << "SIZE: " << size << endl;
  for(int i = 0; i < size; i++){
    sum += myArray[i];
    cout << product << ":" << myArray[i] << endl;
    product *= myArray[i];
  }
  cout << "Sum: " << sum << endl;
  cout << "Product: " << product * 4 << endl;
}
