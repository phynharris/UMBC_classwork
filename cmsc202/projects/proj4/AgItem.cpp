#include "AgItem.h"

// Constants
const int DEFAULT_SIZE = 0;
const int DEFAULT_WORTH = 1;
const bool DEFAULT_HARVESTABLE = false;

// AgItem::AgItem
// Given nothing — Returns nothing
AgItem::AgItem(){
  SetSize(DEFAULT_SIZE);
  SetWorth(DEFAULT_WORTH);
  SetIsHarvestable(DEFAULT_HARVESTABLE);
}

// AgItem::AgItem
// Given an item's size, worth, and harvest status — Returns nothing
AgItem::AgItem(int size, int worth, bool isHarvestable){
  SetSize(size);
  SetWorth(worth);
  SetIsHarvestable(isHarvestable);
}

// AgItem:~AgItem
// Give nothing — Returns nothing
AgItem::~AgItem(){

}

// AgItem::GetSize
// Given nothing — Returns an item's size
int AgItem::GetSize(){
  return m_size;
}

// AgItem::GetWorth
// Given nothing — Returns an item's worth
int AgItem::GetWorth(){
  return m_worth;
}

// AgItem::GetIsHarvestable
// Given nothing — Returns an item's harvest status
bool AgItem::GetIsHarvestable(){
  return m_isHarvestable;
}

// AgItem::SetSize
// Given an item's size — Returns nothing
void AgItem::SetSize(int size){
  if(size < 0){
    m_size = DEFAULT_SIZE;
  }else{
    m_size = size;
  }
}

// AgItem::SetIsHarvestable
// Given an item's harvest status — Returns nothing
void AgItem::SetIsHarvestable(bool isAlive){
  if(isAlive == false){
    m_isHarvestable = DEFAULT_HARVESTABLE;
  }else{
    m_isHarvestable = isAlive;
  }
}

// Name: AgItem::SetWorth
// Given an item's worth — Returns nothing
void AgItem::SetWorth(int worth){
  if(worth < 1){
    m_worth = DEFAULT_WORTH;
  }else{
    m_worth = worth;
  }
}
