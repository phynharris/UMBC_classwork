#include "Animal.h"

// Animal:Animal
// Given nothing — Returns nothing
Animal::Animal(): AgItem(){
  m_name = "Chicken";
}

// Anima::Tick
// Given the current amount of food to update — Returns nothing
void Animal::Tick(int &food){
  // If there is food, then an animal is fed
  // and food is decremented by 1
  if(food > 0){
    --(food);
    SetIsHarvestable(false);
    m_IsHungry = false;

    // If an animal is not yet at its max size, then it's size increments by 1
    if(GetSize() < ANIMAL_MAX_SIZE){
      SetSize(GetSize() + 1);
    }

    // If the animal reaches its max size, it becomes harvestable
    if(GetSize() == ANIMAL_MAX_SIZE){
      SetIsHarvestable(true);
    }

  // Animals are not fed if there is no food
  }else if(food == 0){
    SetIsHarvestable(true);
    
    // Animal becomes hungry if not fed
    if(m_IsHungry == false){
      m_IsHungry = true;
    }  
  }
}

// Animal::Harvest
// Given the current money and food — Returns nothing
void Animal::Harvest(int &money, int &food){
  // Harvests an animal
  if(GetIsHarvestable() == true){
    // If an animal is hungry, it's size is set to small
    if(m_IsHungry == true){
      SetSize(1);
    }
    money += GetWorth() * GetSize();
    
    cout << "Animal was harvested!" << endl;
  }
}

// Animal::GetType
// Given nothing — Returns the name of the subtype (Animal)
string Animal::GetType(){

  return "Animal";
}

// Animal:operator<<
// Given the outstream — Returns class specified output
ostream& Animal::operator<<(ostream& os){
  string harvestable = ""; // Lexically displays harvest status
  string fed = "";         // Lexically displays fed status

  // Checks if an animal is harvestable
  if(GetIsHarvestable() == true){
    harvestable = "Harvestable";
  }else{
    harvestable = "Not Harvestable";
  }

  // Checks if an animal is fed
  if(m_IsHungry == true){
    fed = "Hungry";
  }else{
    fed = "Fed";
  }

  // Returns output stream with the following format:
  // Animal | Chicken | Not Harvestable | Born | Fed
   os << GetType() << CONCAT << m_name << CONCAT << harvestable
    << CONCAT << ANIMAL_SIZE[GetSize()] << CONCAT << fed;
   
   return os;
}

