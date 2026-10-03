#include "Register.h"
#include <iostream>
using namespace std;

const string MENU_ITEMS = "menu_items.txt";

int main() {
  Register reg;
  reg.LoadMenu(MENU_ITEMS);
  reg.Run();
  return 0;
}
