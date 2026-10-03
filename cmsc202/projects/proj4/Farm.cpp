#include "Farm.h"

// Farm::Farm
// Given nothing — Returns nothing
Farm::Farm(){
  // Creates a default farm with preset stats
  m_food = 6;
  m_money = 0;
  m_season = 1;
}

// Farm::~Farm
// Given nothing — Returns nothing
Farm::~Farm(){
  // Iterates through and clears each item out of the farm
  for(int i = 0; i < int(m_farm.size()); i++){
    delete m_farm[i];
  }
}

// Farm::ChooseItem
// Given nothing — Returns the user's choice
int Farm::ChooseItem(){
  int choice = 0;

  // Prompts user to pick an AgItem
  while(choice < 1 || choice > 3){
    cout << "Select an item: " << "\n1. Animal" << "\n2. Vegetable" << "\n3. Tree" << endl;
    cin >> choice;
  }
  
  return choice;
}

// Farm::AddItem
// Given a number paired with a particular item and the quantity of the item
// Returns nothing
void Farm::AddItem(int type, int quantity){
  // Enters an animal into the farm vector
  if(type == 1){
    for(int i = 0; i < quantity; i++){
      Animal* animal = new Animal();
      m_farm.push_back(animal);
    }

  // Enters a vegetable into the farm vector
  }else if(type == 2){
    for(int i = 0; i < quantity; i++){
      Vegetable* vegetable = new Vegetable();
      m_farm.push_back(vegetable);
    }

  // Enters a tree into the farm vector
  }else if(type == 3){
    for(int i = 0; i < quantity; i++){
      Tree* tree = new Tree();
      m_farm.push_back(tree);
    }
  }
}

// Farm::Tick
// Given the number of seasons — Returns nothing
void Farm::Tick(int seasons){
  int j = 0;                      // Counter variable
  int j_max = int(m_farm.size()); // The upper bound for the m_farm vector; prone to decrement
  bool harvested = true;          // Checks if an item has been harvested

  // Ticks for each season passed for each item
  for(int i = 0; i < seasons; i++){
    while(j < j_max){

      // The following occurs if the farm is not empty
      // and while the counter is less than the max
      if(m_farm.size() > 0 && j < j_max){

	// While the previous item was harvested (True by default)
	// An item is harvested and then deleted
	while(harvested == true){

	  // Does not delete item if...
	  // - The counter is not smaller than the upper bound
	  // - The current item is not harvestable
	  // - There are no more items in the farm
	  if(j < j_max){
	    m_farm.at(j)->Harvest(m_money, m_food);
   
	    if(m_farm.at(j)->GetIsHarvestable() == true){
	      
	      delete m_farm.at(j);
	      
	      m_farm.erase(m_farm.begin()+j);
	      j_max--;

	      if(m_farm.size() == 0){
		harvested = false;
	      }else{
		harvested = true;
	      }
	      
	    }else{
	      harvested = false;
	    }
	    
	  }else{
	    harvested = false;
	  }
	}

	// Ticks for each item in m_farm
	if(m_farm.size() > 0 && j < j_max){
	  m_farm.at(j)->Tick(m_food);
	}

	j++;
	harvested = true;
      }
    }
    Status();
    m_season++;
    j = 0;
    cout << endl;
  }
}

// Farm::Menu
// Give nothing — Returns the user's choice
int Farm::Menu(){
  // Prompts the user to make a choice from the available options
  int choice = 0;
  while(choice < 1 || choice > 5){
    cout << "What do you wanna do?" << endl
	 << "1. Add Item to Farm" << endl
	 << "2. Add Two of Each Item to Farm" << endl
	 << "3. Simulate Time" << endl
	 << "4. Farm Status" << endl
	 << "5. Quit" << endl;
    cin >> choice;
  }
  
  return choice;
}

// Farm::StartSimulation
// Given nothing — Returns nothing
void Farm::StartSimulation(){
  int choice = 0;      // The user's menu choice
  int itemChoice = 0;  // The item the user selects
  int seasons = 0;     // The seasons that have passed

  // Program runs while choice isn't 5 "quit"
  do{
    // Prompts the user's choice
    choice = Menu();

    switch(choice){
    // Allows the user to enter a particular item into the m_farm vector 
    case 1:
      itemChoice = ChooseItem();
      AddItem(itemChoice, 1);
      cout << endl;
      break;
    // Enters two of each item into the m_farm vector
    case 2:
      for(int i = 1; i <= 3; i++){
	  AddItem(i, 2);
      }
      cout << endl;
      break;
    // Prompts the user to enter how many seasons to pass by
    // Ticks for each item per season
    case 3:
      seasons = 0;
      while(seasons < 1){
	cout << "How many seasons would you like to simulate? " << endl;
	cin >> seasons;
      }
      cout << endl;
      Tick(seasons);
      
      break;
    // Prints the status of each item in m_farm
    case 4:
      cout << endl;
      Status();
      cout << endl;
      break;
    // Quits the program
    case 5:
      cout << "Auf Wiedersehen!" << endl;
      break;
    }
  }while(choice != 5);
	 
  return;
}

// Farm::Status
// Given nothing — Returns nothing
void Farm::Status(){
  
  // Prints the statuses of food, money, and season
  cout << "SEASON: " << m_season << endl
       << "****Farm Status****" << endl
       << "Food: " << m_food << endl
       << "Money: " << m_money << endl
       << "Season: " << m_season << endl;

  if(m_farm.size() == 0){
    cout << "No items in farm." << endl;
  }else{
  // Prints the statuses of each AgItem
    for(unsigned int  i = 0; i < m_farm.size(); i++){
      (*m_farm.at(i)) << cout << endl;
    }
  }
}
