#include "Matcha.h"

// Constructor
// Preconditions: None
// Postconditions: None
Matcha::Matcha(): Drink("DrinkName"){
  m_ingredient1 = "DefIngredient1";
  m_ingredient2 = "DefIngredient2";
}

// Overloaded Constructor
// Preconditions: None
// Postconditions: Member variables initialized
Matcha::Matcha(string name, string ingredient1, string ingredient2): Drink(name){
  m_ingredient1 = ingredient1;
  m_ingredient2 = ingredient2;
}

// Destructor
// Hint: Nothing is dynamically allocated in Matcha so empty
// Preconditions: None
// Postconditions: None
Matcha::~Matcha(){
}

// DisplayIngredients() - shows Matcha's ingredients
// Preconditions: has a name and two ingredients
// Postconditions: None
void Matcha::DisplayIngredients(){
  cout << GetName() << ": " << m_ingredient1 << " & " << m_ingredient2 << endl;
}

// FlavorProfiles() - describes Matcha's flavor profiles
// Preconditions: None
// Postconditions: None
void Matcha::FlavorProfiles(){
  cout << "The flavor grosses you out, you think the matchs is expired." << endl;

}
