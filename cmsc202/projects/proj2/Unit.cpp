/*****************************************
 ** File: Unit.cpp
 ** Project: CMSC 202 Project 2, Fall 2025
 ** Author: Jaylen Jenkins
 ** Date: 10/9/2025
 ** Section: 20/22
 ** E-mail: fp31977@gl.umbc.edu
 **
 ** This file contains the cpp file for the Unit class.
 ** The unit class contains stats for a unit being a name, health, and attack power.
 ** It also contains various functions for the unit that allow them to attack another unit and take damage from other units.
 ** A unit's alive status can also be checked here.
 **
 ***********************************************/

#include "Unit.h"

// Unit::Unit
// Given nothing — Returns nothing
Unit::Unit(){
  m_name = "defaultName";
  m_health = 2;
  m_attackPower = 1;
  m_alive = true;
}

// Unit:Unit
// Given the name of a unit, their hp, and their attack — Returns nothing
Unit::Unit(string name, int hp, int atk){
  //If name invalid
  if(name == ""){
    m_name = "defaultName";
    cout << "Err — Unit name invalid — Setting default name." << endl;
  }else{
    m_name = name;
  }

  //If HP invalid
  if(hp <= 0){
    m_health = 2;
    cout << "Err — Health must be greater than 0 — Setting default HP." << endl;
  }else{
    m_health = hp;
    m_alive = true;
  }

  //If attack power invalid
  if(atk <= 0){
    m_attackPower = 1;
    cout << "Err — Attack Power must be greater than 0 — Setting default Attack Power." << endl;
  }else{
    m_attackPower = atk;
  }
}

// Unit::TakeDamage
// Given the amount of damage — Returns nothing
void Unit::TakeDamage(int amount){
  // If damage invalid
  if(amount < 0){
    cout << "Err — Damage cannot be a negative number.";
    return;
  }
  m_health -= amount;

  //If health drops below 0, unit is dead
  if(m_health <= 0){
    m_alive = false;
  }
}

// Unit::Attack
// Given the target of an attack — Returns nothing
void Unit::Attack(Unit& target){
  // If the target is still alive, attack that target
  if(target.IsAlive() == true){
    string targetName = target.GetName();

    // The variables below are used to determine how much damage a unit received
    int initHealth = target.GetHealth();
    int newHealth;
    int damage;

    // A unit takes damage, and the damage they took is displayed
    target.TakeDamage(m_attackPower);
    newHealth = target.GetHealth();
    damage = initHealth - newHealth;
    cout << m_name << " attacks " << targetName << " for " << damage << " damage." << endl;

    // If a unit has been killed, then that is displayed
    if(target.IsAlive() == false){
      cout << target.GetName() << " has been defeated." << endl;
    }
  }
}

// Unit::GetName
// Given nothing — Returns the name of a unit
string Unit::GetName(){
  return m_name;
}

// Unit::GetHealth
// Given nothing — Returns a unit's HP
int Unit::GetHealth(){
  return m_health;
}

// Unit::IsAlive
// Give nothing — Returns true if alive, else false.
bool Unit::IsAlive(){
  if(m_health > 0){
    return true;
  }else{
    return false;
  }
}
