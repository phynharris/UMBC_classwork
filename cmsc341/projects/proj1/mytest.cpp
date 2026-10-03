#include "fuel.h"

class Tester{
public:
  bool testAddTankNorm(FuelSys &sys); // Adds multiple tanks
  bool testAddTankErr1(FuelSys &sys); // Tests for invalid tank ID
  bool testAddTankErr2(FuelSys &sys); // Tests for invalid tank capacity
  bool testAddTankErr3(FuelSys &sys); // Tests for invalid fuel amount
  bool testAddTankErr4(FuelSys &sys); // Tests for duplcate ID
  bool testAddTankErr5(FuelSys &sys); // Tests for fuel/capacity discrepancy

  bool testRemoveTankNorm(FuelSys &sys); // Tests all added tanks are properly removed
  bool testRemoveTankErr1(FuelSys &sys); // Tests for invalid tank ID
  bool testRemoveTankErr2(FuelSys &sys); // Tests for extant tank system

  bool testFindTankNorm1(FuelSys &sys); // Verifies lone tank can be found
  bool testFindTankNorm2(FuelSys &sys); // Verifies a tank can be found among numerous others
  bool testFindTankErr1(FuelSys &sys);  // Verifies a non-extant tank cannot be found
  bool testFindTankErr2(FuelSys &sys);  // Verifies a removed tank cannot be found

  bool testTotalFuelNorm(FuelSys &sys); // Tests that the fuel in all tanks is added up properly
  bool testTotalFuelErr1(FuelSys &sys); // Tests that an empty tank system has 0 fuel

  bool testAddPumpNorm(FuelSys &sys); // Tests that multiple pumps may be added in a system populated with multiple tanks
  bool testAddPumpErr1(FuelSys &sys); // Tests for extant tank system
  bool testAddPumpErr2(FuelSys &sys); // Tests for invalid tank ID
  bool testAddPumpErr3(FuelSys &sys); // Tests for invalid target ID
  bool testAddPumpErr4(FuelSys &sys); // Tests for invalid pump ID
  bool testAddPumpErr5(FuelSys &sys); // Test for duplicate pump ID

  bool testRemovePumpNorm(FuelSys &sys); // Verifies that 
  bool testRemovePumpErr1(FuelSys &sys); // Bad system
  bool testRemovePumpErr2(FuelSys &sys); // Bad tank
  bool testRemovePumpErr3(FuelSys &sys); // Bad target
  bool testRemovePumpErr4(FuelSys &sys); // Bad pump

  bool testDrainNorm(FuelSys &sys); // Tests whether a tank has drained fuel into another
  bool testDrainEdge(FuelSys &sys); // Tests whether a the accepting tank has less empty space than fuel
  bool testDrainErr1(FuelSys &sys); // Tests for invalid fuel
  bool testDrainErr2(FuelSys &sys); // Tests for empty tank system
  bool testDrainErr3(FuelSys &sys); // Tests for invalid tank ID
  bool testDrainErr4(FuelSys &sys); // Tests for invalid pump ID
  bool testDrainErr5(FuelSys &sys); // Tests for empty pump system
  bool testDrainErr6(FuelSys &sys); // Tests for full target tank
  bool testDrainErr7(FuelSys &sys); // Tests for invalid source fuel

  bool testOvldAssignNorm(FuelSys &sys); // Tests that the overloaded assignment operator functions
  bool testOvldAssignEdge(FuelSys &sys); // Tests that a null system matches
  
private:
  
};

int main(){

  Tester tester;

  // Test cases for addTank
  {
    FuelSys sys;
    cout << "\nTesting normal case for addTank function:\n";
    if(tester.testAddTankNorm(sys) == true){
      cout << "\tNormal case of addTank function passed!\n";
    }else{
      cout << "\tNormal case of addTank function failed!\n";
    }
  }

  {
    FuelSys sys;
    cout << "\nTesting error case 1 for addTank function:\n";
    if(tester.testAddTankErr1(sys) == true){
      cout << "\tError case 1 of addTank function passed!\n";
    }else{
      cout << "\tError case 1 of addTank function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 2 for addTank function:\n";
    if(tester.testAddTankErr2(sys) == true){
      cout << "\tError case 2 of addTank function passed!\n";
    }else{
      cout << "\tError case 2 of addTank function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 3 for addTank function:\n";
    if(tester.testAddTankErr3(sys) == true){
      cout << "\tError case 3 of addTank function passed!\n";
    }else{
      cout << "\tError case 3 of addTank function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 4 for addTank function:\n";
    if(tester.testAddTankErr4(sys) == true){
      cout << "\tError case 4 of addTank function passed!\n";
    }else{
      cout << "\tError case 4 of addTank function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 5 for addTank function:\n";
    if(tester.testAddTankErr5(sys) == true){
      cout << "\tError case 5 of addTank function passed!\n";
    }else{
      cout << "\tError case 5 of addTank function faild!\n";
    }
  }

  // Test cases for removedTank
  {
    FuelSys sys;
    cout << "\nTesting normal case for removeTank function:\n";
    if(tester.testRemoveTankNorm(sys) == true){
      cout << "\tNormal case of removeTank function passed!\n";
    }else{
      cout << "\tNormal case of removeTank function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 1 for removeTank function:\n";
    if(tester.testRemoveTankErr1(sys) == true){
      cout << "\tError case 1 of removeTank function passed!\n";
    }else{
      cout << "\tError case 1 of removeTank function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 2 for removeTank function:\n";
    if(tester.testRemoveTankErr2(sys) == true){
      cout << "\tError case 2 of removeTank function passed!\n";
    }else{
      cout << "\tError case 2 of removeTank function failed!\n";
    }
  }

  // Test cases for findTank
  {
    FuelSys sys;
    cout << "\nTesting normal case 1 for findTank function:\n";
    if(tester.testFindTankNorm1(sys) == true){
      cout << "\tNormal case 1 of findTank function passed!\n";
    }else{
      cout << "\tNormal case 1 of findTank function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting normal case 2 for findTank function:\n";
    if(tester.testFindTankNorm2(sys) == true){
      cout << "\tNormal case 2 of findTank function passed!\n";
    }else{
      cout << "\tNormal case 2 of findTank function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 1 for findTank function:\n";
    if(tester.testFindTankErr1(sys) == true){
      cout << "\tError case 1 of findTank function passed!\n";
    }else{
      cout << "\tError case 1 of findTank function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 2 for findTank function:\n";
    if(tester.testFindTankErr2(sys) == true){
      cout << "\tError case 2 of findTank function passed!\n";
    }else{
      cout << "\tError case 2 of findTank function failed!\n";
    }
  }

  // Test cases for totalFuel function
  {
    FuelSys sys;
    cout << "\nTesting normal case for totalFuel function:\n";
    if(tester.testTotalFuelNorm(sys) == true){
      cout << "\tNormal case of totalFuel function passed!\n";
    }else{
      cout << "\tNormal case oftotalFuel function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case for totalFuel function:\n";
    if(tester.testTotalFuelErr1(sys) == true){
      cout << "\tError case of totalFuel function passed!\n";
    }else{
      cout << "\tError case of totalFuel function failed!\n";
    }
  }

  // Test cases for addPump function
  {
    FuelSys sys;
    cout << "\nTesting normal case for addPump function:\n";
    if(tester.testAddPumpNorm(sys) == true){
      cout << "\tNormal case of addPump function passed!\n";
    }else{
      cout << "\tNormal case of addPump function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 1 for addPump function:\n";
    if(tester.testAddPumpErr1(sys) == true){
      cout << "\tError case 1 of addPump function passed!\n";
    }else{
      cout << "\tError case 1 of addPump function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 2 for addPump function:\n";
    if(tester.testAddPumpErr2(sys) == true){
      cout << "\tError case 2 of addPump function passed!\n";
    }else{
      cout << "\tError case 2 of addPump function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 3 for addPump function:\n";
    if(tester.testAddPumpErr3(sys) == true){
      cout << "\tError case 3 of addPump function passed!\n";
    }else{
      cout << "\tError case 3 of addPump function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 4 for addPump function:\n";
    if(tester.testAddPumpErr4(sys) == true){
      cout << "\tError case 4 of addPump function passed!\n";
    }else{
      cout << "\tError case 4 of addPump function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 5 for addPump function:\n";
    if(tester.testAddPumpErr5(sys) == true){
      cout << "\tError case 5 of addPump function passed!\n";
    }else{
      cout << "\tError case 5 of addPump function failed!\n";
    }
  }

  // Test cases for removePump function
  {
    FuelSys sys;
    cout << "\nTesting normal case for removePump function:\n";
    if(tester.testRemovePumpNorm(sys) == true){
      cout << "\tNormal case of removePump function passed!\n";
    }else{
      cout << "\tNormal case of removePump function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 1 for removePump function:\n";
    if(tester.testRemovePumpErr1(sys) == true){
      cout << "\tError case 1 of removePump function passed!\n";
    }else{
      cout << "\tError case 1 of removePump function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 2 for removePump function:\n";
    if(tester.testRemovePumpErr2(sys) == true){
      cout << "\tError case 2 of removePump function passed!\n";
    }else{
      cout << "\tError case 2 of removePump function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 3 for removePump function:\n";
    if(tester.testRemovePumpErr3(sys) == true){
      cout << "\tError case 3 of removePump function passed!\n";
    }else{
      cout << "\tError case 3 of removePump function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 4 for removePump function:\n";
    if(tester.testRemovePumpErr4(sys) == true){
      cout << "\tError case 4 of removePump function passed!\n";
    }else{
      cout << "\tError case 4 of removePump function failed!\n";
    }
  }

  // Test cases for drain function
  {
    FuelSys sys;
    cout << "\nTesting normal case for drain function:\n";
    if(tester.testDrainNorm(sys) == true){
      cout << "\tNormal case of drain function passed!\n";
    }else{
      cout << "\tNormal case of drain function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting edge case for drain function:\n";
    if(tester.testDrainEdge(sys) == true){
      cout << "\tEdge case of drain function passed!\n";
    }else{
      cout << "\tEdge case of drain function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 1 for drain function:\n";
    if(tester.testDrainErr1(sys) == true){
      cout << "\tError case 1 of drain function passed!\n";
    }else{
      cout << "\tError case 1 of drain function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 2 for drain function:\n";
    if(tester.testDrainErr2(sys) == true){
      cout << "\tError case 2 of drain function passed!\n";
    }else{
      cout << "\tError case 2 of drain function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 3 for drain function:\n";
    if(tester.testDrainErr3(sys) == true){
      cout << "\tError case 3 of drain function passed!\n";
    }else{
      cout << "\tError case 3 of drain function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 4 for drain function:\n";
    if(tester.testDrainErr4(sys) == true){
      cout << "\tError case 4 of drain function passed!\n";
    }else{
      cout << "\tError case 4 of drain function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 5 for drain function:\n";
    if(tester.testDrainErr5(sys) == true){
      cout << "\tError case 5 of drain function passed!\n";
    }else{
      cout << "\tError case 5 of drain function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 6 for drain function:\n";
    if(tester.testDrainErr6(sys) == true){
      cout << "\tError case 6 of drain function passed!\n";
    }else{
      cout << "\tError case 6 of drain function failed!\n";
    }
  }
  {
    FuelSys sys;
    cout << "\nTesting error case 7 for drain function:\n";
    if(tester.testDrainErr7(sys) == true){
      cout << "\tError case 7 of drain function passed!\n";
    }else{
      cout << "\tError case 7 of drain function failed!\n";
    }
  }

  {
    FuelSys sys;
    cout << "\nTesting normal case for the overloaded assignment operator:\n";
    if(tester.testOvldAssignNorm(sys) == true){
      cout << "\tNormal case of the overloaded assignment operator function passed!\n";
    }else{
      cout << "\tNormal case of the overloaded assignment operator function failed!\n";
    }
  }

  {
    FuelSys sys;
    cout << "\nTesting edge case for the overloaded assignment operator:\n";
    if(tester.testOvldAssignEdge(sys) == true){
      cout << "\tEdge case of the overloaded assignment operator function passed!\n";
    }else{
      cout << "\tEdge case of the overloaded assignment operator function failed!\n";
    }
  }
  
  return 0;
}

// Test function that verifies whether a set of tanks are added to the system
bool Tester::testAddTankNorm(FuelSys &sys){
  for(int i = 1; i < 4; i++){
    if(sys.addTank(i,i,i) == false){
      cout << "A tank was not added.\n";
      return false;
    }
  }

  // Verifies m_current is the most recent node
  if(sys.m_current->m_tankID != 3){
    cout << "\tCurrent tank is inconsistent\n";
    return false;
  }

  // Verifies each node is present
  for(int i = 1; i < 4; i++){
    sys.findTank(i);
    if(sys.m_current->m_tankID != i){
      cout << "\tThere is a tank discrepancy\n";
      return false;
    }
  }
  
  return true;
}

// Test function that verifies a tank with an invalid ID is not added
bool Tester::testAddTankErr1(FuelSys &sys){
  if(sys.addTank(-1, 10, 0) == true){
    cout << "Tank with invalid ID added\n";
    return false;
  }

  // Verifies the system is empty
  if(sys.m_current != nullptr){
    cout << "\nSystem is not empty\n";
    return false;
  }
  
  return true;
}

// Test function that verifies a tank with an invalid capacity is not added
bool Tester::testAddTankErr2(FuelSys &sys){
  if(sys.addTank(0,-1,0) == true){
    cout << "Tank with invalid capacity added\n";
    return false;
  }

  // Verifies the system is empty
  if(sys.m_current != nullptr){
    cout << "\nSystem is not empty\n";
    return false;
  }
  
  return true;
  
}

// Test function that verifies a tank with invalid fuel is not added
bool Tester::testAddTankErr3(FuelSys &sys){
  if(sys.addTank(0,10,-1) == true){
    cout << "Tank with invalid fuel added\n";
    return false;
  }

  // Verifies the system is empty
  if(sys.m_current != nullptr){
    cout << "\nSystem is not empty\n";
    return false;
  }
 
  return true;
}

// Test function that verifies a tank with a duplicate ID is not added
bool Tester::testAddTankErr4(FuelSys &sys){
  sys.addTank(1,20,2);
  if(sys.addTank(1,19,17) == true){
    cout << "Tank with duplicated ID added\n" << endl;
    return false;
  }

  // Verifies the tank ID matches
  if(sys.m_current->m_tankID != 1){
    cout << "\tInconsistent tank ID\n";
    return false;
  }
    
  return true; 
}

// Test function that verifies a tank with more fuel than its capacity is not added
bool Tester::testAddTankErr5(FuelSys &sys){
  if(sys.addTank(3,5,77) == true){
    cout << "Tank with more fuel than capacity added\n";
    return false;
  }

  if(sys.m_current != nullptr){
    cout << "\nSystem is not empty\n";
    return false;
  }
   
  return true;
}

// Test function that verifies that numerous tanks added are removed properly
bool Tester::testRemoveTankNorm(FuelSys &sys){
  for(int i = 0; i < 7; i++){
    sys.addTank(i,i+1,i);
  }
  for(int i = 6; i >= 0; i--){
    if(sys.removeTank(i) == false){
      cout << "\tA tank was not removed\n";
      return false;
    }
  }

  // Verifies system is empty
  if(sys.m_current != nullptr){
    cout << "\tTanks not properly removed\n";
    return false;
  }
  
  return true;
}

// Test function that verifies a tank that doesn't exist isn't removed
bool Tester::testRemoveTankErr1(FuelSys &sys){
  sys.addTank(3,3,3);

  if(sys.removeTank(1) == true){
    cout << "\tNon-existent tank was removed\n";
    return false;
  }
  
  return true;
}

// Tets function that verifies a tank cannot be removed from an empty system
bool Tester::testRemoveTankErr2(FuelSys &sys){
  if(sys.removeTank(1) == true){
    cout << "\tNon-existent tank was removed from an empty system\n";
    return false;
  }
  
  return true;
}

// Test function that verifies an extant tank can be found
bool Tester::testFindTankNorm1(FuelSys &sys){
  sys.addTank(10,10,10);
  if(sys.findTank(10) == false){
    cout << "\tExtant tank not found\n";
    return false;
  }

  // Verifies that m_current is consistent
  if(sys.m_current->m_tankID != 10){
    cout << "\tCurrent tank is inconsistent\n";
    return false;
  }

  return true;  
}

// Test function that verifies an extant tank can be found among many
bool Tester::testFindTankNorm2(FuelSys &sys){
  for(int i = 0; i < 17; i++){
    sys.addTank(i,(i+1)*77,0);
  }

  if(sys.findTank(15) == false){
    cout << "\tExtant tank not found among many\n";
    return false;
  }

  if(sys.m_current->m_tankID != 15){
    cout << "\tCurrent tank is inconsistent\n";
    return false;
  }
  
  return true;
}

// Test function that verifies a non-extant tank is not found
bool Tester::testFindTankErr1(FuelSys &sys){
  if(sys.findTank(77) == true){
    cout << "\tNon-Extant tank was found\n";
    return false;
  }
  
  return true;
}

// Test function that verifies a removed tank can no longer be found
bool Tester::testFindTankErr2(FuelSys &sys){
  sys.addTank(77,45,5);
  sys.addTank(100,10,1);
  sys.removeTank(77);
  if(sys.findTank(77) == true){
    cout << "\tRemoved tank was found\n";   
    return false;
  }
  
  return true;
}

// Test function that verifies fuel in tanks are properly summed
bool Tester::testTotalFuelNorm(FuelSys &sys){
  sys.addTank(0,20000,4);
  sys.addTank(100,20000,17);
  sys.addTank(2,20000,6);
  sys.addTank(5,20000,50);
  if(sys.totalFuel() != 77){
    cout << "\tFuel total is inconsistent\n";
    return false;
  }
  
  return true;
}

// Test function that verifies a system of 0 tanks has 0 fuel
bool Tester::testTotalFuelErr1(FuelSys &sys){
  if(sys.totalFuel() != 0){
    cout << "\tFuel total is not 0\n";
    return false;
  }
  
  return true;
}

// Test function that verifies whether numerous pumps are added to a system of tanks
bool Tester::testAddPumpNorm(FuelSys &sys){
  sys.addTank(0,100,10);
  sys.addTank(1,100,1);
  sys.addTank(2,100,5);
  for(int i = 0; i < 6; i++){
    if(sys.addPump(i%3,i,(i+1)%3) == false){
      cout << "\tPump not added\n";
	return false;
    }
  }
  
  return true;
}

// Test function that verifies whether a pump is added to an empty tank system
bool Tester::testAddPumpErr1(FuelSys &sys){
  if(sys.addPump(0,0,0) == true){
    cout << "\tPump added to empty system\n";
    return false;
  }
  
  return true;
}

// Test function that verfies a tank that does not exist cannot get a pump
bool Tester::testAddPumpErr2(FuelSys &sys){
  sys.addTank(0,20,2);
  sys.addTank(1,2,0);
  if(sys.addPump(2,0,0) == true){
    cout << "\tPump added to non-extant tank\n";
    return false;
  }
  
  return true;
}

// Test function that verifies a pump cannot be given a non-extant target
bool Tester::testAddPumpErr3(FuelSys &sys){
  sys.addTank(0,20,2);
  if(sys.addPump(0,0,1) == true){
    cout << "\tPump target set to non-extant tank\n";
    return false;
  }
    
  return true;
}

// Test function that verfies a pump with an invalid Id cannot be created
bool Tester::testAddPumpErr4(FuelSys &sys){
  sys.addTank(0,1,0);
  if(sys.addPump(0,-1,0) == true){
    cout << "\tPump created with invalid ID\n";
    return false;
  }
  
  return true;
}

// Test function that verifies a pump with a duplicate ID cannot be created
bool Tester::testAddPumpErr5(FuelSys &sys){
  sys.addTank(0,10,1);
  sys.addPump(0,0,0);
  if(sys.addPump(0,0,0) == true){
    cout << "\tDuplicate pump added to same tank\n";
    return false;
  }

  return true;
}

// Test function that verifies whether multiple pumps can be removed from a system
bool Tester::testRemovePumpNorm(FuelSys &sys){
  sys.addTank(0,100,10);
  sys.addTank(1,100,10);
  sys.addTank(2,100,10);
  sys.addPump(0,0,1);
  sys.addPump(0,1,2);
  sys.addPump(1,2,0);
  sys.addPump(1,3,2);
  sys.addPump(1,4,0);
  sys.addPump(2,5,1);

  // Checks that each pump is removed
  if(sys.removePump(0,0) == false){
    cout << "\tPump in beginning not removed\n";
    return false;
  }else if(sys.removePump(1,3) == false){
    cout << "\tPump in center not removed\n";
    return false;
  }else if(sys.removePump(2,5) == false){
    cout << "\tLone pump not removed\n";
    return false;
  }
  
  return true;
}

// Test function that verifies a pump cannot be removed from a system without tanks
bool Tester::testRemovePumpErr1(FuelSys &sys){
  if(sys.removePump(0,0) == true){
    cout << "\tPump removed from tankless system\n";
    return false;
  }

  return true;
}

// Test function that verifies a pump cannot be removed from a non-extant tank
bool Tester::testRemovePumpErr2(FuelSys &sys){
  sys.addTank(0,20,0);
  sys.addPump(0,0,0);
  if(sys.removePump(1,0) == true){
    cout << "\tPump removed from non-extant tank\n";
    return false;
  }

  return true;
}

// Test function that verifies a pump cannot be removed from a pumpless tank
bool Tester::testRemovePumpErr3(FuelSys &sys){
  sys.addTank(0,1,0);
  if(sys.removePump(0,1) == true){
    cout << "\tPump removed from pumpless system\n";
    return false;
  }

  return true;
}

// Test function that verifies a non-extant pump cannot be removed
bool Tester::testRemovePumpErr4(FuelSys &sys){
  sys.addTank(0,1,0);
  sys.addPump(0,0,0);
  if(sys.removePump(0,1) == true){
    cout << "\tNon-Extant pump removed\n";
    return false;
  }

  return true;
}

// Test function that verifies a tank has appropriately drained into another
bool Tester::testDrainNorm(FuelSys &sys){
  sys.addTank(0,100,50);
  sys.addTank(1,100000,0);
  sys.addPump(0,0,1);
  if(sys.drain(0,0,50) == false){
    cout << "\tTransfer did not occur\n";
    return false;
  }

  // Verifies that the source tank is drained
  sys.findTank(0);
  if(sys.m_current->m_tankFuel != 0){
    cout << "\tSource tank not emptied\n";
    cout << "\tExpected (Source): 0. Actual: " << sys.m_current->m_tankFuel << endl;
    return false;
  }

  // Verifies that the target tank is filled
  sys.findTank(1);
  if(sys.m_current->m_tankFuel != 50){
    cout << "\tTarget tank not filled\n";
    cout << "\tExpected (Target): 50. Actual: " << sys.m_current->m_tankFuel << endl;
    return false;
  }

  return true;
}

// Test function that verifies fuel is appropriately added to a tank with less space than fuel
bool Tester::testDrainEdge(FuelSys &sys){
  sys.addTank(0,100,50);
  sys.addTank(1,100,50);
  sys.addPump(0,0,1);
  if(sys.drain(0,0,80) == false){
    cout << "\tTransfer did not occur\n";
    return false;
  }

  // Verifies that the source tank is empty
  sys.findTank(0);
  if(sys.m_current->m_tankFuel != 0){
    cout << "\tSource tank not emptied\n";
    cout << "\tExpected (Source): 49. Actual: " << sys.m_current->m_tankFuel << endl; 
    return false;
  }

  // Verifies that the source tank is full
  sys.findTank(1);
  if(sys.m_current->m_tankFuel != 100){
    cout << "\tTarget tank not filled\n";
    cout << "\tExpected (Target): 100. Actual: " << sys.m_current->m_tankFuel << endl;
    return false;
  }

  return true;
}

// Test function that verifies fuel is valid
bool Tester::testDrainErr1(FuelSys &sys){
  sys.addTank(0,10,1);
  sys.addTank(1,10,1);
  sys.addPump(0,0,1);
  if (sys.drain(0,1,-10) == true){
    cout << "\tInvalid fuel drained from tank\n";
    return false;
  }

  return true;
}

// Test function that verifies fuel cannot be drained in an empty tank system
bool Tester::testDrainErr2(FuelSys &sys){
  if(sys.drain(0,0,10) == true){
    cout << "\tFuel drained from empty tank system\n";
    return false;
  }

  return true;
}

// Test function that verifies fuel cannot be drained from a non-extant tank
bool Tester::testDrainErr3(FuelSys &sys){
  sys.addTank(0,10,1);
  sys.addTank(1,10,1);
  sys.addPump(0,0,1);
  if(sys.drain(2,0,1) == true){
    cout << "\tFuel drained from non-extant tank\n";
    return false;
  }

  return true;
}

// Test function that verifies fuel cannot be drained from a non-extant pump
bool Tester::testDrainErr4(FuelSys &sys){
  sys.addTank(0,10,1);
  sys.addTank(1,10,1);
  sys.addPump(0,0,1);
  if(sys.drain(1,0,1) == true){
    cout << "\tFuel drained from non-extant pump\n";
    return false;
  }

  return true;
}

// Test function that verifies fuel cannot be drained from a pumpless system
bool Tester::testDrainErr5(FuelSys &sys){
  sys.addTank(0,10,1);
  sys.addTank(1,10,1);
  if(sys.drain(0,0,1) == true){
    cout << "\tFuel drained from non-extant pump system\n";
    return false;
  }

  return true;
}

// Test function that verifies fuel cannot be drained into a full tank
bool Tester::testDrainErr6(FuelSys &sys){
  sys.addTank(0,10,1);
  sys.addTank(1,10,10);
  sys.addPump(0,0,1);
  if(sys.drain(0,0,1) == true){
    cout << "\tFuel drained into full tank\n";
    return false;
  }

  return true;
}

// Test function that verifies fuel cannot be drained from an empty source
bool Tester::testDrainErr7(FuelSys &sys){
  sys.addTank(0,10,0);
  sys.addTank(1,10,1);
  sys.addPump(0,0,1);
  if(sys.drain(0,0,1) == true){
    cout << "\tFuel drained from empty tank\n";
    return false;
  }

  return true;
}

bool Tester::testOvldAssignNorm(FuelSys &sys){
  int tankIDs[] = {0,1,2};
  int tankCaps[] = {100,200,10};
  int tankFuels[] = {10,0,10};

  for(int i = 0; i < 3; i++){
    sys.addTank(tankIDs[i],tankCaps[i],tankFuels[i]);
  }
  
  sys.addPump(0,0,1);
  sys.addPump(1,1,1);
  sys.addPump(1,2,2);

  FuelSys newSys;
  newSys = sys;

  for(int i = 0; i < 3; i++){
    sys.findTank(i);
    newSys.findTank(i);

    // Verifies they have separate tank systems
    if(sys.m_current == newSys.m_current){
      cout << "\tSystems point to same m_current\n";
      return false;
    }

    // Verifies their next pointers are not shared
    if(sys.m_current->m_next == newSys.m_current->m_next){
      cout << "\tSystems point to same m_current->m_next\n";
      return false;
    }

    // Verifies that their pumps are not shared
    if((sys.m_current->m_pumps == newSys.m_current->m_pumps) &&
       (sys.m_current->m_pumps != nullptr && newSys.m_current->m_pumps != nullptr)){
      cout << "\tSystems contain the same m_pumps\n";
      return false;
    }

    // Verifies that their values match
    if(sys.m_current->m_tankID != newSys.m_current->m_tankID ||
       sys.m_current->m_tankCapacity != newSys.m_current->m_tankCapacity ||
       sys.m_current->m_tankFuel != newSys.m_current->m_tankFuel){
      cout << "\tValues have not properly been copied\n";
      return false;
    }
  }
  
  return true;
}

// Test function that verifies a null system is copied by the overloaded assignment operator
bool Tester::testOvldAssignEdge(FuelSys &sys){
  int tankIDs[] = {0,1,2};
  int tankCaps[] = {100,200,10};
  int tankFuels[] = {10,0,10};

  for(int i = 0; i < 3; i++){
    sys.addTank(tankIDs[i],tankCaps[i],tankFuels[i]);
  }

  sys.addPump(0,0,1);
  sys.addPump(1,1,1);
  sys.addPump(1,2,2);
  sys.addPump(2,3,0);
  FuelSys newSys;
  
  sys = newSys;

  if(sys.m_current != nullptr){
    cout << "\tSystem was not nullified\n";
    return false;
  }
  
  return true;
}
