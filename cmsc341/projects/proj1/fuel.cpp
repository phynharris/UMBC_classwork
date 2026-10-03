// UMBC - CMSC 341 - Spring 2026 - Proj1
#include "fuel.h"

// FuelSys::FuelSys
// Given nothing — Returns nothing
FuelSys::FuelSys(){
  // Creates a fuel system with zero tanks
  m_current = nullptr;
}

// FuelSys::~FuelSys
// Given nothing — Returns nothing
FuelSys::~FuelSys(){
  clearLists();
}

// FuelSys::addTank
// Given a new tank's ID, its capacity, and its fuel
bool FuelSys::addTank(int tankID, int tankCap, int tankFuel = 0){
  // Tank IDs or fuel cannot be less than 0
  if(tankID < 0 || tankFuel < 0){
    return false;
  }

  // Tank capacities cannot be less than or equal to 0
  if(tankCap <= 0){
    return false;
  }

  // Tank capacity cannot be less than given fuel
  if(tankCap < tankFuel){
    return false;
  }

  // Tank ID must not already exist
  if(findTank(tankID) == true){
    return false;
  }

  // A new tank object is created
  Tank* tank = new Tank(tankID, tankCap, tankFuel, nullptr, nullptr);

  // If empty, add first tank to start of the list and connect it to itself
  if(m_current == nullptr){ 
    m_current = tank;
    tank->m_next = m_current;
    
  // Else, place new tank immediately after the current tank 
  }else{
    tank->m_next = m_current->m_next;
    m_current->m_next = tank;
    m_current = tank;
  }
  
  return true;
}

// FuelSys::removeTank
// Given a tank's ID — Returns nothing
bool FuelSys::removeTank(int tankID){
  // Desired tank must exist
  if(findTank(tankID) == false){
    return false;
  }

  // Creates temporary Tanks to traverse list until desired tank is found
  Tank* curr = m_current;
  Tank* prev = m_current;
  bool started = false;

  while(!(curr == m_current && started == true)){
    started = true;
    prev = curr;
    curr = curr->m_next;
  }

  if(curr->m_pumps != nullptr){
    Pump* prev_p = nullptr;
    Pump* curr_p = curr->m_pumps;

    // Cycles through and deletes each pump
    while(curr->m_pumps != nullptr){
      prev_p = curr_p;
      curr_p = curr_p->m_next;
      delete prev_p;
      prev_p = nullptr;  
    }
  }

  // Deletes the tank
  // Edge case for last tank in the list
  if(m_current->m_next == m_current){
    delete m_current;
    m_current = nullptr;
    
  // Edge case for the final 2 tanks 
  }else if(curr->m_next == prev){
    if(curr == m_current){
      m_current = m_current->m_next;
    }
    prev->m_next = prev;
    delete curr;
    curr = nullptr;
    
  // Deletes the current tank and reassigns pointer values
  }else{
    if(curr == m_current){
      m_current = m_current->m_next;
    }
    prev->m_next = curr->m_next;
    delete curr;
    curr = nullptr;
  }

  return true;
}

// FuelSys::findTank
// Given a tank's ID — Returns whether tank is found
bool FuelSys::findTank(int tankID){
  // If there are no tanks, return false
  if(m_current == nullptr){
    return false;
  }

  // Create a tank to cycle through the tanks until desired tank is found
  Tank* curr = m_current;
  bool started = false;

  while(!(curr == m_current && started == true)){
    started = true;
    
    // If the target tank is found, that becomes the new current tank
    if(curr->m_tankID == tankID){
      m_current = curr;
      return true;
    }
    curr = curr->m_next;
  }

  return false;
}

// FuelSys::addPump
// Given a tank's ID, the pumps ID, and the target of the pump — Returns whether a pump was added
bool FuelSys::addPump(int tankID, int pumpID, int targetTank){
  // If the either tank does not exist, return false
  if(findTank(tankID) == false || findTank(targetTank) == false){
    return false;
  }

  // If the pump ID is less than 0, return false
  if(pumpID < 0){
    return false;
  }

  // Creates a new pump with given values
  Pump* pump = new Pump(pumpID, targetTank, nullptr);

  findTank(tankID);

  // If such a pump with a matching ID exists, return false
  Pump* curr = m_current->m_pumps;
  while(curr != nullptr){
    if(curr->m_pumpID == pumpID){
      return false;
    }
    curr = curr->m_next;
  }

  // If there are no pumps, add the first one to the start of the list (this is the tail)
  if(m_current->m_pumps == nullptr){
    m_current->m_pumps = pump;
    pump->m_next = nullptr;

  // Subsequent pumps are added to the start of the list
  }else{
    findTank(tankID);
    pump->m_next = m_current->m_pumps;
    m_current->m_pumps = pump;
  }
  
  return true;
}

// FuelSys::removePump
// Given a tank's ID and the pump to be removed — Returns whether the pump was removed
bool FuelSys::removePump(int tankID, int pumpID){
  // If there are no tanks, pump not removed
  if(m_current == nullptr){
    return false;
  }

  // If tank does not exist, pump not removed
  if(findTank(tankID) ==  false){
    return false;
  }

  // If there are no pumps, pump not removed
  if(m_current->m_pumps == nullptr){
    return false;
  }

  // Traverse the pumps until desired pump found
  Pump* curr = m_current->m_pumps;
  Pump* prev = nullptr;

  while(curr->m_pumpID != pumpID){
    if(curr->m_next == nullptr){
      return false;
    }

    prev = curr;
    curr = curr->m_next;
  }

  // Edge case for when only 1 pump is in the system
  if(prev == nullptr){
    delete m_current->m_pumps;
    m_current->m_pumps = nullptr;

  // Edge case for last pump
  }else if(curr->m_next == nullptr){
    prev->m_next = nullptr;
    delete curr;
    curr = nullptr;
    m_current->m_pumps = prev;

  // Edge case if the pump being removed is the head of the list
  }else if(curr == m_current->m_pumps){
    m_current->m_pumps = m_current->m_pumps->m_next;
    delete curr;
    curr = nullptr;

  // Remove the desired pump and realign previous pointer
  }else{
    prev->m_next = curr->m_next;
    delete curr;
    curr = nullptr;
  }
  
  return true;
}

// FuelSys::totalFuel
// Given nothing — Returns amount of fuel
int FuelSys::totalFuel() const{
  // If there are no tanks, there is 0 fuel
  if(m_current == nullptr){
    return 0;
  }

  // Cycles through all tanks and totals the fuel in every tank
  int totalFuel = 0;
  Tank* curr_t = m_current;
  bool started = false;
  
  while(!(curr_t == m_current && started == true)){
    started = true;
    totalFuel += curr_t->m_tankFuel;
    curr_t = curr_t->m_next;
  }
  
  return totalFuel;
}

// FuelSys::drain
// Given a tank's ID, a pump's ID, and the amount of fuel to be drained — Returns wether pumps were drained
bool FuelSys::drain(int tankID, int pumpID, int fuel){
  // If ID's are invalid or fuel is less than or equal to 0, fuel not drained 
  if(fuel <= 0){
    return false;
  }

  // If there are no tanks, fuel not drained
  if(m_current == nullptr){
    return false;
  }

  // If tank not found, fuel not drained
  if(findTank(tankID) == false){
    return false;
  }

  // If there are no pumps, fuel not drained
  if(m_current->m_pumps == nullptr){
    return false;
  }

  // If the source tank is empty, do not drain it
  if(m_current->m_tankFuel <= 0){
    return false;
  }

  // Cycles through pumps until desired pump is found
  Tank* source = m_current;        // Where the fuel comes from
  Pump* curr = m_current->m_pumps;

  while(curr != nullptr && curr->m_pumpID != pumpID){
    curr = curr->m_next;
  }

  // Obtains the target tank from the pump
  findTank(curr->m_target);

  // If the target tank is full, fuel not added
  if(m_current->m_tankFuel == m_current->m_tankCapacity){
    return false;
  }

  // If amount the fuel is greater than the amount of fuel in the source, drain source fuel 
  if(fuel > source->m_tankFuel){
    fuel = source->m_tankFuel;
  }

  // If the amound of fuel is greater than the remaining capacity of the target, drain enough to fill target
  if(fuel + m_current->m_tankFuel >= m_current->m_tankCapacity){
    fuel = m_current->m_tankCapacity - m_current->m_tankFuel;
  }

  // Adds fuel to target, then drains from source
  fill(m_current->m_tankID, fuel);
  findTank(tankID);
  fill(source->m_tankID, -fuel);

  return true;
}

// FuelSys::fill
// Given a tank's ID and fuel to be added — Returns wether fuel was added
bool FuelSys::fill(int tankID, int fuel){
  // If there are no tanks, fuel not added
  if(m_current == nullptr){
    return false;
  }

  // If tank does not exist, fuel not added
  if(findTank(tankID) == false){
    return false;
  }

  m_current->m_tankFuel += fuel;
  
  return true;
}

// FuelSys::operator=
// Given system to be copied — Returns *this
const FuelSys & FuelSys::operator=(const FuelSys & rhs){
  // If the right hand side and the accepting system are the same, then return
  if(&rhs == this){
    return *this;
  }

  // If the system has tanks, clear them
  if(m_current != nullptr){
    clearLists();
  }

  // If the rhs has no tanks, the accepting system has no tanks
  if(rhs.m_current == nullptr){
    m_current = nullptr;
    return *this;
  }

  // Defaults values
  bool started = false;
  
  // Accepting Tank:
  m_current = nullptr;
  Tank* curr_t = m_current;
  Pump* curr_p = nullptr;

  int tankID = -1;
  int tankCap = -1;
  int tankFuel = -1;
  int pumpID = -1;
  int targetTank = -1;

  // rhs
  Tank* rhs_t = rhs.m_current;
  Pump* rhs_p = nullptr;

  // While-loop for copying tanks
  while(!(rhs.m_current == rhs_t && started == true)){
    started = true;

    // Obtains value for tank
    tankID = rhs_t->m_tankID;
    tankCap = rhs_t->m_tankCapacity;
    tankFuel = rhs_t->m_tankFuel;
    addTank(tankID, tankCap, tankFuel);
    
    curr_t = m_current;
    rhs_p = rhs_t->m_pumps;
    curr_p = curr_t->m_pumps;

    // Obtains pump values
    while(rhs_p != nullptr){
      pumpID = rhs_p->m_pumpID;
      targetTank = rhs_p->m_target;
      Pump* pump = new Pump(pumpID, targetTank, nullptr);

      // Add the first pump in the original to the head of the accepting tank
      if(m_current->m_pumps == nullptr){
	m_current->m_pumps = pump;
	curr_p = m_current->m_pumps;
      // Set each subsequent accepting pump to the subsequent pump of the original
      }else{
	curr_p->m_next = pump;
	curr_p = curr_p->m_next;
      }
      rhs_p = rhs_p->m_next;
    }
    rhs_t = rhs_t->m_next;
  }

  return *this;
}

void FuelSys::dumpSys() const{
  if (m_current != nullptr){
    Tank* tempTank = m_current->m_next;//we start at front item
    //we continue visting nodes until we reach the cursor
    while(m_current != nullptr && tempTank != m_current){
      cout << "Tank " << tempTank->m_tankID << "(" << tempTank->m_tankFuel << " kg)" << endl;
      // now dump the targets for all pumps in this tank
      // we need to traverse the list of pumps
      dumpPumps(tempTank->m_pumps);
      tempTank = tempTank->m_next;
    }
    //at the end we visit the cursor (current)
    //this also covers the case that there is only one item
    cout << "Tank " << m_current->m_tankID << "(" << m_current->m_tankFuel << " kg)" << endl;
    dumpPumps(tempTank->m_pumps);
    cout << "The current tank is " << m_current->m_tankID << endl;
  }
  else
    cout << "There is no tank in the system!\n\n";
}

void FuelSys::dumpPumps(Pump* pumps) const{
  // this traverses the linked list to the end
  Pump* tempPump = pumps;
  while (tempPump != nullptr){
    cout << " => pump " << tempPump->m_pumpID << "(To tank " << tempPump->m_target << ")" << endl;
    tempPump = tempPump->m_next;
  }
}

// Helper functions

// FuelSys::clearLists — Clears out every tank and pump
// Given nothing — Returns nothing
void FuelSys::clearLists(){
  // Create temp nodes to represent current and previous tanks and pumps
  bool started = false;
  Tank* curr_t = m_current;
  Tank* prev_t = m_current;
  Pump* curr_p = nullptr;
  Pump* prev_p = nullptr;

  // While the previous or first tank is not a nullptr, cycle through and delete remaining tanks
  while(!(started == true && curr_t == m_current) && m_current != nullptr){
    started = true;
    if(m_current != nullptr){
      curr_p = curr_t->m_pumps;
      prev_p = curr_p;
    }
    
    curr_t = curr_t->m_next;

    // While the previous or first pump is not a nullptr, cycle through and delete remaining pumps
    while(prev_p != nullptr){
      curr_p = curr_p->m_next;
      delete prev_p;
      prev_p = nullptr;
      prev_p = curr_p;
    }
    delete prev_t;
    prev_t = nullptr;
    prev_t = curr_t;
  }
}
