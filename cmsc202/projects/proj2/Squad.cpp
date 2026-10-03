/*****************************************
 ** File: Squad.cpp
 ** Project: CMSC 202 Project 2, Fall 2025
 ** Author: Jaylen Jenkins
 ** Date: 10/9/2025
 ** Section: 20/22
 ** E-mail: fp31977@gl.umbc.edu
 **
 ** This file contains the cpp file for the Squad class
 ** It creats a squad that can fit up to a set No. of units.
 ** The name of a squad can be set here, members can be added to it, and the first of its members can be obtained.
 ** This program can also check if a squad is defeated (all of its members are dead) and print the current status of a squad.
 ** 
 ***********************************************/
#include "Squad.h"

const int MAX_PLAYERS = 2;
const int MAX_ENEMIES = 2;

// Squad::Squad
// Given nothing — Returns nothing.
Squad::Squad(){
  m_squadName = "Unnamed";
}

// Squad::Squad
// Given the name of a squad — Returns nothing
Squad::Squad(string name){
  SetName(name);
}

// Squad::SetName
// Given the name of a squad — Returns nothing
void Squad::SetName(string name){
  // If a squad is given an invalid name, then its name is defaulted
  // Otherwise, m_squadName is set to the entered name.
  if(name == ""){
    m_squadName = "Unnamed";
    cout << "Err — Invalid Squad Name." << endl;
  }else{
    m_squadName = name;
  }

  m_count = 0;
}

// Squad::GetName
// Given nothing — Returns the name of a squad
string Squad::GetName(){

  return m_squadName;
}

// Squad::AddMember
// Given a unit — Returns false if a squad is full, else true
bool Squad::AddMember(Unit unit){
  // If the number of units is less than the maximum allowed players, then there is room for more units
  if(m_count < MAX_PLAYERS){
    m_members[m_count] = unit;
    m_count += 1;
    return true;
  }else{
    return false;
  }
}

// Squad::GetFirstAliveMember
// Given nothing — Returns either a pointer to a unit or a nullpointer
Unit* Squad::GetFirstAliveMember(){
  // Iterates through the m_members array and checks if each is alive in sequential order
  // It returns the first one that is alive
  for(int i = 0; i < MAX_PLAYERS; i++){
    if(m_members[i].IsAlive()){
      return &m_members[i];
    }
  }
  return nullptr;
}

// Squad::IsDefeated
// Given nothing — Returns true if a unit is defeated, else false
bool Squad::IsDefeated(){

  m_count = MAX_PLAYERS;

  // Iterates through the m_members array and checks if each unit is alive
  // If a unit is alive, then false is returned — otherwise true.
  for(int i = 0; i < MAX_PLAYERS; i++){
    if(!m_members[i].IsAlive()){
      m_count -= 1;
    }
  }

  if(m_count == 0){
    return true;
  }else{
    return false;
  }
}

// Squad::PrintStatus
// Given nothing — Returns nothing
void Squad::PrintStatus(){
  string squadName = GetName();
  cout << "--- " << squadName << " ---" << endl;

  for(int i = 0; i < MAX_PLAYERS; i++){
    int alive = m_members[i].IsAlive();
    int health = m_members[i].GetHealth();
    string unitName = m_members[i].GetName();

    // Prints a unit's name and HP
    // If they are not alive, then that is indicated by [X]
    if(alive){
      cout << unitName << " (" << health << ")" << endl;
    }else{
      health = 0;
      cout << unitName << " (" << health << ") [X]" << endl;
    }
  }
}
