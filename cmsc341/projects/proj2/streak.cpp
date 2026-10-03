// UMBC - CMSC 341 - Spring 2026 - Proj2
#include "streak.h"

Streak::Streak(): m_root(nullptr), m_gridID(0), m_left(nullptr), m_right(nullptr){}

Streak::Streak(int grid, Tiger tigers[], int population){
  m_root = nullptr;
  m_gridID = grid;
  m_left = nullptr;
  m_right = nullptr;
  Tiger tiger;

  for(int i = 0; i < population; i++){
    tiger = tigers[i];
    insert(tiger);
  }
}

Streak::~Streak(){
  clear();
}

void Streak::insert(const Tiger& tiger){
  // If the root is a nullpointer, then the tiger becomes the root.
   if(!m_root){
    m_root = new Tiger(tiger);
   }
   // Inserts a node if it has a unique ID
   else if(!findTiger(tiger.m_id)){
     Tiger* newTiger = new Tiger(tiger);
     insertHelper(newTiger, m_root); 
   }
}

// Helper Function
void Streak::insertHelper(Tiger* tiger, Tiger* root){
  // If the tiger id is less than the root's, insert left
  if(tiger->m_id < root->m_id){
    // If the left branch is a nullptr, tiger is inserted left
    if(!(root->m_left)){
      root->m_left = tiger;
    }
    // If the left branch is occupied, call recursion with that node as the root
    else{
      insertHelper(tiger, root->m_left);
    }
  }
  // If the tiger id is greater than the root's, insert right
  else if(tiger->m_id > root->m_id){
    // If the right branch is a nullptr, tiger is inserted right
    if(!(root->m_right)){
      root->m_right = tiger;
    }
    // If the right branch is occupied, call recursion with that node as the root
    else{
      insertHelper(tiger, root->m_right);
    }
  }

  // Sets height of parent nodes
  root->m_height = setHeight(root->m_left, root->m_right);

  // Check if the tree needs rotating
  rotation(root);
}

// Helper Function
int Streak::setHeight(Tiger* left, Tiger* right){
  int left_h = 0;
  int right_h = 0;
  
  // If the node has no children, height is 0
  if(!left && !right){
    return 0;
  }

  // If there is a left node, get that node's height
  if(left != nullptr){
    left_h = setHeight(left->m_left, left->m_right) + 1;
  }

  // If there is a right node, get that node's height
  if(right != nullptr){
    right_h = setHeight(right->m_left, right->m_right) + 1; 
  }

  // Return the larger height
  if(left_h >= right_h){
    return left_h;
  }else{
    return right_h;
  }
}

// Helper Function
Tiger* Streak::getParent(Tiger* tiger, Tiger* root){

  if(root == nullptr || tiger == nullptr){
    return nullptr;
  }
  
  // If either the left or right node of the root is the current node, then root its the parent
  if(root->m_left == tiger || root->m_right == tiger){
    return root;
  }

  // Compare root and current ID's; smaller cur -> left, bigger cur -> right
  if(tiger->m_id < root->m_id){
    return getParent(tiger, root->m_left);
  }else if(tiger->m_id > root->m_id){
    return getParent(tiger, root->m_right);
  }

  return nullptr;
}

// Helper Function
void Streak::rotation(Tiger* tiger){
  // If the curr is the root, do not perform rotation
  if(tiger == m_root){
    return;
  }
  
  Tiger* parent = getParent(tiger, m_root); // Obtain grandparent
  int left = -1;
  int right = -1;

  if(!parent){
    return;
  }

  // Get heights of parent's children
  if(parent->m_left != nullptr){
    left = parent->m_left->m_height;
  }

  if(parent->m_right != nullptr){
    right = parent->m_right->m_height;
  }

  // If there is a height imbalance, rotate
  if(left > right && left - right > 1){
    rotateLeft(tiger, parent);
  }else if(right > left && right - left > 1){
    rotateRight(tiger, parent);
  }
}

// Helper Function
void Streak::rotateLeft(Tiger* tiger, Tiger* grandparent){
  Tiger* child;           // Indicates child of central node/parent
  Tiger* parent = tiger;  // Indicates current node/parent
  Tiger* ancestor = nullptr;
  bool rightWeight = false;

  if(grandparent != nullptr){
    ancestor = getParent(grandparent, m_root);
  }

  if(tiger->m_right != nullptr){
    if(tiger->m_left == nullptr){
      rightWeight = true;
    }else if(tiger->m_left->m_height < tiger->m_right->m_height){
      rightWeight = true;
    }
  }
  
  // If the child weight is to the right, rotate to an all-left form
  if(rightWeight){
    // Sets the child equal to the parent's right child
    child = parent->m_right;

    // Makes grandparent point to child instead of parent
    grandparent->m_left = child;

    // Makes the parent point to the child's right subtree
    parent->m_right = child->m_left;

    // Makes the child's left child it's former parent 
    child->m_left = parent;

    // Sets parent equal to child
    parent->m_height -= 1;
    child->m_height += 1;
    parent = grandparent->m_left;
  }

  if(grandparent == m_root){
    m_root = grandparent->m_left;
  }else if(parent == m_root){
    m_root = parent->m_left;
  }
  
  grandparent->m_left = parent->m_right;
  parent->m_right = grandparent;

  if(ancestor != nullptr){
    if(ancestor->m_left == grandparent){
    ancestor->m_left = parent;
    }
    else if(ancestor->m_right == grandparent){
      ancestor->m_right = parent;
    }
  }

  grandparent-> m_height -= 1;
}

// Helper Function
void Streak::rotateRight(Tiger* tiger, Tiger* grandparent){
  Tiger* child;           // Indicates child of central node/parent
  Tiger* parent = tiger;  // Indicates current node/parent
  Tiger* ancestor = nullptr;
  bool leftWeight = false;

  if(grandparent != nullptr){
    ancestor = getParent(grandparent, m_root);
  }
  
  if(tiger->m_left != nullptr){
    if(tiger->m_right == nullptr){
      leftWeight = true;
    }else if(tiger->m_right->m_height < tiger->m_left->m_height){
      leftWeight = true;
    }
  }

  // If the child weight is to the right, rotate to an all-left form
  if(leftWeight){
    // Sets the child equal to the parent's right child
    child = parent->m_left;

    // Makes grandparent point to child instead of parent
    grandparent->m_right = child;

    // Makes the parent point to the child's right subtree
    parent->m_left = child->m_right;

    // Makes the child's left child it's former parent
    child->m_right = parent;

    parent->m_height -= 1;
    child->m_height += 1;
    // Sets parent equal to child
    parent = grandparent->m_right;
  }

  if(grandparent == m_root){
    m_root = grandparent->m_right;
  }else if(parent == m_root){
    m_root = parent->m_left;
  };

  grandparent->m_right = parent->m_left;
  parent->m_left = grandparent;

  if(ancestor != nullptr){
    if(ancestor->m_left == grandparent){
      ancestor->m_left = parent;
    }
    else if(ancestor->m_right == grandparent){
      ancestor->m_right = parent;
    }
  }

  grandparent-> m_height -= 1;
}

// Helper Function
void Streak::clearRecurs(Tiger* root){
  if(root == nullptr){
    return;
  }
  
  if(root->m_left != nullptr){
    clearRecurs(root->m_left);
  }

  if(root->m_right != nullptr){
    clearRecurs(root->m_right);
  }

  delete root;
  root = nullptr;
}

void Streak::clear(){
  clearRecurs(m_root);
}

void Streak::remove(int id){
  if(!findTiger(id)){
    return;
  }

  if(m_root == nullptr){
    return;
  }

  Tiger* tiger = getTiger(id);
  Tiger* parent = getParent(tiger, m_root);
  Tiger* succ = nullptr;
  Tiger* succParent = nullptr;
  
  Tiger* left = tiger->m_left;
  Tiger* right = tiger->m_right;
  string branch = getBranch(tiger);
  string succBranch = "none";

  // If m_root is the only node, delete root
  if(tiger == m_root && left != nullptr && right != nullptr){
    delete tiger;
    m_root = nullptr;
    return;
  }

  
  // If node has 1 or 0 children
  if(tiger->m_height == 0 || tiger->m_height == 1){
    if(left == nullptr){
      if(branch == "left"){
	parent->m_left = right;
      }else if(branch == "right"){
	parent->m_right = right;
      }

      if(tiger == m_root){
	m_root = right;
      }
    }else{
      if(branch == "left"){
	parent->m_left = left;
      }else if(branch == "right"){
	parent->m_right = left;
      }

      if(tiger == m_root){
	m_root = left;
      }

      if(left && right){
	left->m_right = right;
      }
    }
  }else{
    succ = getSucc(tiger);
    succParent = getParent(succ, m_root);
    succBranch = getBranch(succ);

    if(succBranch == "left"){
      succParent->m_left = succ->m_left;
    }else if(succBranch == "right"){
      succParent->m_right = succ->m_left;
    }
    
    if(parent == m_root){
      if(branch == "left"){
	m_root->m_left = succ;
      }else if(branch == "right"){
	m_root->m_right = succ;
      }
    }else{
      if(branch == "left"){
	parent->m_left = succ;
      }else if(branch == "right"){
	parent->m_right = succ;
      }

      if(tiger == m_root){
	m_root = succ;
      }
    }

    if(succ){
      succ->m_left = tiger->m_left;
      succ->m_right = tiger->m_right;
      succ->m_height = tiger->m_height;
    }
  }

  delete tiger;
  tiger = nullptr;  

  heightRecurs(m_root);
}

// Helper Function
void Streak::heightRecurs(Tiger* root){
  if(root->m_left != nullptr){
    heightRecurs(root->m_left);
  }
  if(root->m_right != nullptr){
    heightRecurs(root->m_right);
  }
  
  root->m_height = setHeight(root->m_left, root->m_right);
  rotation(root);
}

// Helper Function
Tiger* Streak::getSucc(Tiger* tiger){
  if(tiger->m_left == nullptr && tiger->m_right == nullptr){
    return nullptr;
  }
  
  Tiger* left = tiger->m_left;
  Tiger* right = nullptr;

  if(left->m_right == nullptr){
    return left;
  }

  right = left->m_right;
  while(right->m_right != nullptr){
    right = right->m_right;
  }
  
  return right;
}

void Streak::listTigers() const {
  if(m_root == nullptr){
    cout << "There are no tigers in this tree." << endl;
    return;
  }

  listRecurs(m_root);
}

// Helper Function
void Streak::listRecurs(Tiger* tiger) const{
  if(tiger->m_left != nullptr){
    listRecurs(tiger->m_left);
  }

  cout << tiger->m_id << ":" << tiger->getAgeStr() << ":" << tiger->getGenderStr() << ":" << tiger->getStateStr() << endl;
  
  if(tiger->m_right != nullptr){
    listRecurs(tiger->m_right);
  }
}

bool Streak::setState(int id, STATE state){
  if(!findTiger(id)){
    return false;
  }
  
  Tiger* tiger = getTiger(id);
  tiger->m_state = state;

  return true;
}

void Streak::removeDead(){
  deadHelper(m_root);
}

// Helper function
void Streak::deadHelper(Tiger* root){
  if(root->m_left != nullptr){
    deadHelper(root->m_left);
  }
  if(root->m_right != nullptr){
    deadHelper(root->m_left);
  }
  if(root->m_state == DEAD){
    remove(root->m_id);
  }
}

bool Streak::findTiger(int id) const {
  Tiger* curr = m_root;

  while(curr != nullptr){
    if(id < curr->m_id){
      curr = curr->m_left;
    }else if(id > curr->m_id){
      curr = curr->m_right;
    }else if(id == curr->m_id){
      return true;
    }
  }

  return false;
}

int Streak::count(AGE age) const{
  return countAge(m_root, age);
}

int Streak::count(STATE state) const{
  return countState(m_root, state);
}

int Streak::countAge(Tiger* root, AGE age) const{
  if(root->m_left != nullptr){
    if(root->m_age == age){
      return countAge(root->m_left, age) + 1;
    }else{
      return countAge(root->m_left, age);
    }
  }
  if(root->m_right != nullptr){
    if(root->m_age == age){
      return countAge(root->m_right, age) + 1;
    }else{
      return countAge(root->m_right, age);
    }
  }
  
  if(root->m_age == age){
    return 1;
  }else{
    return 0;
  }
}

int Streak::countState(Tiger* root, STATE state) const{
  if(root->m_left != nullptr){
    if(root->m_state == state){
      return countState(root->m_left, state) + 1;
    }else{
      return countState(root->m_left, state);
    }
  }
  if(root->m_right != nullptr){
    if(root->m_state == state){
      return countState(root->m_right, state) + 1;
    }else{
      return countState(root->m_right, state);
    }
  }

  if(root->m_state == state){
    return 1;
  }else{
    return 0;
  }
}

void Streak::dumpTree() const {dump(m_root);}
void Streak::dump(Tiger* aTiger) const{
  if (aTiger != nullptr){
    cout << "(";
    dump(aTiger->m_left);//first visit the left child
    cout << aTiger->m_id << ":" << aTiger->m_height;//second visit the node itself
    dump(aTiger->m_right);//third visit the right child
    cout << ")";
  }
}

// Helper Function
Tiger* Streak::getTiger(int id){
  Tiger* curr = m_root;

  while(curr != nullptr){
    if(id < curr->m_id){
      curr = curr->m_left;
    }else if(id > curr->m_id){
      curr = curr->m_right;
    }else if(id == curr->m_id){
      return curr;
    }
  }

  return nullptr;
}

string Streak::getBranch(Tiger* tiger){
  string branch = "none";
  Tiger* parent = getParent(tiger, m_root);
  
  if(parent != nullptr){
    if(parent->m_left == tiger){
      branch = "left";
    }else if(parent->m_right == tiger){
      branch = "right";
    }
  }
  
  return branch;
}

//////////////////////////////////////////////////////////////////////
Grid::Grid(): m_root(nullptr){}

Grid::~Grid(){
  clear(m_root);
}

bool Grid::insert(int grid, Tiger tigers[], int population){
  // If the tree is empty, the first node is the root
  if(m_root == nullptr){
    m_root = new Streak(grid, tigers, population);
  }

  // If the node does not exist, it may be inserted
  else if(!findGrid(grid)){
    Streak* newStreak = new Streak(grid, tigers, population);

    // If the left branch of the root is empty, a lesser node becomes the new root
    if(m_root->m_left == nullptr && grid < m_root->m_gridID){
      Streak* former = m_root;
      newStreak->m_right = former;
      m_root = newStreak;
    }
    // If the right branch of the root is empty, a greater node becomes the new root 
    else if(m_root->m_right == nullptr && grid > m_root->m_gridID){
      Streak* former = m_root;
      newStreak->m_left = former;
      m_root = newStreak;
    }else{
      insertHelper(newStreak, m_root);
    }
  }
  
  return false;
}

int Grid::count(int grid, STATE state){
  if(!findGrid(grid)){
    return 0;
  }
  
  return m_root->count(state);
}

int Grid::count(int grid, AGE age){
  if(!findGrid(grid)){
    return 0;
  }

  return m_root->count(age);
}

bool Grid::removeTiger(int grid, int tiger, bool all){
  if(!findGrid(grid)){
    return false;
  }

  if(!all){
    m_root->remove(tiger);
  }else{
    m_root->removeDead();
  }
  
  return true;
}

int Grid::getGridHeight(int grid){
  if(!findGrid(grid)){
    return 0;
  }

  if(m_root == nullptr){
    return 0;
  }
  
  return heightHelper(m_root->m_left, m_root->m_right);
}

bool Grid::setState(int grid, int tiger, STATE state){
  if(!findGrid(grid)){
    return false;
  }

  m_root->setState(tiger, state);
  
  return true;
}

void Grid::dump(bool verbose) const{
  dumpHelper(m_root, verbose);
  cout << endl;
}

void Grid::dumpHelper(Streak* root, bool verbose) const{
  if (root != nullptr){
    {
      cout << "(";
      dumpHelper( root->m_left, verbose );
      if (verbose)
	cout << root->m_gridID << ":" << root->m_root->m_id;
      else
	cout << root->m_gridID;
      dumpHelper( root->m_right, verbose );
      cout << ")";
    }
  }
}

// Helper Functions

void Grid::insertHelper(Streak* streak, Streak* root){
  // If the given ID is less than that of the root's, insert left
  if(streak->m_gridID < root->m_gridID){
    if(root->m_left == nullptr){
      root->m_left = streak;
    }else{
      insertHelper(streak, root->m_left);
    }
  }
  
  // If the given ID is greater than that of the root's, insert right
  else if(streak->m_gridID > root->m_gridID){
    if(root->m_right == nullptr){
      root->m_right = streak;
    }else{
      insertHelper(streak, root->m_right);
    }
  }

  setRoot(streak, root);
}

bool Grid::findGrid(int id){
  if(m_root == nullptr){
    return false;
  }

  Streak* curr = m_root;

  while(curr->m_gridID != id){
    if(id < curr->m_gridID){
      curr = curr->m_left;
    }else if(id > curr->m_gridID){
      curr = curr->m_right;
    }
    if(curr == nullptr){
      return false;
    }
  }

  if(curr->m_gridID == id){
    return true;
  }else{
    return false;
  }
}

void Grid::setRoot(Streak* streak, Streak* root){
  if(m_root == streak){
    return;
  }
  
  Streak* parent = getParent(streak->m_gridID, m_root);
  Streak* grandparent = getParent(parent->m_gridID, m_root);
  Streak* ancestor = nullptr;
  
  while(m_root != streak){

    parent = getParent(streak->m_gridID, m_root);
    
    if(parent != nullptr){
      grandparent = getParent(parent->m_gridID, m_root);
    }
    
    if(grandparent != nullptr){
      ancestor = getParent(grandparent->m_gridID, m_root);
    }
    
    if(m_root == parent){
      if(m_root->m_left == streak){
	parent->m_left = streak->m_right;
	streak->m_right = parent;
	m_root = streak;
      }
      else if(m_root->m_right == streak){
	parent->m_right = streak->m_left;
	streak->m_left = parent;
	m_root = streak;
      }
      return;
    }

    // Left-Left
    else if(grandparent->m_left == parent && parent->m_left == streak){
      grandparent->m_left = parent->m_right;
      parent->m_left = streak->m_right;
      parent->m_right = grandparent;
      streak->m_right = parent;
    }

    // Left-Right
    else if(grandparent->m_left == parent && parent->m_right == streak){
      grandparent->m_left = streak->m_right;
      parent->m_right = streak->m_left;
      streak->m_left = parent;
      streak->m_right = grandparent;
    }

    // Right-Left
    else if(grandparent->m_right == parent && parent->m_left == streak){
      grandparent->m_right = streak->m_left;
      parent->m_left = streak->m_right;
      streak->m_right = parent;
      streak->m_left = grandparent;
    }

    // Right-Right
    else if(grandparent->m_right == parent && parent->m_right == streak){
      grandparent->m_right = parent->m_left;
      parent->m_right = streak->m_left;
      parent->m_left = grandparent;
      streak->m_left = parent;
    }

    
    if(m_root == grandparent){
      m_root = streak;
    }else{
      if(ancestor->m_left == grandparent){
	ancestor->m_left = streak;
      }else if(ancestor->m_right == grandparent){
	ancestor->m_right = streak;
      }
    }
    
    if(m_root == streak){
      return;
    }
  }
}

Streak* Grid::getParent(int id, Streak* root){
  if(id < root->m_gridID){
    if(root->m_left != nullptr){
      if(root->m_left->m_gridID == id){
	return root;
      }else{
	return getParent(id, root->m_left);
      }
    }
  }else if(id > root->m_gridID){
    if(root->m_right != nullptr){
      if(root->m_right->m_gridID == id){
	return root;
      }else{
	return getParent(id, root->m_right);
      }
    }
  }

  return nullptr;
}

void Grid::clear(Streak* root){
  if(root != nullptr){
    if(root->m_left != nullptr){
      clear(root->m_left);
    }
    if(root->m_right != nullptr){
      clear(root->m_right);
    }

    delete root;
    root = nullptr;
  }
}


int Grid::heightHelper(Streak* left, Streak* right){
  int left_h = 0;
  int right_h = 0;
  
  if(!left && !right){
    return 0;
  }

  if(left != nullptr){
    left_h = heightHelper(left->m_left, left->m_right) + 1;
  }
  if(right != nullptr){
    right_h = heightHelper(right->m_left, right->m_right) + 1;
  }

  if(left_h >= right_h){
    return left_h;
  }else{
    return right_h; 
  }
}
