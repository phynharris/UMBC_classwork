// Jaylen Jenkins — FP31977
// CMSC 341 - Spring 26 - Project 4
#include "vdetect.h"

// Constructor for VDetect object
// Accepts max size, hash function, and probing policy
VDetect::VDetect(int size, hash_fn hash, prob_t probing = DEFPOLCY){
  // Set members
  m_hash = hash;
  m_newPolicy = probing;

  // Initialize current table with default viruses
  setCurrCap(size);
  m_currentSize = 0;
  m_currentTable = new Virus*[size]{};
  for(int i = 0; i < size; i++){
    Virus* virus = new Virus();
    m_currentTable[i] = {virus};
  }

  m_currNumDeleted = 0;
  m_currProbing = probing;

  // Initialize old table
  m_oldCap = 0;
  m_oldSize = 0;
  m_oldTable = nullptr;

  m_oldNumDeleted = 0;
  m_oldProbing = DEFPOLCY;

  m_transferIndex = 0;
}

// Destroy VDetect object
VDetect::~VDetect(){
  // Clear both tables
  clear(m_currentTable, m_currentCap);
  clear(m_oldTable, m_oldCap);
}

// Change the current probing policy
// Accepts a probing policy
void VDetect::changeProbPolicy(prob_t policy){
  m_newPolicy = policy;
}

// Insert a new virus into the hash table
// Accepts a virus to insert
// Returns operation success
bool VDetect::insert(Virus virus){
  // Do not insert if ID is invalid
  if(virus.getID() < MINID || virus.getID() > MAXID){
    // Check if table needs rehashing
    rehashCall();
    return false;
  }

  // Edge Case: If the hash table is completely full...
  // do not insert unless the a matching, used virus exists
  if(m_currentSize == MAXPRIME){
    Virus testVirus = getVirus(virus.getKey(), virus.getID());

    if(testVirus.getUsed()){
      return false;
    }
  }

  // Calculate the hash value
  int currHashVal = m_hash(virus.getKey());
  int oldHashVal = 0;
  if(m_oldCap > 0){
    oldHashVal = currHashVal % m_oldCap;
  }
  currHashVal = currHashVal % m_currentCap;

  // Variables for verifying the existence of new virus
  int index = 0;
  int currIndex = currHashVal;
  int oldIndex = oldHashVal;
  bool currFound = false;
  bool oldFound = false;
 
  // Do not insert if the node is in use in the current table
  while(!emptyVirus(*m_currentTable[currIndex]) && !currFound){
    currIndex = probe(m_currProbing, currHashVal, m_currentCap, index, m_currentTable);

    // Verify if a duplicate is not in use
    if(*m_currentTable[currIndex] == virus){
      if(m_currentTable[currIndex]->getUsed() == true){
	  rehashCall();
	  return false;
      }else{
	currFound = true;
      }
    }

    if(!currFound){
      index++;
    }
  }

  // Recalibrate values
  currHashVal = currIndex;
  index = 0;

  // Do not insert if the node is in use in the old table (if it exsists)
  if(m_oldTable != nullptr){
    while(!emptyVirus(*m_oldTable[oldIndex]) && !oldFound){
      oldIndex = probe(m_oldProbing, oldHashVal, m_oldCap, index, m_oldTable);

      // Verify if a duplicate is not in use
      if(*m_oldTable[oldIndex] == virus){
	if(m_oldTable[oldIndex]->getUsed() == true){
	  rehashCall();
	  return false;
	}else{
	  oldFound = true;
	}
      }

      if(!oldFound){
	index++;
      }
    }
    oldHashVal = oldIndex;
  }
  
  // Insert into the current table
  Virus* newVirus = new Virus(virus);
  delete m_currentTable[currHashVal];
  m_currentTable[currHashVal] = newVirus;
  m_currentSize += 1;
  
  // Check if the table needs to be rehashed
  if(m_transferIndex == 0){
    checkRehashing();
  }
  
  // Rehash 25% of live nodes incrementally into new table
  // If the old table is empty, it must be removed
  rehashCall();
  
  return true;
}

// Remove a virus from the system
// Accepts a virus to remove
// Returns operation success
bool VDetect::remove(Virus virus){
  // If the system is empty, return false
  if(m_currentSize <=0 && m_oldSize <= 0){
    return false;
  }

  // Initialize hash values
  int currHashVal = m_hash(virus.getKey()) % m_currentCap;
  int currIndex = currHashVal;
  int oldHashVal = 0;
  if(m_oldSize > 0){
    oldHashVal = m_hash(virus.getKey()) % m_oldCap;
  }

  // Variables for verifying the existence of new virus
  int oldIndex = oldHashVal;
  string key = virus.getKey();
  int id = virus.getID();
  Virus toDelete = getVirus(key, id);
  int index = 0;

  // If the virus to delete does not exist, return
  if(toDelete == EMPTY){
    rehashCall();
    return false;
  }
  
  // Remove a virus from the current table
  while(!emptyVirus(*m_currentTable[currIndex])){
    currIndex = probe(m_currProbing, currHashVal, m_currentCap, index, m_currentTable);

    // Verifies that the desired node is in use
    if(*m_currentTable[currIndex] == virus){
      if(m_currentTable[currIndex]->getUsed() == false){
	rehashCall();
	return false;
      }else{
	removeVirus(m_currentTable, currIndex);

	// Check if the table needs to be rehashed
	if(m_transferIndex == 0){
	  checkRehashing();
	}
	
	rehashCall();
	return true;
      }
    }
    index++;
  }

  // Recalibrate values
  currHashVal = currIndex;
  index = 0;

  // Do not remove if the node is not in use in the old table
  if(m_oldTable != nullptr){
    while(!emptyVirus(*m_oldTable[oldIndex])){
      oldIndex = probe(m_oldProbing, oldHashVal, m_oldCap, index, m_oldTable);

      // Verifies that the desired node is in use
      if(*m_oldTable[oldIndex] == virus){
	if(m_oldTable[oldIndex]->getUsed() == false){
	  rehashCall();
	  return false;
	}else{
	  removeVirus(m_oldTable, oldIndex);

	  // Check if the table needs to be rehashed
	  if(m_transferIndex == 0){
	    checkRehashing();
	  }
	  
	  rehashCall();
	  return true;
	}
      }

      index++;
    }
    oldHashVal = oldIndex;
  }
  
  return false;
}

// Locate a virus in the system
// Given a sequence and id to locate
// Returns matching virus
const Virus VDetect::getVirus(string sequence, int id) const{
  // Initialize hash values and iterator values
  int hashVal = m_hash(sequence) % m_currentCap;
  int currIndex = hashVal;
  int index = 0;
  int subHash = 0;
  int size = m_currentCap;
  Virus virus(sequence, id, true);

  // Probe through the current system for desired virus
  while(!(*m_currentTable[currIndex] == virus) && index < size){
    if(m_currProbing == LINEAR){
      subHash = (hashVal + index) % size;
    }else if(m_currProbing == QUADRATIC){
      subHash = (hashVal + index * index) % size;
    }else if(m_currProbing == DOUBLEHASH){
      subHash = ((hashVal % size) + index * (11 - hashVal % 11) ) % size;
    }

    currIndex = subHash;
    index++;
  }

  // If the virus is not found...
  // Probe through the old table
  if(*m_currentTable[currIndex] == virus){
    return *m_currentTable[currIndex];
  }else{
    if(m_oldTable){
      // Recalibrate hash and iterator values
      int oldHash = m_hash(sequence) % m_oldCap;
      currIndex = oldHash;
      size = m_oldCap;
      index = 0;
    
      // Probe through old table
      while(!(*m_oldTable[currIndex] == virus) && index < size){
	if(m_oldProbing == LINEAR){
	  subHash = (oldHash + index) % size;
	}else if(m_oldProbing == QUADRATIC){
	  subHash = (oldHash + index * index) % size;
	}else if(m_oldProbing == DOUBLEHASH){
	  subHash = ((oldHash % size) + index * (11 - oldHash % 11) ) % size;
	}

	currIndex = subHash;
	index++;
      }
      if(*m_oldTable[currIndex] == virus){
	return *m_oldTable[currIndex];
      }
    }

    // Return EMPTY if the virus was found in neither table
    return EMPTY;
  }
}

// Update a virus's ID
// Accepts a virus and an id
// Returns operation success
bool VDetect::updateID(Virus virus, int id){
  // Do not change ID if it is invalid
  if(id < MINID || id > MAXID){
    return false;
  }

  // Do not change ID if a virus with that same ID already exists
  if(!(getVirus(virus.getKey(), id) == EMPTY)){
    return false;
  }

  // Calculate the hash value
  int currHashVal = m_hash(virus.getKey());
  int oldHashVal = 0;
  if(m_oldCap > 0){
    oldHashVal = currHashVal % m_oldCap;
  }
  currHashVal = currHashVal % m_currentCap;

  // Variables for verifying the existence of new virus
  int index = 0;
  int currIndex = currHashVal;
  int oldIndex = oldHashVal;
  bool currFound = false;
  bool oldFound = false;

  // Locate the virus's index and update it (curr)
  while(!emptyVirus(*m_currentTable[currIndex]) && !currFound){
    currIndex = probe(m_currProbing, currHashVal, m_currentCap, index, m_currentTable);

    // Verify if node is not in use
    if(*m_currentTable[currIndex] == virus){
      if(m_currentTable[currIndex]->getUsed() == true){
	rehashCall();
	return false;
      }else{
	currFound = true;
      }
    }

    if(!currFound){
      index++;
    }
  }

  // If node was found in the current table, operation success
  if(currFound){
    m_currentTable[currIndex]->setID(id);
    return true;
  }

  // Recalibrate values
  currHashVal = currIndex;
  index = 0;

  // Locate the virus's index and update it (old)
  if(m_oldTable != nullptr){
    while(!emptyVirus(*m_oldTable[oldIndex]) && !oldFound){
      oldIndex = probe(m_oldProbing, oldHashVal, m_oldCap, index, m_oldTable);

      // Verify if a duplicate is not in use
      if(*m_oldTable[oldIndex] == virus){
	if(m_oldTable[oldIndex]->getUsed() == true){
	  rehashCall();
	  return false;
	}else{
	  oldFound = true;
	}
      }

      if(!oldFound){
	index++;
      }
    }
    oldHashVal = oldIndex;
  }

  // If node was found in the old table, operation success
  if(oldFound){
    m_oldTable[oldIndex]->setID(id);
    return true;
  }
  
  return false;
}

// Determine the load factor
// Returns the load factor
float VDetect::lambda() const {
  float currSize = m_currentSize;
  float currCap = m_currentCap;

  return currSize/currCap;
}

// Determine the deleted ratio
// Returns the deleted ratio
float VDetect::deletedRatio() const {
  float currDel = m_currNumDeleted;
  float currSize = m_currentSize;

  return currDel/currSize;
}

void VDetect::dump() const {
  cout << "Dump for the current table: " << endl;
  if (m_currentTable != nullptr)
    for (int i = 0; i < m_currentCap; i++) {
      cout << "[" << i << "] : " << m_currentTable[i] << endl;
    }
  cout << "Dump for the old table: " << endl;
  if (m_oldTable != nullptr)
    for (int i = 0; i < m_oldCap; i++) {
      cout << "[" << i << "] : " << m_oldTable[i] << endl;
    }
}

bool VDetect::isPrime(int number){
  bool result = true;
  for (int i = 2; i <= number / 2; ++i) {
    if (number % i == 0) {
      result = false;
      break;
    }
  }
  return result;
}

int VDetect::findNextPrime(int current){
  //we always stay within the range [MINPRIME-MAXPRIME]
  //the smallest prime starts at MINPRIME
  if (current < MINPRIME) current = MINPRIME-1;
  for (int i=current; i<MAXPRIME; i++) {
    for (int j=2; j*j<=i; j++) {
      if (i % j == 0)
	break;
      else if (j+1 > sqrt(i) && i != current) {
	return i;
      }
    }
  }
  //if a user tries to go over MAXPRIME
  return MAXPRIME;
}


// HELPER FUNCTIONS

// Calculates the rehash index
// Given the current transfer index and a table capacity
// Returns an updated rehash index
int VDetect::calcIndex(int transIndex, int cap){
  if(transIndex == cap/4){
    return 0;
  }else if(transIndex == cap/2){
    return cap/4;
  }else if(transIndex == cap * 3 / 4){
    return cap / 4 * 2;
  }else{
    return cap/4 * 3;
  } 
}

// Calculates the transfer index
// Given the current transfer index and a table capacity
// Returns an updated transfer index
int VDetect::calcTI(int index, int cap){
  if(index == 0 || index == cap){
    index = cap/4;
  }else if(index == cap/4){
    index = cap/2;
  }else if(index == cap/2){
    index = cap * 3 / 4;
  }else if(index == cap * 3 / 4){
    index = cap;
  }else{
    index = 0;
  }
  
  return index;
}

// Traverse the hash table
// Accepts a probing policy, a hash index, the max size, an index value, and a table
// Returns an index
int VDetect::probe(prob_t probing, int hashVal, int size, int i, Virus** table){
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

// Determine if a virus is empty
// Accepts a virus
// Returns validity
bool VDetect::emptyVirus(Virus virus){
  if(virus.getKey() == ""){
    return true;
  }else{
    return false;
  }
}

// Determine if the current table is empty
// Returns validity
bool VDetect::isCurrEmpty(){
  if(m_currentSize == 0){
    return true;
  }else{
    return false;
  }
}

// Check if the table needs to be rehashed and rehash it if needed
void VDetect::checkRehashing(){

  // If current table is empty, do not rehash
  if(!isCurrEmpty()){
    // Rehash if the load factor or deletion ratio demands it
    if(lambda() <= 0.5 && deletedRatio() <= 0.8){
      return;
    }

    // Resize the table
    resize(m_currentTable, m_currentCap, m_currentSize, m_currNumDeleted, m_currProbing);

    // Update the transfer index
    m_transferIndex = calcTI(m_transferIndex, m_oldCap);
  }
}

// Clear a table
// Accepts a table and its capacity
void VDetect::clear(Virus** table, int cap){
  // Clear the nodes
  if(table != nullptr){
    for(int i = 0; i < cap; i++){
      if(table[i] != nullptr){
	delete table[i];
	table[i] = nullptr;
      }
    }

    // Clear the table
    delete[] table;
    table = nullptr;
  }
}

// Rehash the system
// Accepts the old table and the transfer index
void VDetect::rehash(Virus** oldTable, int transferIndex){
  // Insert nodes incrementally in quarters
  for(int i = calcIndex(transferIndex, m_oldCap); i < transferIndex; i++){

    // If the node is in use, then it should be re-inserted
    if(oldTable[i]->getUsed() == true){
      reinsert(oldTable[i], i);
    }
  }
}

// Call the rehash function
void VDetect::rehashCall(){
  // If the transfer index is greater than 0, rehash the table
  if(m_transferIndex > 0){
    rehash(m_oldTable, m_transferIndex);

    // If the transferIndex equals the oldCap, then remove the old table
    if(m_transferIndex == m_oldCap){
      m_transferIndex = 0;
      clear(m_oldTable, m_oldCap);
      m_oldTable = nullptr;
    }else{
      m_transferIndex = calcTI(m_transferIndex, m_oldCap);
    }
  }
}

// Reinsert nodes from the old table to the current table
// Accepts a virus reference and its index
void VDetect::reinsert(Virus* virus, int oldIndex){
  // If the virus is empty, do not re-insert
  if(emptyVirus(*virus)){
    return;
  }

  // If the virus is used, do not re-insert
  if(!(virus->getUsed())){
    return;
  }
  
  int hashVal = m_hash(virus->getKey()) % m_currentCap;
  int currIndex = hashVal;
  int index = 0;
  
  // Locate where the node can be inserted
  while(!emptyVirus(*m_currentTable[currIndex]) && index < m_currentCap){
    currIndex = probe(m_currProbing, hashVal, m_currentCap, index, m_currentTable);
    index++;
  }
  
  hashVal = currIndex;

  // Swap the viruses in the old and new table
  m_oldTable[oldIndex] = m_currentTable[hashVal];
  m_currentTable[hashVal] = virus;

  m_currentSize += 1;
  m_oldSize -= 1;
}

// Remove a virus
// Accepts a table and an index
void VDetect::removeVirus(Virus** table, int index){
  table[index]->setUsed(false);

  // Increase the deleted size of the particular table
  if(table == m_currentTable){
    m_currNumDeleted++;
  }else if(table == m_oldTable){
    m_oldNumDeleted++;
  }
}

// Resize the system
// Accepts a table, its capacity, current size, total deleted, and its probing policy
void VDetect::resize(Virus** table, int cap, int size, int numDeleted, prob_t probing){
  // Set old variables equal to the modern
  m_oldTable = table;
  m_oldCap = cap;
  m_oldSize = size;
  m_oldNumDeleted = numDeleted;
  m_oldProbing = probing;

  // Updates the probing policy
  updatePolicy();

  // Adjust the new cap and other variables
  m_currentCap = 4 * (size - numDeleted);
  if(!isPrime(m_currentCap)){
    m_currentCap = findNextPrime(m_currentCap);
  }
 
  m_currentSize = 0;
  m_currNumDeleted = 0;

  // Fill new current table with empty viruses
  Virus virus;
  m_currentTable = new Virus*[m_currentCap]{};
  
  for(int i = 0; i < m_currentCap; i++){
    Virus* virus = new Virus();
    m_currentTable[i] = virus;
  }
  
}

// Set the current cap to a prime
// Accepts a size to update
void VDetect::setCurrCap(int size){
  if(!isPrime(size)){
    m_currentCap = findNextPrime(size);
  }else{
    m_currentCap = size;
  }
}

// Updates the current probing policy
void VDetect::updatePolicy(){
  if(m_newPolicy != m_currProbing){
    m_oldProbing = m_currProbing;
    m_currProbing = m_newPolicy;
  }
}
