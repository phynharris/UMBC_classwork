#include <iostream>
using namespace std;

int main() {
  int age;
  char name1[80];
  char name2[80];
  cout << "Enter your age: " << endl;
  cin >> age;
  if (cin.peek() == '\n')
    cin.ignore();
  cout << "Enter your first  name: " << endl;
  cin.getline(name1, 80);
  cout << "Enter your last name: " << endl;
  cin.getline(name2, 80);
  cout << "age = " << age << endl;
  cout << "first name = " << name1 << endl;
  cout << "last name = " << name2 << endl;
  
  return 0;
}
