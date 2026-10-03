#include "Vegetable.h"

// Vegetable::Vegetable
// Given nothing — Returns nothing
Vegetable::Vegetable(): AgItem(){

}

// Vegetable::Harvest
// Given the current money and food — Returns nothing
void Vegetable::Harvest(int &money, int &food){
  // If a vegetable has reached its max size, it is harvested and food increments by 1
  if(GetIsHarvestable() == true){
    food += GetSize();
    cout << "Vegetable was harvested!" << endl;
  }
}

// Vegetable::Tick
// Given the current food (unused) — Returns nothing
void Vegetable::Tick(int &food){
  // If a vegetable is not at its max size yet, then its size increments by 1
  if(GetSize() < MAX_VEG_SIZE){
    SetSize(GetSize() + 1);
    
  // Otherwise, the vegetable is harvested
  }
  if(GetSize() >= MAX_VEG_SIZE){
    SetIsHarvestable(true);
  }
}

// Vegetable::GetType
// Given nothing — Returns string name of the subtype (Vegetable)
string Vegetable::GetType(){
  
  return "Vegetable";
}

// Vegetable:operator<<
// Given the ouput stream — Returns class specified output
ostream& Vegetable::operator<<(ostream& os){
  string harvestable = ""; // Lexically displays harvest status

  // Checks if vegetable is harvestable
  if(GetIsHarvestable() == true){
    harvestable = "Harvestable";
  }else{
    harvestable = "Not Harvestable";
  }
  
  // Returns output stream with the following format
  // Vegetable | Not Harvestable | Seedling
  os << GetType() << CONCAT << harvestable << CONCAT << Veg_Size[GetSize()];
  return os;
}

