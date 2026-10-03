#include "Coffee.h"


// Constructor
// Preconditions: None
// Postconditions: None
Coffee::Coffee(): Drink("DrinkName"){
  m_ingredient1 = "Def Ingredient1";
  m_ingredient2 = "Def Ingredient2";
}

// Overloaded Constructor
// Preconditions: None
// Postconditions: Member variables initialized
Coffee::Coffee(string name, string ingredient1, string ingredient2): Drink(name){
  m_ingredient1 = ingredient1;
  m_ingredient2 = ingredient2;
}

// Destructor
// Hint: Nothing is dynamically allocated in Coffee so empty
// Preconditions: None
// Postconditions: None
Coffee::~Coffee(){

}

// DisplayIngredients() - shows Coffee's Ingredients
// Preconditions: has a name and two Ingredients
// Postconditions: None
void Coffee::DisplayIngredients(){

  cout << GetName() << ": " << m_ingredient1 << " & " << m_ingredient2 << endl;
  
}


// FlavorProfiles() - describes Coffee flavor profiles
// Preconditions: None
// Postconditions: None
void Coffee::FlavorProfiles(){

  cout << "Tastes as bitter as the hatred it was made with." << endl;
}
