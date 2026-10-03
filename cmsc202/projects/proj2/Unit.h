#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <iostream>
using namespace std;

class Unit {
 public:
  // Name - Unit()
  // Desc - Default constructor, initializes with placeholder values
  // Preconditions - None
  // Postconditions - Creates Unit with minimal health and attack
  Unit();
  // Name - Unit(string name, int hp, int atk)
  // Desc - Overloaded constructor, creates Unit with given stats
  // Preconditions - Valid parameters
  // Postconditions - Creates Unit with specified values
  Unit(string name, int hp, int atk);
  // Name - TakeDamage()
  // Desc - Reduces Unit's health by specified amount and updates alive status
  // Preconditions - Unit exists, amount is non-negative
  // Postconditions - Updates health and alive status
  void TakeDamage(int amount);
  // Name - Attack()
  // Desc - Attacks another Unit, dealing damage equal to this Unit's attack power
  // Preconditions - Both Units exist and are alive
  // Postconditions - Target Unit's health is reduced
  void Attack(Unit& target);
  // Name - GetName()
  // Desc - Returns Unit's name
  // Preconditions - Unit exists
  // Postconditions - Returns string name
  string GetName();
  // Name - GetHealth()
  // Desc - Returns Unit's current health
  // Preconditions - Unit exists
  // Postconditions - Returns integer health
  int GetHealth();
  // Name - IsAlive()
  // Desc - Returns whether Unit is still alive
  // Preconditions - Unit exists
  // Postconditions - Returns true if alive, false if dead
  bool IsAlive();
 private:
  string m_name;
  int m_health;
  int m_attackPower;
  bool m_alive;
};

#endif
