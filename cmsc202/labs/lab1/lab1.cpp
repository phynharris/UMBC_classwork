#include <iostream>
#include <string>
using namespace std;

int main(){
  // Variables
  string name = "";
  int age = 0;
  int choice = 0;
  bool checked_bulb = false;
  bool checked_squirt = false;
  bool checked_char = false;


  // Gets the user's name and age.
  cout << "What is your name? " << endl;
  cin >> name;
  cout << "\nWhat is your age? " << endl;
  cin >> age;

  // While the user's age is outside of 10 and 122, the user will be re-prompted.
  while (age < 10 or age > 122){
    cout << "\nApologies, but we can't legally allow you to get a Pokémon." << endl
	 << "Buuuut, if you say something else, I can pretened I didn't hear you the first time." << endl
         << "(Please re-enter your age)" << endl;
    cin >> age;
  };

   cout << "\nWelcome, Pokémon trainer, " << name << "!" << endl
        << "Before you start your journey, you must pick a starter Pokémon." << endl
        << "Take a moment to reveal your options.\n" << endl;
  do{
    cout << "What would you like to do?" << endl
	 << "1: Learn about Bulbasaur \n2: Learn about Squirtle \n3: Learn about Charmander"
	 << endl;
    cin >> choice;
    if (choice == 1){
      cout << "\nIt carries a seed on its back right from birth. By" << endl
	   << "soaking up the sun's rays, the seed grows" << endl
	   << "progressively larger. It is filled with nutrients." << endl
	   << "Able to go for days without eating a single morsel, it" << endl
	   << "uses this to grow while its young.\n" << endl;
      checked_bulb = true;
      
    }else if (choice == 2){
      cout << "\nIts shell is soft immediatelt after it is born. In no" << endl
	   << "time at all, the shell becomes so resilient that a" << endl
	   << "prodding finger will bounce right off it. It hides in" << endl
	   << "its shell to protect itself, thens strikes back with " << endl
	   << "spouts of water at every opportunity.\n" << endl;
      checked_squirt = true;
      
    }else if (choice == 3){
      cout << "\nFrom the time it is born, a flame burns at the tip of" << endl
	   << "its tail. It shows the strenght of its life-force. If" << endl
	   << "Charmander is weak, the flame also burns weakly. If" << endl
	   << "Charmander is healthy, the flame will burn vigorously" << endl
	   << "and won't go out, even if it gets wet.\n" << endl;
      checked_char = true;
    }else{
      cout << "\nThat is not an option.\n";
	};
      }while (!(checked_bulb == true  && checked_squirt == true && checked_char == true));

  cout << "What do you mean you want a Pikachu? Get out!" << endl;
  return 0;
}
