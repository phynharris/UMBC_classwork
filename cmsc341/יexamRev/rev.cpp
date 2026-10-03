#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main(){
  int x = 14;
  int y = 10;
  int* p = &x;
  x = 11;
  *p = y;

  cout << x << ", " << y << endl;

  int arr[3] = {1,2,3};
  cout << *(arr + 2) << endl;

  string str[3] = {"Jeree", "hnf", "fgg"};
  cout << *str << endl;


  int a = 1;
  int b = 0;

  cout << (a*b + 1)/4 << endl;


  int xr = 3;
  int& ref = x;
  ref = 10;


  cout << ref << ", " << x << endl;

  char* le_pointer = nullptr;

  delete le_pointer;

  char stringe[] = "Hello";
  cout << stringe[1] << endl;

  int marr[5] = {1,2,3,4,5};

  // cout << marr[6] << endl;

  //marr[60] = 5;

  stack<int> stacc;
  stacc.pop();
  stacc.pop();
  stacc.pop();
  
  return 0;
}
