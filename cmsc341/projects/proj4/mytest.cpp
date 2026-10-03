// CMSC 341 - Spring 2026 - Project 4
#include "vdetect.h"
#include <random>
#include <vector>
enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
  Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
  {
    if (type == NORMAL){
      //the case of NORMAL to generate integer numbers with normal distribution
      m_generator = std::mt19937(m_device());
      //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
      //the mean and standard deviation can change by passing new values to constructor
      m_normdist = std::normal_distribution<>(mean,stdev);
    }
    else if (type == UNIFORMINT) {
      //the case of UNIFORMINT to generate integer numbers
      // Using a fixed seed value generates always the same sequence
      // of pseudorandom numbers, e.g. reproducing scientific experiments
      // here it helps us with testing since the same sequence repeats
      m_generator = std::mt19937(10);// 10 is the fixed seed value
      m_unidist = std::uniform_int_distribution<>(min,max);
    }
    else{ //the case of UNIFORMREAL to generate real numbers
      m_generator = std::mt19937(10);// 10 is the fixed seed value
      m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
    }
  }
  void setSeed(int seedNum){
    // we have set a default value for seed in constructor
    // we can change the seed by calling this function after constructor call
    // this gives us more randomness
    m_generator = std::mt19937(seedNum);
  }

  int getRandNum(){
    // this function returns integer numbers
    // the object must have been initialized to generate integers
    int result = 0;
    if(m_type == NORMAL){
      //returns a random number in a set with normal distribution
      //we limit random numbers by the min and max values
      result = m_min - 1;
      while(result < m_min || result > m_max)
	result = m_normdist(m_generator);
    }
    else if (m_type == UNIFORMINT){
      //this will generate a random number between min and max values
      result = m_unidist(m_generator);
    }
    return result;
  }

  double getRealRandNum(){
    // this function returns real numbers
    // the object must have been initialized to generate real numbers
    double result = m_uniReal(m_generator);
    // a trick to return numbers only with two deciaml points
    // for example if result is 15.0378, function returns 15.03
    // to round up we can use ceil function instead of floor
    result = std::floor(result*100.0)/100.0;
    return result;
  }

private:
  int m_min;
  int m_max;
  RANDOM m_type;
  std::random_device m_device;
  std::mt19937 m_generator;
  std::normal_distribution<> m_normdist;//normal distribution
  std::uniform_int_distribution<> m_unidist;//integer uniform distribution
  std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};
class Tester{
public:
  bool testInsertNorm(VDetect &vdetect, int size);          // Test normal case for inserting nodes
  bool testInsertEdge(VDetect &vdetect);                    // Test edge case for inserting nodes by making half of them be colliding nodes
  bool testInsertErr1(VDetect &vdetect);                    // Test that duplicate nodes are not added
  bool testInsertErr2(VDetect &vdetect, int id);            // Test that a node with an invalid ID is not added
  bool testFindErr(VDetect &vdetect);                       // Test error case for find a node — node doesn't exist
  bool testFindNorm(VDetect &vdetect);                      // Test normal case for finding nodes — several non-colliding nodes
  bool testFindEdge(VDetect &vdetect);                      // Test edge case for finding nodes — several collided nodes
  bool testRemoveEdge(VDetect &vdetect, int size);          // Test edge case for removing nodes — few, no rehashing
  bool testRemoveNorm(VDetect &vdetect, int size);          // Test edge normal for removing nodes — few, collided
  bool testRehashInsert(VDetect &vdetect);                  // Test rehashing is performed after insertion
  bool testRehashCompLF(VDetect &vdetect);                  // Test that old, empty table is removed — Load Factor
  bool testRehashRem(VDetect &vdetect);                     // Test rehashing is performed after removal
  bool testRehashCompDR(VDetect &vdetect);                  // Test that old, empty table is removed — Deletion Ratio
private:
  // Helper Functions
  bool validDeleted(vector<Virus> currList, Virus notInserted, int size);                        // Ensure deleted elements have a copy
  int validInsert(Virus** table, Virus virus, prob_t probing, int hashVal, int size, int i);    // Ensure nodes are inserted in the right place
};

unsigned int hashCode(const string str);
string sequencer(int size, int seedNum);

int findNextPrime(int current);//ToRemove
int tempArray[101] = {0};//ToRemove, used to count number of collisions

int main(){
  Tester tester;

  // Test that nodes are inserted into a hash table via linear probing — zero rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, LINEAR);

    cout << "\nTesting normal case for inserting nodes in LINEAR hash table" << endl;
    if(tester.testInsertNorm(vdetect, 50)){
      cout << "\tNormal case for inserting nodes in LINEAR hash table passed!\n";
    }else{
      cout << "\tNormal case for inserting nodes in LINEAR hash table failed!\n";
    }
  }

  // Test that nodes are inserted into a hash table via quadratic probing — zero rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, QUADRATIC);

    cout << "\nTesting normal case for inserting nodes in QUADRATIC hash table" << endl;
    if(tester.testInsertNorm(vdetect, 50)){
      cout << "\tNormal case for inserting nodes in QUADRATIC hash table passed!\n";
    }else{
      cout << "\tNormal case for inserting nodes in QUADRATIC hash table failed!\n";
    }
  }

  // Test that nodes are inserted into a hash table via doublehash probing — zero rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    cout << "\nTesting normal case for inserting nodes in DOUBLEHASH hash table" << endl;
    if(tester.testInsertNorm(vdetect, 50)){
      cout << "\tNormal case for inserting nodes in DOUBLEHASH hash table passed!\n";
    }else{
      cout << "\tNormal case for inserting nodes in DOUBLEHASH hash table failed!\n";
    }
  }

  // Test that nodes are inserted into a hash table via linear probing — many nodes, one rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, LINEAR);

    cout << "\nTesting normal case for inserting many nodes in LINEAR hash table" << endl;
    if(tester.testInsertNorm(vdetect, 100)){
      cout << "\tNormal case for inserting many nodes in LINEAR hash table passed!\n";
    }else{
      cout << "\tNormal case for inserting many nodes in LINEAR hash table failed!\n";
    }
  }

  // Test that nodes are inserted into a hash table via quadratic probing — many nodes, one rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, QUADRATIC);

    cout << "\nTesting normal case for inserting many nodes in QUADRATIC hash table" << endl;
    if(tester.testInsertNorm(vdetect, 100)){
      cout << "\tNormal case for inserting many nodes in QUADRATIC hash table passed!\n";
    }else{
      cout << "\tNormal case for inserting many nodes in QUADRATIC hash table failed!\n";
    }
  }

  // Test that nodes are inserted into a hash table via doublehash probing — many nodes, one rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    cout << "\nTesting normal case for inserting many nodes in DOUBLEHASH hash table" << endl;
    if(tester.testInsertNorm(vdetect, 100)){
      cout << "\tNormal case for inserting many nodes in DOUBLEHASH hash table passed!\n";
    }else{
      cout << "\tNormal case for inserting many nodes in DOUBLEHASH hash table failed!\n";
    }
  }

  // Test that nodes are inserted into a hash table via linear probing — many nodes, multiple rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, LINEAR);

    cout << "\nTesting normal case for inserting many nodes in LINEAR hash table (multiple rehashing)" << endl;
    if(tester.testInsertNorm(vdetect, 500)){
      cout << "\tNormal case for inserting many nodes in LINEAR hash table (multiple rehashing) passed!\n";
    }else{
      cout << "\tNormal case for inserting many nodes in LINEAR hash table (multiple rehashing) failed!\n";
    }
  }

  // Test that nodes are inserted into a hash table via quadratic probing — many nodes, multiple rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, QUADRATIC);

    cout << "\nTesting normal case for inserting many nodes in QUADRATIC hash table (multiple rehashing)" << endl;
    if(tester.testInsertNorm(vdetect, 500)){
      cout << "\tNormal case for inserting many nodes in QUADRATIC hash table (multiple rehashing) passed!\n";
    }else{
      cout << "\tNormal case for inserting many nodes in QUADRATIC hash table (multiple rehashing) failed!\n";
    }
  }

  // Test that nodes are inserted into a hash table via doublehash probing — many nodes, two rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    cout << "\nTesting normal case for inserting many nodes in DOUBLEHASH hash table (2 rehashing)" << endl;
    if(tester.testInsertNorm(vdetect, 500)){
      cout << "\tNormal case for inserting many nodes in DOUBLEHASH hash table (2 rehashing) passed!\n";
    }else{
      cout << "\tNormal case for inserting many nodes in DOUBLEHASH hash table (2 rehashing) failed!\n";
    }
  }

  // Test that nodes with many collisions are added to the table — LINEAR
  {
    VDetect vdetect(MINPRIME, hashCode, LINEAR);

    cout << "\nTesting edge case for inserting nodes with numerous collisions in LINEAR hash table" << endl;
    if(tester.testInsertEdge(vdetect)){
      cout << "\tEdge case for inserting nodes in LINEAR hash table passed!\n";
    }else{
      cout << "\tEdge case for inserting nodes in LINEAR hash table failed!\n";
    }
  }

  // Test that nodes with many collisions are added to the table — QUADRATIC
  {
    VDetect vdetect(MINPRIME, hashCode, QUADRATIC);

    cout << "\nTesting edge case for inserting nodes with numerous collisions in QUADRATIC hash table" << endl;
    if(tester.testInsertEdge(vdetect)){
      cout << "\tEdge case for inserting nodes in QUADRATIC hash table passed!\n";
    }else{
      cout << "\tEdge case for inserting nodes in QUADRATIC hash table failed!\n";
    }
  }

  // Test that nodes with many collisions are added to the table — DOUBLEHASH
  {
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    cout << "\nTesting edge case for inserting nodes with numerous collisions in DOUBLEHASH hash table" << endl;
    if(tester.testInsertEdge(vdetect)){
      cout << "\tEdge case for inserting nodes in DOUBLEHASH hash table passed!\n";
    }else{
      cout << "\tEdge case for inserting nodes in DOUBLEHASH hash table failed!\n";
    }
  }

  // Test that duplicate nodes are not added to the table
  {
    VDetect vdetect(MINPRIME, hashCode, LINEAR);

    cout << "\nTesting error case for inserting nodes — no dupes" << endl;
    if(tester.testInsertErr1(vdetect)){
      cout << "\tError case for inserting nodes in hash table passed!\n";
    }else{
      cout << "\tError case for inserting nodes in hash table failed!\n";
    }
  }

  // Test that a node with a small ID is not added
  {
    VDetect vdetect(MINPRIME, hashCode, LINEAR);

    cout << "\nTesting error case for inserting nodes — small ID" << endl;
    if(tester.testInsertErr2(vdetect, 77)){
      cout << "\tError case for inserting nodes in hash table passed!\n";
    }else{
      cout << "\tError case for inserting nodes in hash table failed!\n";
    }
  }

  // Test that a node with a large ID is not added
  {
    VDetect vdetect(MINPRIME, hashCode, LINEAR);

    cout << "\nTesting error case for inserting nodes — large ID" << endl;
    if(tester.testInsertErr2(vdetect, 10000000)){
      cout << "\tError case for inserting nodes in hash table passed!\n";
    }else{
      cout << "\tError case for inserting nodes in hash table failed!\n";
    }
  }

  // Test that a non-extant node is not found
  {
    VDetect vdetect(MINPRIME, hashCode, LINEAR);

    cout << "\nTesting error case for finding nodes" << endl;
    if(tester.testFindErr(vdetect)){
      cout << "\tError case for finding nodes in hash table passed!\n";
    }else{
      cout << "\tError case for finding nodes in hash table failed!\n";
    }
  }

  // Test that a nodes are found — LINEAR
  {
    VDetect vdetect(MINPRIME, hashCode, LINEAR);

    cout << "\nTesting normal case for finding nodes — LINEAR" << endl;
    if(tester.testFindNorm(vdetect)){
      cout << "\tNormal case for finding nodes in LINEAR hash table passed!\n";
    }else{
      cout << "\tNormal case for finding nodes in LINEAR hash table failed!\n";
    }
  }

  // Test that a nodes are found — QUADRATIC
  {
    VDetect vdetect(MINPRIME, hashCode, QUADRATIC);

    cout << "\nTesting normal case for finding nodes — QUADRATIC" << endl;
    if(tester.testFindNorm(vdetect)){
      cout << "\tNormal case for finding nodes in QUADRATIC hash table passed!\n";
    }else{
      cout << "\tNormal case for finding nodes in QUADRATIC hash table failed!\n";
    }
  }

  // Test that a nodes are found — DOUBLEHASH
  {
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    cout << "\nTesting normal case for finding nodes — DOUBLEHASH" << endl;
    if(tester.testFindNorm(vdetect)){
      cout << "\tNormal case for finding nodes in DOUBLEHASH hash table passed!\n";
    }else{
      cout << "\tNormal case for finding nodes in DOUBLEHASH hash table failed!\n";
    }
  }

  // Test that colliding nodes are found — LINEAR
  {
    VDetect vdetect(MINPRIME, hashCode, LINEAR);

    cout << "\nTesting normal case for finding colliding nodes — LINEAR" << endl;
    if(tester.testFindEdge(vdetect)){
      cout << "\tNormal case for finding colliding nodes in LINEAR hash table passed!\n";
    }else{
      cout << "\tNormal case for finding colliding nodes in LINEAR hash table failed!\n";
    }
  }

  // Test that colliding nodes are found — QUADRATIC
  {
    VDetect vdetect(MINPRIME, hashCode, QUADRATIC);

    cout << "\nTesting normal case for finding colliding nodes — QUADRATIC" << endl;
    if(tester.testFindEdge(vdetect)){
      cout << "\tNormal case for finding colliding nodes in QUADRATIC hash table passed!\n";
    }else{
      cout << "\tNormal case for finding colliding nodes in QUADRATIC hash table failed!\n";
    }
  }

  // Test that colliding nodes are found — DOUBLEHASH
  {
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    cout << "\nTesting normal case for finding colliding nodes — DOUBLEHASH" << endl;
    if(tester.testFindEdge(vdetect)){
      cout << "\tNormal case for finding colliding nodes in DOUBLEHASH hash table passed!\n";
    }else{
      cout << "\tNormal case for finding colliding nodes in DOUBLEHASH hash table failed!\n";
    }
  }
  
  // Test that nodes are removed from a hash table via linear probing — zero rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, LINEAR);

    cout << "\nTesting edge case for removing nodes in LINEAR hash table" << endl;
    if(tester.testRemoveEdge(vdetect, 50)){
      cout << "\tEdge case for removing nodes in LINEAR hash table passed!\n";
    }else{
      cout << "\tEdge case for removing nodes in LINEAR hash table failed!\n";
    }
  }

  // Test that nodes are removed from a hash table via quadratic probing — zero rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, QUADRATIC);

    cout << "\nTesting edge case for removing nodes in QUADRATIC hash table" << endl;
    if(tester.testRemoveEdge(vdetect, 50)){
      cout << "\tEdge case for removing nodes in QUADRATIC hash table passed!\n";
    }else{
      cout << "\tEdge case for removing nodes in QUADRATIC hash table failed!\n";
    }
  }

  // Test that nodes are removed from a hash table via doublehash probing — zero rehashing
  {
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    cout << "\nTesting edge case for removing nodes in DOUBLEHASH hash table" << endl;
    if(tester.testRemoveEdge(vdetect, 50)){
      cout << "\tEdge case for removing nodes in DOUBLEHASH hash table passed!\n";
    }else{
      cout << "\tEdge case for removing nodes in DOUBLEHASH hash table failed!\n";
    }
  }

  // Test that nodes are removed from a hash table via linear probing
  {
    VDetect vdetect(MAXPRIME, hashCode, LINEAR);

    cout << "\nTesting normal case for removing nodes in LINEAR hash table" << endl;
    if(tester.testRemoveNorm(vdetect, 150)){
      cout << "\tNormal case for removing nodes in LINEAR hash table passed!\n";
    }else{
      cout << "\tNormal case for removing nodes in LINEAR hash table failed!\n";
    }
  }

  // Test that nodes are removed from a hash table via quadratic probing
  {
    VDetect vdetect(MAXPRIME, hashCode, QUADRATIC);

    cout << "\nTesting normal case for removing nodes in QUADRATIC hash table" << endl;
    if(tester.testRemoveNorm(vdetect, 150)){
      cout << "\tNormal case for removing nodes in QUADRATIC hash table passed!\n";
    }else{
      cout << "\tNormal case for removing nodes in QUADRATIC hash table failed!\n";
    }
  }

  // Test that nodes are removed from a hash table via doublehash probing
  {
    VDetect vdetect(MAXPRIME, hashCode, DOUBLEHASH);

    cout << "\nTesting normal case for removing nodes in DOUBLEHASH hash table" << endl;
    if(tester.testRemoveNorm(vdetect, 150)){
      cout << "\tNormal case for removing nodes in DOUBLEHASH hash table passed!\n";
    }else{
      cout << "\tNormal case for removing nodes in DOUBLEHASH hash table failed!\n";
    }
  }

  // Test rehashing is performed after insertion
  {
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    cout << "\nVerifying that rehashing occurs after insertion" << endl;
    if(tester.testRehashInsert(vdetect)){
      cout << "\tVerifying that rehashing occurs after insertion passed!\n";
    }else{
      cout << "\tVerifying that rehashing occurs after insertion failed!\n";
    }
  }

  // Test rehashing is completed after insertion
  {
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    cout << "\nVerifying that rehashing completes after insertion" << endl;
    if(tester.testRehashCompLF(vdetect)){
      cout << "\tVerifying that rehashing completes after insertion passed!\n";
    }else{
      cout << "\tVerifying that rehashing completes after insertion failed!\n";
    }
  }

  // Test rehashing is performed after removal
  {
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    cout << "\nVerifying that rehashing occurs after removal" << endl;
    if(tester.testRehashRem(vdetect)){
      cout << "\tVerifying that rehashing occurs after removal passed!\n";
    }else{
      cout << "\tVerifying that rehashing occurs after removal failed!\n";
    }
  }

  // Test rehashing is completed after insertion
  {
    VDetect vdetect(MINPRIME, hashCode, DOUBLEHASH);

    cout << "\nVerifying that rehashing completes after insertion" << endl;
    if(tester.testRehashCompDR(vdetect)){
      cout << "\tVerifying that rehashing completes after insertion passed!\n";
    }else{
      cout << "\tVerifying that rehashing completes after insertion failed!\n";
    }
  }

  return 0;
}

// Test normal case for inserting nodes
bool Tester::testInsertNorm(VDetect &vdetect, int size){
  // Initialize bacukp virus storage and IDs
  vector<Virus> dataList;
  vector<Virus> notInserted;
  Random RndID(MINID, MAXID);
  Virus** table = vdetect.m_currentTable;
  prob_t probing = vdetect.m_currProbing;
  int delSize = 0;

  // Old Table
  Virus** oldTable = vdetect.m_oldTable;
  prob_t oldProbing = vdetect.m_oldProbing;

  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus(sequencer(5, i), RndID.getRandNum(), true);

    // Keep track of which viruses have been inserted
    if(vdetect.insert(virus)){
      dataList.push_back(virus);
    }else{
      notInserted.push_back(virus);
      delSize++;
    }
  }

  // At least one table must be active
  if(!table && !oldTable){
    return false;
  }

  if(vdetect.m_currentSize + vdetect.m_oldSize != size){
    return false;
  }

  size -= delSize;

  // Ensure deleted elements have a shared key
  for(int i = 0; i < delSize; i++){
    if(!validDeleted(dataList, notInserted[i], size)){
      return false;
    }
  }
  
  // Re-calibrate tables
  table = vdetect.m_currentTable;
  oldTable = vdetect.m_oldTable;
  probing = vdetect.m_currProbing;
  oldProbing = vdetect.m_oldProbing;
  
  // Ensure nodes are inserted in the right place
  for(int i = 0; i < size; i++){
    Virus virus = dataList[i];
    int hashVal = vdetect.m_hash(virus.getKey()) % vdetect.m_currentCap;
    int currIndex = hashVal;
    int index = 0;
    bool currFound = false;
    
    while(!(vdetect.emptyVirus(*table[currIndex])) && !currFound){
      currIndex = validInsert(table, *table[currIndex], probing, hashVal, vdetect.m_currentCap, index);

      if(*table[currIndex] == virus){
	currFound = true;	
      }

      index++;
    }

    // If the node cannot be found in the current table, try the oldTable if it exists
    if(!currFound){
      if(oldTable){
	int oldHash = vdetect.m_hash(virus.getKey()) % vdetect.m_oldCap;
	int oldIndex = oldHash;
	index = 0;
      
	while(!(vdetect.emptyVirus(*oldTable[oldIndex]) && !currFound)){
	  oldIndex = validInsert(oldTable, *oldTable[oldIndex], oldProbing, oldHash, vdetect.m_oldCap, index);
	  
	  if(*oldTable[oldIndex] == virus){
	    currFound = true;
	  }
	}
      }

      // If the virus still cannot be found, return false;
      if(!currFound){
	return false;
      }
    }
  }

  return true;
}

bool Tester::testInsertEdge(VDetect &vdetect){
  // Initialize bacup virus storage and IDs
  vector<Virus> dataList;
  vector<Virus> notInserted;
  Random RndID(MINID, MAXID);
  Virus** table = vdetect.m_currentTable;
  prob_t probing = vdetect.m_currProbing;
  int size = 78;
  int delSize = 0;

  // Old Table
  Virus** oldTable = vdetect.m_oldTable;
  prob_t oldProbing = vdetect.m_oldProbing;

  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus(sequencer(5, i), RndID.getRandNum(), true);

    if(i > size/2){
      virus.setKey("AAAAA");
    }
    
    // Keep track of which viruses have been inserted
    if(vdetect.insert(virus)){
      dataList.push_back(virus);
    }else{
      notInserted.push_back(virus);
      delSize++;
    }
  }

  // At least one table must be active
  if(!table && !oldTable){
    return false;
  }

  // Check size and verify it
  size -= delSize;
  if(size != vdetect.m_currentSize){
    return false;
  }

  // Ensure deleted elements have a shared key
  for(int i = 0; i < delSize; i++){
    if(!validDeleted(dataList, notInserted[i], size)){
      return false;
    }
  }

  // Re-calibrate tables
  table = vdetect.m_currentTable;
  oldTable = vdetect.m_oldTable;
  probing = vdetect.m_currProbing;
  oldProbing = vdetect.m_oldProbing;

  // Ensure nodes are inserted in the right place
  for(int i = 0; i < size; i++){
    Virus virus = dataList[i];
    int hashVal = vdetect.m_hash(virus.getKey()) % vdetect.m_currentCap;
    int currIndex = hashVal;
    int index = 0;
    bool currFound = false;

    while(!(vdetect.emptyVirus(*table[currIndex])) && !currFound){
      currIndex = validInsert(table, *table[currIndex], probing, hashVal, vdetect.m_currentCap, index);

      if(*table[currIndex] == virus){
	currFound = true;
      }

      index++;
    }

    // If the node cannot be found in the current table, try the oldTable if it exists
    if(!currFound){
      if(oldTable){
	int oldHash = vdetect.m_hash(virus.getKey()) % vdetect.m_oldCap;
	int oldIndex = oldHash;
	index = 0;

	while(!(vdetect.emptyVirus(*oldTable[oldIndex]) && !currFound)){
	  oldIndex = validInsert(oldTable, *oldTable[oldIndex], oldProbing, oldHash, vdetect.m_oldCap, index);

	  if(*oldTable[oldIndex] == virus){
	    currFound = true;
	  }
	}
      }

      // If the virus still cannot be found, return false;
      if(!currFound){
	return false;
      }
    }
  }

  return true;
}

bool Tester::testInsertErr1(VDetect &vdetect){
  // Initialize bacup virus storage and IDs
  vector<Virus> dataList;
  vector<Virus> notInserted;
  Random RndID(MINID, MAXID);
  int size = 78;

  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus("BBBBB", 777777, true);

    // Keep track of which viruses have been inserted
    if(vdetect.insert(virus)){
      dataList.push_back(virus);
    }
    // Test passes if a dupe node is not inserted
    else{
      return true;
    }
  }

  return false;
}

bool Tester::testInsertErr2(VDetect &vdetect, int id){
  // Initialize bacup virus storage and IDs
  vector<Virus> dataList;
  vector<Virus> notInserted;
  Random RndID(MINID, MAXID);
  int size = 78;

  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus(sequencer(5, i), id, true);

    // Keep track of which viruses have been inserted
    if(vdetect.insert(virus)){
      dataList.push_back(virus);
    }
    // Test passes if a node with an invalid ID is not inserted
    else{
      return true;
    }
  }

  return false;
}

// Test error case for find a node — node doesn't exist
bool Tester::testFindErr(VDetect &vdetect){
  // Initialize bacup virus storage and IDs
  vector<Virus> dataList;
  vector<Virus> notInserted;
  Random RndID(MINID, MAXID);
  int size = 77;
  int delSize = 0;

  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus(sequencer(5, i), RndID.getRandNum(), true);

    // Keep track of which viruses have been inserted
    if(vdetect.insert(virus)){
      dataList.push_back(virus);
    }else{
      notInserted.push_back(virus);
      delSize++;
    }
  }

  Virus virus("AAAAA", 123456);

  // If a fake virus is found, return false
  if(vdetect.getVirus("AAAAA", 123456) == virus){
    return false;
  }else{
    return true;
  }
}

// Test normal case for finding nodes — several non-colliding nodes
bool Tester::testFindNorm(VDetect &vdetect){
  // Initialize bacup virus storage and IDs
  vector<Virus> dataList;
  vector<Virus> notInserted;
  vector<Virus> virusIndeces;
  Random RndID(MINID, MAXID);
  int size = 100;

  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus(sequencer(5, i), RndID.getRandNum(), true);

    // Keep track of half of the viruses
    if(vdetect.insert(virus)){
      dataList.push_back(virus);

      if(i % 2 == 0){
	virusIndeces.push_back(virus);
      }
    }
  }

  // If a node cannot be found, return false
  for(int i = 0; i < size/2; i++){
    if(vdetect.getVirus(virusIndeces[i].getKey(), virusIndeces[i].getID()) == EMPTY){
      return false;
    }
  }

  return true;
}

// Test edge case for finding nodes — several collided nodes
bool Tester::testFindEdge(VDetect &vdetect){
  // Initialize bacup virus storage and IDs
  vector<Virus> dataList;
  vector<Virus> notInserted;
  vector<Virus> virusIndeces;
  Random RndID(MINID, MAXID);
  int size = 100;
  
  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
      Virus virus(sequencer(5, i), RndID.getRandNum(), true);

      if(i > size/2){
	virus.setKey("AAAAA");
      }
    
    // Keep track of half of the viruses
    if(vdetect.insert(virus)){
      dataList.push_back(virus);

      if(i % 2 == 0){
	virusIndeces.push_back(virus);
      } 
    }    
  }

  // If a virus cannot be found, return false
  for(int i = 0; i < size/2; i++){
    if(vdetect.getVirus(virusIndeces[i].getKey(), virusIndeces[i].getID()) == EMPTY){
      return false;
    }
  }

  return true;
}

// Test edge case for removing nodes — few, no rehashing
bool Tester::testRemoveEdge(VDetect &vdetect, int size){
  // Initialize bacup virus storage and IDs
  vector<Virus> dataList;
  vector<Virus> toRemove;
  Random RndID(MINID, MAXID);
  Virus** table = vdetect.m_currentTable;
  prob_t probing = vdetect.m_currProbing;
  int delSize = 0;
  int startSize = 0;
  int startOldSize = 0;

  // Old Table
  Virus** oldTable = vdetect.m_oldTable;
  prob_t oldProbing = vdetect.m_oldProbing;
  
  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus(sequencer(5, i), RndID.getRandNum(), true);

    // Keep track of which viruses have been inserted
    if(i % 2 == 0){
      dataList.push_back(virus);
    }else{
      toRemove.push_back(virus);
      delSize++;
    }
    vdetect.insert(virus);
  }

  startSize = vdetect.m_currentCap;
  startOldSize = vdetect.m_oldCap;

  // If a virus is not removed, return false
  for(int i = 0; i < delSize; i++){
    if(!vdetect.remove(toRemove[i])){
      return false;
    }
  }

  // Re-calibrate tables
  table = vdetect.m_currentTable;
  oldTable = vdetect.m_oldTable;
  probing = vdetect.m_currProbing;
  oldProbing = vdetect.m_oldProbing;
  size = vdetect.m_currentSize/2;

  if(startSize != vdetect.m_currentCap || startOldSize != vdetect.m_oldCap){
    return false;
  }
 
  // Ensure nodes are inserted in the right place
  for(int i = 0; i < size; i++){
    Virus virus = dataList[i];
    int hashVal = vdetect.m_hash(virus.getKey()) % vdetect.m_currentCap;
    int currIndex = hashVal;
    int index = 0;
    bool currFound = false;
    
    while(!(vdetect.emptyVirus(*table[currIndex])) && !currFound){
      currIndex = validInsert(table, *table[currIndex], probing, hashVal, vdetect.m_currentCap, index);

      if(*table[currIndex] == virus){
	if(table[currIndex]->getUsed() == false){
	  return false;
	}
	currFound = true;
      }

      index++;
    }
    
    // If the node cannot be found in the current table, try the oldTable if it exists
    if(!currFound){
      if(oldTable){
	int oldHash = vdetect.m_hash(virus.getKey()) % vdetect.m_oldCap;
	int oldIndex = oldHash;
	index = 0;

	while(!(vdetect.emptyVirus(*oldTable[oldIndex]) && !currFound)){
	  oldIndex = validInsert(oldTable, *oldTable[oldIndex], oldProbing, oldHash, vdetect.m_oldCap, index);

	  if(*oldTable[oldIndex] == virus){
	    if(table[currIndex]->getUsed() == false){
	      return false;
	    }
	    currFound = true;
	  }
	}
      }

      // If the virus still cannot be found, return false;
      if(!currFound){
	return false;
      }
    }
  }

  return true;
}

// Test edge normal for removing nodes — few, collided
bool Tester::testRemoveNorm(VDetect &vdetect, int size){
  // Initialize bacup virus storage and IDs
  vector<Virus> dataList;
  vector<Virus> toRemove;
  Random RndID(MINID, MAXID);
  Virus** table = vdetect.m_currentTable;
  prob_t probing = vdetect.m_currProbing;
  int delSize = 0;

  // Old Table
  Virus** oldTable = vdetect.m_oldTable;
  prob_t oldProbing = vdetect.m_oldProbing;

  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus(sequencer(5, i), RndID.getRandNum(), true);

    // Keep track of which viruses have been inserted
    if(i % 2 == 0){
      dataList.push_back(virus);
    }else{
      toRemove.push_back(virus);
      delSize++;
    }
    vdetect.insert(virus);
  }

  // If virus isn't removed, return false
  for(int i = 0; i < delSize; i++){
    if(!vdetect.remove(toRemove[i])){
      return false;
    }
  }

  // Re-calibrate tables
  table = vdetect.m_currentTable;
  oldTable = vdetect.m_oldTable;
  probing = vdetect.m_currProbing;
  oldProbing = vdetect.m_oldProbing;
  size = vdetect.m_currentSize/2;

  // Ensure nodes are inserted in the right place
  for(int i = 0; i < size; i++){
    Virus virus = dataList[i];
    int hashVal = vdetect.m_hash(virus.getKey()) % vdetect.m_currentCap;
    int currIndex = hashVal;
    int index = 0;
    bool currFound = false;

    while(!(vdetect.emptyVirus(*table[currIndex])) && !currFound){
      currIndex = validInsert(table, *table[currIndex], probing, hashVal, vdetect.m_currentCap, index);

      if(*table[currIndex] == virus){
	if(table[currIndex]->getUsed() == false){
	  return false;
	}
	currFound = true;
      }

      index++;
    }
    // If the node cannot be found in the current table, try the oldTable if it exists
    if(!currFound){
      if(oldTable){
	int oldHash = vdetect.m_hash(virus.getKey()) % vdetect.m_oldCap;
	int oldIndex = oldHash;
	index = 0;

	while(!(vdetect.emptyVirus(*oldTable[oldIndex]) && !currFound)){
	  oldIndex = validInsert(oldTable, *oldTable[oldIndex], oldProbing, oldHash, vdetect.m_oldCap, index);

	  if(*oldTable[oldIndex] == virus){
	    if(table[currIndex]->getUsed() == false){
	      return false;
	    }
	    currFound = true;
	  }
	}
      }

      // If the virus still cannot be found, return false;
      if(!currFound){
	return false;
      }
    }
  }

  return true;
}

// Test rehashing is performed after insertion
bool Tester::testRehashInsert(VDetect &vdetect){
  // Initialize bacup virus storage and IDs
  vector<Virus> dataList;
  vector<Virus> notInserted;
  Random RndID(MINID, MAXID);
  int size = 100;
  int startCap = vdetect.m_currentCap;

  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus(sequencer(5, i), RndID.getRandNum(), true);

    // Keep track of which viruses have been inserted
    if(vdetect.insert(virus)){
      dataList.push_back(virus);
    }
  }

  // If the capacity is invalid, return false
  if(vdetect.m_currentCap != vdetect.findNextPrime(startCap/2 * 4)){
    return false;
  }

  // If the old table isn't removed, return false
  if(vdetect.m_oldTable != nullptr){
    return false;
  }

  return true;
}

// Test that old, empty table is removed — Load Factor
bool Tester::testRehashCompLF(VDetect &vdetect){
  // Initialize bacup virus storage and IDs
  vector<Virus> dataList;
  vector<Virus> notInserted;
  Random RndID(MINID, MAXID);
  int size = 150;
  Virus** table = vdetect.m_currentTable;
  Virus** oldTable = vdetect.m_oldTable;
  prob_t probing = vdetect.m_currProbing;
  prob_t oldProbing = vdetect.m_oldProbing;

  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus(sequencer(5, i), RndID.getRandNum(), true);

    // Keep track of which viruses have been inserted
    if(vdetect.insert(virus)){
      dataList.push_back(virus);
    }
  }

  // Re-calibrate tables
  table = vdetect.m_currentTable;
  oldTable = vdetect.m_oldTable;
  probing = vdetect.m_currProbing;
  oldProbing = vdetect.m_oldProbing;

  // Ensure nodes are inserted in the right place
  for(int i = 0; i < size; i++){
    Virus virus = dataList[i];
    int hashVal = vdetect.m_hash(virus.getKey()) % vdetect.m_currentCap;
    int currIndex = hashVal;
    int index = 0;
    bool currFound = false;

    while(!(vdetect.emptyVirus(*table[currIndex])) && !currFound){
      currIndex = validInsert(table, *table[currIndex], probing, hashVal, vdetect.m_currentCap, index);

      if(*table[currIndex] == virus){
	currFound = true;
      }

      index++;
    }

    // If the node cannot be found in the current table, try the oldTable if it exists
    if(!currFound){
      if(oldTable){
	int oldHash = vdetect.m_hash(virus.getKey()) % vdetect.m_oldCap;
	int oldIndex = oldHash;
	index = 0;

	while(!(vdetect.emptyVirus(*oldTable[oldIndex]) && !currFound)){
	  oldIndex = validInsert(oldTable, *oldTable[oldIndex], oldProbing, oldHash, vdetect.m_oldCap, index);

	  if(*oldTable[oldIndex] == virus){
	    currFound = true;
	  }
	}
      }

      // If the virus still cannot be found, return false;
      if(!currFound){
	return false;
      }
    }
  }

  return true;
}

// Test rehashing is performed after removal
bool Tester::testRehashRem(VDetect &vdetect){
  vector<Virus> dataList;
  vector<Virus> toRemove;
  Random RndID(MINID, MAXID);
  int delSize = 0;
  int size = 66;

  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus(sequencer(5, i), RndID.getRandNum(), true);

    // Keep track of which viruses have been inserted
    if(i % 10 == 0){
      dataList.push_back(virus);
    }else{
      toRemove.push_back(virus);
      delSize++;
    }
    vdetect.insert(virus);
  }

  int startCap = vdetect.m_currentCap;
  bool decrease = false;

  // If the node isn't removed, return false
  for(int i = 0; i < delSize; i++){
    if(!vdetect.remove(toRemove[i])){
      return false;
    }

    // If the new cap is invalid, return false
    if(!decrease && vdetect.m_currentCap < startCap)
      decrease = true;
  }

  if(!decrease){
    return false;
  }

  if(vdetect.m_oldTable != nullptr){
    return false;
  }

  return true;
}

// Test that old, empty table is removed — Deletion Ratio
bool Tester::testRehashCompDR(VDetect &vdetect){
  vector<Virus> dataList;
  vector<Virus> toRemove;
  Random RndID(MINID, MAXID);
  int delSize = 0;
  int size = 66;

  // Insert viruses into hash table and vector
  for(int i = 0; i < size; i++){
    Virus virus(sequencer(5, i), RndID.getRandNum(), true);

    // Keep track of which viruses have been inserted
    if(i % 10 == 0){
      dataList.push_back(virus);
    }else{
      toRemove.push_back(virus);
      delSize++;
    }
    vdetect.insert(virus);
  }

  for(int i = 0; i < delSize; i++){
    if(!vdetect.remove(toRemove[i])){
      return false;
    }
  }

  for(int i = 0; i < 7; i++){
    if(vdetect.getVirus(dataList[i].getKey(), dataList[i].getID()) == EMPTY){
      cout << dataList[i].getKey() << endl;
      return false;
    }
  }

  return true;
}

// HELPER FUNCTIONS

// Helper function that ensures deleted elements have a shared key
bool Tester::validDeleted(vector<Virus> currList, Virus notInserted, int size){
  for(int j = 0; j < size; j++){
    if(currList[j] == notInserted){
      return true;
    }
  }
  
  return false;
}


// Helper function that ensures nodes are inserted in the right place
int Tester::validInsert(Virus** table, Virus virus, prob_t probing, int hashVal, int size, int i){
  int index = 0;

  if(probing == LINEAR){
    index = (hashVal + i) % size;
  }else if(probing == QUADRATIC){
    index = (hashVal + i * i) % size;
  }else if(probing == DOUBLEHASH){
    index = ((hashVal % size) + i * (11 - hashVal % 11) ) % size;
  }

  return index;
}

// Predefined functions
unsigned int hashCode(const string str) {
  unsigned int val = 0 ;
  const unsigned int thirtyThree = 33 ;  // magic number from textbook
  for ( int i = 0 ; i < str.length(); i++)
    val = val * thirtyThree + str[i] ;
  return val ;
}
string sequencer(int size, int seedNum){
  //this function returns a random DNA sequence
  string sequence = "";
  Random rndObject(0,3);
  rndObject.setSeed(seedNum);
  for (int i=0;i<size;i++){
    sequence = sequence + ALPHA[rndObject.getRandNum()];
  }
  return sequence;
}
