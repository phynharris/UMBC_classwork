#include "Tree.h"

// Tree::Tree
// Given nothing — Returns nothing
Tree::Tree(): AgItem(){
  m_age = 0;
}

// Tree:~Tree
// Given nothing — Returns nothing
Tree::~Tree(){
  // Iterates through the m_fruit vector and deletes every fruit
  for(unsigned int i = 0; i < m_fruit.size(); i++){
    delete m_fruit.at(i);
  }
}

// Tree::Tick
// Given the total number of food (unused) — Returns nothing
void Tree::Tick(int &food){
  // If a tree is old enough to fruit (12 seasons), then it will start producing fruit
  if(m_age >= SEASONS_TO_FRUIT){
    Fruit *fruit = new Fruit;

    // Fruit is added to the back of the m_fruit vector
    m_fruit.push_back(fruit);
  }

  // Tree ages if it is below its max age
  if(m_age < SEASONS_TO_HARVEST){
    m_age += 1;
  }

  // Increases tree size after 3, 7, and 11 seasons
  if(m_age == 3){
    SetSize(GetSize()+1);
  }

  if(m_age == 7){
    SetSize(GetSize()+1);
  }

  if(m_age == 11){
    SetSize(GetSize()+1);
  }

  // Once a tree turns 60 years old, it is cut down
  if(m_age == SEASONS_TO_HARVEST){
    SetIsHarvestable(true);
  }
}

// Tree::Harvest
// Given current money and food — Returns nothing
void Tree::Harvest(int &money, int &food){
  int fruitAmount = m_fruit.size(); // The total number of fruit
  Fruit* fruit;                     // To represent the current fruit
  
  // If a tree has at least one fruit, then fruit is harvested
  // and food increments by 1
  if(fruitAmount > 0){
    fruit = m_fruit[0];
    m_fruit.pop_back();
    delete fruit;
    food++;
    
    cout << "Fruit was harvested!" << endl;
  }

  // Harvests a tree
  if(GetIsHarvestable()  == true){
    cout << "Tree was harvested!" << endl;
  }
}

// Tree::GetType
// Given nothing — Returns string name of the subtype (Tree)
string Tree::GetType(){
  return "Tree";
}

// Tree:operator<<
// Given the out stream — Returns class specified output
ostream& Tree::operator<<(ostream& os){
  string harvestable = ""; // Lexically displays harvest status
  string fruiting = "";    // Lexically displays fruiting status

  // Checks if tree is harvestable
  if(GetIsHarvestable() == true){
    harvestable = "Harvestable";
  }else{
    harvestable = "Not Harvestable";
  }

  // Checks if tree is fruiting
  if(m_age >= SEASONS_TO_FRUIT){
    fruiting = "Fruiting";
  }else{
    fruiting = "Not Fruiting";
  }

  
  //  Returns output stream with the following format:
  //  Tree  | Seedling | Not Harvestable | Not Fruiting | Fruit Count: 0
  os << GetType() << CONCAT << TREE_SIZE[GetSize()] << CONCAT << harvestable
      << CONCAT << fruiting << CONCAT << "Fruit Count: " <<  m_fruit.size();
  
  return os;
}

