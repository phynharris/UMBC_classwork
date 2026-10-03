// CMSC 341 - Spring 2026 - Project 3
#include "shop.h"

// Create empty object
Shop::Shop(){
  m_heapType = NOTYPE;
  m_structure = NOSTRUCT;
  m_regPrior = 0;
  m_shopID = 0;
  m_heap = nullptr;
  m_size = 0;
}

// Create Shop objects
Shop::Shop(prifn_t priFn, HEAPTYPE heapType,
	   STRUCTURE structure, int regPrior,
	   int id)
{
  m_priorFunc = priFn;
  m_heapType = heapType;
  m_structure = structure;
  m_regPrior = regPrior;
  m_shopID = id;
  m_heap = nullptr;
  m_size = 0;
}

// Empty the shop
Shop::~Shop()
{
  clear();
}

// Call function to recursively clear the shop
void Shop::clear() {
  clearHelper(m_heap);
  m_heap = nullptr;
  m_size = 0;
}

// Create a copy of a shop
Shop::Shop(const Shop& rhs)
{
  // Set members equal
  m_priorFunc = rhs.m_priorFunc;
  m_heapType = rhs.m_heapType;
  m_structure = rhs.m_structure;
  m_regPrior = rhs.m_regPrior;
  m_shopID = rhs.m_shopID;

  // Default m_heap and size
  m_heap = nullptr;
  m_size = 0;

  // Function copies nodes into current heap
  copyHelper(rhs.m_heap, m_heap);
}

// Copy a shop into another shop
Shop& Shop::operator=(const Shop& rhs) {
  // If the two shops are the same, return
  if(&rhs == this){
    return *this;
  }

  // Clear the first shop
  clear();

  // Set members equal to the right side
  m_priorFunc = rhs.m_priorFunc;
  m_heapType = rhs.m_heapType;
  m_structure = rhs.m_structure;
  m_regPrior = rhs.m_regPrior;
  m_shopID = rhs.m_shopID;

  // Default m_heap and size
  m_heap = nullptr;
  m_size = 0;

  // Function copies nodes into current heap
  copyHelper(rhs.m_heap, m_heap);

  return *this;
}

// Merges two queues if the same types together
void Shop::mergeWithQueue(Shop& rhs) {
  // If the heapTypes are incompatible, throw domain_error
  if(rhs.m_heapType != m_heapType || rhs.m_priorFunc != m_priorFunc){
    throw domain_error("Incompatible heapTypes");
  }

  // If the structures are incompatible, throw domain_error
  if(rhs.m_structure != m_structure){
    throw domain_error("Incompatible structure");
  }

  // If heaptype is not defined, return
  if(m_heapType == NOTYPE || rhs.m_heapType == NOTYPE){
    return;
  }

  // If structure is not defined, return
  if(m_structure == NOSTRUCT || rhs.m_structure == NOSTRUCT){
    return;
  }

  // If the rhs has nodes, reinsert them into the main heap
  if(rhs.m_heap){
    reinsert(rhs.m_heap);
    rhs.m_heap = nullptr;
  }
}

// Insert new orders into a shop
bool Shop::insertOrder(const Order& order) {
  // If invalid customer ID, false
  if(order.m_customerID < 0){
    return false;
  }

  // If invalid order ID, false;
  if(order.m_orderID < 0){
    return false;
  }

  // If invaid order quantity, false
  if(order.m_count < 0){
    return false;
  }  

  // Create a new Order and insert it
  Order* newOrder = new Order(order);
  if(m_size == 0){
    // If heap is empty, new order becomes the root
    m_heap = newOrder;
  }else{
    if(m_structure == SKEW){
      mergeSkew(m_heap, newOrder);
    }else if(m_structure == LEFTIST){
      mergeLeftist(m_heap, newOrder);
    }
  }

  ++m_size;

  return true;
}

// Return number of orders in queue
int Shop::numOrders() const{
  return m_size;
}

// Return the priority function
prifn_t Shop::getPriorityFn() const {
  return m_priorFunc;
}

// Dequeue the order with the highest priority
Order Shop::getNextOrder() {
  // If heap is empty, throw out_of_range
  if(!m_heap){
    throw out_of_range("Heap is empty.");
  }
  
  Order nextOrder = *m_heap;        // Highest priority order
  Order* left = m_heap->m_left;     // Left child of HPO
  Order* right = m_heap->m_right;   // Right child of HPO, to be reinserted
  
  // If there is only one node (the root), remove it and return it
  if(numOrders() == 1){
    clear();
    --m_size;
    return nextOrder;
  }
  // Rebalance tree by reinserting the right side
  else{
    m_size -= 1;
    delete m_heap;
    m_heap = left;
    rebalance(right);
  }
  
  return nextOrder;
}

// Change the priority of a shop
void Shop::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
  // If either the heapType or PriorityFn are the same, return
  if(heapType == m_heapType || priFn == m_priorFunc){
    return;
  }

  // If heapType is invalid, return
  if(heapType != MAXHEAP && heapType != MINHEAP){
    return;
  }

  // Disassociate the heap from its nodes and reconfigure members
  Order* oldHeap = m_heap;
  m_heap = nullptr;
  m_heapType = heapType;
  m_priorFunc = priFn;
  m_size = 0;

  // Reinsert nodes
  reinsert(oldHeap);
  oldHeap = nullptr;
}

// Change structure of heap
void Shop::setStructure(STRUCTURE structure){
  // If the structure is the same, return
  if(structure == m_structure){
    return;
  }

  // If structure is invalid, return
  if(structure != SKEW && structure != LEFTIST){
    return;
  }

  // Disassociate the heap from its nodes and reconfigure members
  Order* oldHeap = m_heap;
  m_heap = nullptr;
  m_structure = structure;
  m_size = 0;

  // Reinsert nodes
  reinsert(oldHeap);
  oldHeap = nullptr;
}

// Return the heapType
HEAPTYPE Shop::getHeapType() const {
  return m_heapType;
}

// Return the structure
STRUCTURE Shop::getStructure() const {
  return m_structure;
}

// Print orders in the queue
void Shop::printOrdersQueue() const {
  printHelper(m_heap);
}

void Shop::dump() const {
  if (m_size == 0) {
    cout << "Empty heap.\n" ;
  } else {
    cout << "Shop " << m_regPrior << ": => ";
    dump(m_heap);
  }
  cout << endl;
}
void Shop::dump(Order *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    if (m_structure == SKEW)
      cout << m_priorFunc(*pos) << ":" << pos->m_orderID;
    else
      cout << m_priorFunc(*pos) << ":" << pos->m_orderID << ":" << pos->m_npl;
    dump(pos->m_right);
    cout << ")";
  }
}

ostream& operator<<(ostream& sout, const Order& order) {
  sout << "Order ID: " << order.getOrderID()
       << ", item: " << order.getItem()
       << ", count: " << order.getCount();
  return sout;
}

// Shop Helper Functions
// Helper function that merges two leftist heaps
Order* Shop::mergeLeftist(Order* h1, Order* h2){
  // If h1 is null, return h2
  if(!h1){
    return h2;
  }

  // If h2 is null, return h1
  if(!h2){
    return h1;
  }

  Order* temp;   // Dummy order

  // If max heap and priorities are invalid swap h1 and h2
  if(m_heapType == MAXHEAP && m_priorFunc(*h1) < m_priorFunc(*h2)){
    if(h1 == m_heap){
      m_heap = h2;
    }

    temp = h1;
    h1 = h2;
    h2 = temp;
  }
  // If min heap and priorities are invalid swap h1 and h2
  else if(m_heapType == MINHEAP && m_priorFunc(*h1) > m_priorFunc(*h2)){
    if(h1 == m_heap){
      m_heap = h2;
    }

    temp = h1;
    h1 = h2;
    h2 = temp;
  }

  // Merge right child of h1 with h2
  h1->m_right = mergeLeftist(h1->m_right, h2);

  // If the left side has a smaller npl than the right, swap them
  if(h1->m_left == nullptr || h1->m_left->m_npl < h1->m_right->m_npl){
    temp = h1->m_left;
    h1->m_left = h1->m_right;
    h1->m_right = temp;
  }

  // Set NPL for each node
  if(!(h1->m_left) || !(h1->m_right)){
    h1->m_npl = 0;
    }
  else if(h1->m_right){
    h1->m_npl = 1 + h1->m_right->m_npl;
  }
  
  return h1;
}

// Helper function that merges two skew heaps
Order* Shop::mergeSkew(Order* h1, Order* h2){
  if(!h1){
    return h2;
  }

  if(!h2){
    return h1;
  }

  Order* temp;  // Dummy order

  // If max heap and priorities are invalid swap h1 and h2
  if(m_heapType == MAXHEAP && m_priorFunc(*h1) < m_priorFunc(*h2)){
    if(h1 == m_heap){
      m_heap = h2;
    }
    
    temp = h1;
    h1 = h2;
    h2 = temp;
  }
  // If max heap and priorities are invalid swap h1 and h2
  else if(m_heapType == MINHEAP && m_priorFunc(*h1) > m_priorFunc(*h2)){
    if(h1 == m_heap){
      m_heap = h2;
    }
    
    temp = h1;
    h1 = h2;
    h2 = temp;
  }

  // Merge right child of h1 with h2
  h1->m_right = mergeSkew(h1->m_right, h2);

  // Swap h1 and h2
  temp = h1->m_left;
  h1->m_left = h1->m_right;
  h1->m_right = temp;
  
  return h1;
}

// Helper function that recursively clears heap
void Shop::clearHelper(Order* &root){
  if(root != nullptr){
    clearHelper(root->m_left);
    clearHelper(root->m_right);
    delete root;
    root = nullptr;
  }
}

// Helper function that recursively copies a heap
void Shop::copyHelper(Order* root, Order* &newRoot){
  if(root){
    // If the heap is empty
    if(m_size == 0){
      // Create a node from the root of the original heap
      Order* order = new Order(*root);
      m_heap = order;
      newRoot = m_heap;
      m_heap->m_left = nullptr;
      m_heap->m_right = nullptr;
      m_size++;
    }

    // If newRoot has nodes (if the original root wasn't empty)
    if(newRoot){
      newRoot->m_left = nullptr;
      newRoot->m_right = nullptr;

      // If og root has a left child, create the same node in newRoot
      if(root->m_left){
	Order* orderLeft = new Order(*(root->m_left));
	orderLeft->m_right = nullptr;
	orderLeft->m_left = nullptr;
	newRoot->m_left = orderLeft;
	m_size++;
      }

      // If og root has a right child, create the same node in newRoot
      if(root->m_right){
	Order* orderRight = new Order(*(root->m_right));
	orderRight->m_right = nullptr;
	orderRight->m_left = nullptr;
	newRoot->m_right = orderRight;
	m_size++;
      }

      // Recurse the function with the root's children
      copyHelper(root->m_left, newRoot->m_left);
      copyHelper(root->m_right, newRoot->m_right);
    }
  }
}

// Recursively prints out order information
void Shop::printHelper(Order* root) const{
  if(root){
    cout << "[" << m_priorFunc(*root) << "]"
	 << " Order ID: " << root->getOrderID()
	 << ", item: " << root->getItemString()
	 << ", count: " << root->getCountString() << endl;
    printHelper(root->m_left);
    printHelper(root->m_right);
  }
}

// Recursively rebalance the heap (after dequeueing)
void Shop::rebalance(Order* root){
  if(root){
    // Create duplicate nodes from the left and right children of root and reset NPL
    Order* left = root->m_left;
    Order* right = root->m_right;
    root->m_left = nullptr;
    root->m_right = nullptr;
    root->m_npl = 0;

    // If the heap is empty, node becomes the root
    if(!m_heap){
      m_heap = root;
    }
    // If the heap is not empty, merge the node appropriately
    else{
      if(m_structure == SKEW){
	mergeSkew(m_heap, root);
      }else{
	mergeLeftist(m_heap, root);
      }
    }

    // Recurse with the left and right nodes
    rebalance(left);
    rebalance(right);
  }
}

// Recursively reinsert nodes into a heap
void Shop::reinsert(Order* root){
  if(root){
    // Create duplicate nodes from the left and right children of root and reset NPL
    Order* left = root->m_left;
    Order* right = root->m_right;
    root->m_npl = 0;
    root->m_left = nullptr;
    root->m_right = nullptr;

    // If the heap is empty, node becomes the root—increase size of heap
    if(!m_heap){
      ++m_size;
      m_heap = root;
    }
    // If the heap is not empty, merge the node appropriately—incease size of heap
    else{
      ++m_size;
      if(m_structure == SKEW){
	mergeSkew(m_heap, root);
      }else{
	mergeLeftist(m_heap, root);
      }
    }

    // Recurse with the left and right nodes
    reinsert(left);
    reinsert(right);
  }
}


//////////////////////////////////////////////////////////////

// Constructor for region
Region::Region(int size){
  m_heap = new Shop[size]{};
  m_capacity = size;
  m_size = 0;
}

// Clear region
Region::~Region(){  
  //delete[] m_heap;
  m_heap = nullptr;
}

// Add a shop into region
bool Region::addShop(Shop & aShop){
  // If the size is less than the max capacity minus one, add a new node
  if(m_size < m_capacity - 1){
    m_heap[m_size + ROOTINDEX] = aShop;
    bubbleUp(aShop, m_size + ROOTINDEX);
    m_size++;
    return true;
  }else{
    return false;
  }
}

// Dequeue the shop with the highest priority
bool Region::getShop(Shop & aShop){
  // If there are nodes, dequeue the highest node
  if(m_size > 0){
    aShop = m_heap[ROOTINDEX];
    m_heap[ROOTINDEX] = m_heap[m_size];
    m_heap[m_size] = aShop;
    --m_size;
    // If there is more than one node after dequeueing, bubble the shop down
    if(m_size > 1){
      bubbleDown(m_heap[ROOTINDEX], ROOTINDEX);
    }
    return true;
  }
  
  return false;
}

// Dequeue shops until the nth shop (inclusive)
bool Region::getNthShop(Shop & aShop, int n){
  // If there is no nth shop, return
  if(n > m_size){
    return false;
  }

  // Dequeue each shop and test if it is a success
  bool success = true;
  for(int i = 0; i < n; i++){
    success = getShop(m_heap[ROOTINDEX]);
    if(!success){
      return false;
    }
  }
  
  return true;
}

// Set priority function for a shop
bool Region::setPriorityFn(prifn_t priFn, HEAPTYPE heapType, int n){
  // If the nth shop does not exist, return false;
  if(n > m_size){
    return false;
  }

  // Create an array of shops of size n to store the other queues
  Shop shop[n];
  bool success = true;

  // Store each shop before the nth in an array
  for(int i = ROOTINDEX; i < n; i++){
    shop[i] = m_heap[i];
    getShop(m_heap[ROOTINDEX]);
  }

  // Check if the heapType can be changed
  if(m_heap[ROOTINDEX].m_heapType == heapType || m_heap[ROOTINDEX].m_priorFunc == priFn){
    success = false;
  }

  // Change the heap if it can be
  if(success){
    m_heap[ROOTINDEX].setPriorityFn(priFn, heapType);
  }

  // Reinsert the heaps back into the region
  for(int i = ROOTINDEX; i < n; i++){
    m_heap[i] = shop[i];
  }

  return success;
}

// Set stucture function for a shop
bool Region::setStructure(STRUCTURE structure, int n){
  // If the nth shop does not exist, return false;
  if(n > m_size){
    return false;
  }

  // Create an array of shops of size n to store the other queues
  Shop shop[n];
  bool success = true;

  // Store each shop before the nth in an array
  for(int i = ROOTINDEX; i < n; i++){
    shop[i] = m_heap[i];
    getShop(m_heap[ROOTINDEX]);
  }

  // Check if the heapType can be changed
  if(m_heap[ROOTINDEX].m_structure == structure){
    success = false;
  }

  // Change the heap if it can be
  if(success){
    m_heap[ROOTINDEX].setStructure(structure);
  }

  // Reinsert the heaps back into the region
  for(int i = ROOTINDEX; i < n; i++){
    m_heap[i] = shop[i];
  }

  return success;
}

// Get an order from the highest priority shop
bool Region::getOrder(Order & order){
  // If the heap is empty, false
  if(m_size <= 0){
    return false;
  }

  // Dequeue all empty queues until a nonempty queue is reached
  while(m_heap[ROOTINDEX].m_heap == nullptr){
    getShop(m_heap[ROOTINDEX]);

    // If the heap is cleared, return false 
    if(m_size <= 0){
      return false;
    }
  }

  // Clear the highest priority order from the highest priority shop
  m_heap[ROOTINDEX].getNextOrder();
  
  return true;
}

void Region::dump(){
  dump(ROOTINDEX);
  cout << endl;
}

void Region::dump(int index){
  if (index <= m_size){
    cout << "(";
    dump(index*2);
    cout << m_heap[index].m_regPrior;
    dump(index*2 + 1);
    cout << ")";
  }
}

// Helper Functions

// Gets the parent of a Shop based on its index
int Region::getParent(int index){
  if(index > ROOTINDEX){

    // If the index is even
    if(index % 2 == 0){
      return index/2;
    }

    // If the index is odd
    if(index % 2 == 1){
      return (index - 1)/2;
    }
  }

  return index;
}

// Bubbles a node upward in the heap
void Region::bubbleUp(Shop &shop, int index){
  // Get parent info
  int parentIndex = getParent(index);
  Shop parent = m_heap[parentIndex];

  // If the parent has a larger priority, swap the parent and the child
  if(parent.m_regPrior > shop.m_regPrior){
    m_heap[parentIndex] = shop;
    m_heap[index] = parent;

    // Continue bubbling up
    bubbleUp(shop, parentIndex);
  }
}

// Bubbles a node downward in the heap
void Region::bubbleDown(Shop shop, int index){
  // Gets children info
  Shop leftChild;
  Shop rightChild;
  int leftChildI = index * 2;
  int rightChildI = index * 2 + 1;

  // If the left child doesn't exist, return
  if(leftChildI <= m_size){
    leftChild = m_heap[leftChildI];
  }else{
    return;
  }

  // If the right child doesn't exist, bubble down with the left child
  if(rightChildI <= m_size){
    rightChild = m_heap[rightChildI];
  }else{
    m_heap[leftChildI] = shop;
    m_heap[index] = leftChild;
    bubbleDown(shop, leftChildI);
  }

  // Bubble down with the l/r child based on their priority
  if(leftChild.m_regPrior >= rightChild.m_regPrior){
    m_heap[rightChildI] = shop;
    m_heap[index] = rightChild;
    bubbleDown(shop, rightChildI);
  }else{
    m_heap[leftChildI] = shop;
    m_heap[index] = leftChild;
    bubbleDown(shop, leftChildI);
  }
}
