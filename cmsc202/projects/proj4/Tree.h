//Title: Tree.h
//Author: Jeremy Dixon
//Date: 10/25/2025
//Description: Describes the child class Tree (which fruits) - Parent is AgItem

#ifndef TREE_H
#define TREE_H
#include "AgItem.h"
#include "Fruit.h"
#include <vector>

const string TREE_SIZE[] = {"Seedling", "Sapling", "Pole", "Mature"}; //age 0-3 = seedling
const int SEASONS_TO_FRUIT = 12; //Roughly 4 years to produce fruit (when age = 12, fruit)
const int SEASONS_TO_SIZE = 4; //Roughly every 4 seasons they move to next size (up to mature)
const int SEASONS_TO_HARVEST = 60; //Roughly every 15 years cut down (when age = 60)

class Tree: public AgItem {
public:
  // Name: Tree (Default constructor)
  // Desc: Creates a tree with size 0 and age of 0
  // Preconditions:  Uses AgItem default constructor
  // Postconditions: A tree is created.
  Tree();

  // Name: ~Tree
  // Desc: Destructor for tree (and importantly fruit)
  // Preconditions:  Tree exists
  // Postconditions: All fruit is purged from tree.
  ~Tree();

  // Name: Tick
  // Desc: A season passes is the tree's life (always fed)
  // Preconditions: Tree exists. Food passed but not used for tree (only animal)
  // Postconditions: Returns amount of fruit harvested each season.
  // One of the following occurs:
  //    1. Tree is not Mature yet and ages. Every 4 seasons, size increases til age 12 when fruits
  //    2. Tree is Mature and grows a one fruit a season. Fruit is harvested every season.
  //    3. Tree is 60 seasons old and is cut down (IsHarvesteable)
  virtual void Tick(int &food);

  // Name: Harvest
  // Desc: If there is fruit, removes last fruit and increments food by 1
  // Preconditions:  Tree exists and passed money and food (to update)
  // Postconditions: If fruiting, increases food by 1. After 60 seasons dies.
  virtual void Harvest(int &money, int &food);

  // Name: GetType
  // Desc: Returns the name of the subtype (Tree)
  // Preconditions:  None
  // Postconditions: Returns string name of the subtype (Tree)
  virtual string GetType();
  
  // Name: overloaded operator<<
  // Desc: Allows Tree objects to be outputted
  // Preconditions:  None
  // Postconditions: Returns output stream with this format:
  //                 Tree  | Seedling | Not Harvestable | Not Fruiting | Fruit Count: 0
  virtual ostream& operator<<(ostream&);

private:
  vector <Fruit*> m_fruit; //Hold fruit objects
  int m_age; //Trees are not harvested when they are mature - they make fruit
};

#endif 
