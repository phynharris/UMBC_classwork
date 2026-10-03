#ifndef SQUAD_H
#define SQUAD_H

#include "Unit.h"
#include <string>
#include <iostream>
using namespace std;

//Constants
const int MAX_MEMBERS = 4; //Used to define how large array is for units

class Squad {
 public:
  // Name - Squad()
  // Desc - Default constructor, initializes squad with "Unnamed"
  // Preconditions - None
  // Postconditions - Creates empty squad with default name
  Squad();
  // Name - Squad(string name)
  // Desc - Overloaded constructor, creates squad with given name
  // Preconditions - Name is a valid string
  // Postconditions - Creates empty squad with specified name
  Squad(string name);
  // Name - SetName()
  // Desc - Sets the name of the squad
  // Preconditions - None
  // Postconditions - Updates squad name
  void SetName(string name);
  // Name - GetName()
  // Desc - Returns the name of the squad
  // Preconditions - Squad exists
  // Postconditions - Returns squad name as string
  string GetName();
  // Name - AddMember()
  // Desc - Adds a Unit to the squad if there is space
  // Preconditions - Unit exists, squad not full
  // Postconditions - Adds Unit to squad, returns true if successful
  bool AddMember(Unit unit);
  // Name - GetFirstAliveMember()
  // Desc - Returns pointer to first alive Unit in squad
  // Preconditions - Squad has members
  // Postconditions - Returns Unit pointer or nullptr if none alive
  Unit* GetFirstAliveMember();
  // Name - IsDefeated()
  // Desc - Checks if all members of squad are defeated
  // Preconditions - Squad has members
  // Postconditions - Returns true if all members are dead, false otherwise
  bool IsDefeated();
  // Name - PrintStatus()
  // Desc - Displays squad name and current status of each member
  // Preconditions - Squad has members
  // Postconditions - Outputs squad info to console
  void PrintStatus();
 private:
  string m_squadName;
  Unit m_members[MAX_MEMBERS];
  int m_count;
};

#endif
