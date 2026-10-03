// UMBC - CSEE - CMSC 341 - Spring 2026 - Proj5
// Do not write your name or campus ID in files
#include "graph.h"

// Default constructor — initializes an empty graph
Graph::Graph(){
  m_numNodes = 0;
  m_head = nullptr;
  m_dataFile = "";
}

// Overloaded constructor — initializes member variables and loads graph data from file
Graph::Graph(string dataFile){
  m_numNodes = 0;
  m_head = nullptr;
  m_dataFile = dataFile;
  loadData();
}

// Destructor — frees all dynamically allocated nodes
Graph::~Graph(){
  clearGraph();
}

void Graph::loadData(){
  int numNodes;
  int node, n, e, s, w;
  ifstream dataFile;
  dataFile.open(m_dataFile);
  if (dataFile.is_open()) {
    dataFile >> numNodes;
    m_numNodes = numNodes;
    for (int i = 0; i < numNodes; i++) {
      dataFile >> node >> n >> e >> s >> w;
      insert(node, n, e, s, w);
    }
  }
  else
    //the following statement provides the reason if a file doesn't open
    //please note: not all platforms are providing the same message
    cerr << "Error: " << strerror(errno) << endl;
}

// Finds or creates the main node, then wires up its directional neighbors
void Graph::insert(int node, int n, int e, int s, int w){
  // Find or create the main node
  Node* mainNode = findNode(node);
  if (mainNode == nullptr) {
    mainNode = new Node(node);
    insertAtHead(mainNode);
  }

  // Store neighbor values and their corresponding setters in parallel arrays
  int neighborValues[4] = {n, e, s, w};
  void (Node::*setters[4])(Node*) = {
    &Node::setNorth,
    &Node::setEast,
    &Node::setSouth,
    &Node::setWest
  };

  // For each direction, find or create the neighbor node and wire it up
  for (int i = 0; i < 4; i++) {
    if (neighborValues[i] == -1) continue;

    Node* neighbor = findNode(neighborValues[i]);
    if (neighbor == nullptr) {
      neighbor = new Node(neighborValues[i]);
      insertAtHead(neighbor);
    }
    (mainNode->*setters[i])(neighbor);
  }
}

// Inserts a node at the head of the linked list
void Graph::insertAtHead(Node * aNode){
  aNode->setNext(m_head);
  m_head = aNode;
}

// Traverses the linked list and returns a pointer to the node with the matching value, or nullptr if not found
Node * Graph::findNode(int nodeValue){
  Node* current = m_head;
  while (current != nullptr) {
    if (current->getValue() == nodeValue)
      return current;
    current = current->getNext();
  }
  return nullptr;
}

// Public entry point — sets up and initiates the recursive DFS search
bool Graph::findPath(int start, int end){
  clearResult();
  clearVisited();

  Node* startNode = findNode(start);
  if (startNode == nullptr) return false;

  return findPath(startNode, end);
}

// Recursive DFS helper — visits nodes, records path, and backtracks on dead ends
bool Graph::findPath(Node* aNode, int end){
  // If this node has already been visited, backtrack
  if (aNode->getVisited()) return false;

  // Mark as visited and record in path
  aNode->setVisited(true);
  m_path.push(aNode->getValue());

  // Base case — destination reached
  if (aNode->getValue() == end) return true;

  // Try all four directions
  Node* neighbors[4] = {
    aNode->getNorth(),
    aNode->getEast(),
    aNode->getSouth(),
    aNode->getWest()
  };

  for (int i = 0; i < 4; i++) {
    if (neighbors[i] != nullptr) {
      if (findPath(neighbors[i], end)) return true;
    }
  }

  // All connections exhausted — backtrack
  m_path.pop();
  return false;
}

// Prints the path found from start to end in the correct order
void Graph::dump() {
  // Transfer stack contents to a temporary stack to reverse the order
  stack<int> temp;
  while (!m_path.empty()) {
    temp.push(m_path.top());
    m_path.pop();
  }

  // Print the path in order, or just END if no path was found
  while (!temp.empty()) {
    cout << temp.top() << " => ";
    temp.pop();
  }
  cout << "END" << endl;
}

// Clears the stack storing the path result
void Graph::clearResult(){
  while (!m_path.empty())
    m_path.pop();
}

// Resets the visited flag of all nodes
void Graph::clearVisited(){
  Node* current = m_head;
  while (current != nullptr) {
    current->setVisited(false);
    current = current->getNext();
  }
}

// Clears the existing graph and builds a new one from the provided file
void Graph::buildGraph(string file){
  clearGraph();
  m_dataFile = file;
  loadData();
}

// Deletes all dynamically allocated nodes and resets all member variables
void Graph::clearGraph(){
  Node* current = m_head;
  while (current != nullptr) {
    Node* next = current->getNext();
    delete current;
    current = next;
  }

  m_head = nullptr;
  m_numNodes = 0;
  m_dataFile = "";
  clearResult();
}

// Overloaded assignment operator — creates a deep copy of the rhs graph
const Graph & Graph::operator=(const Graph & rhs){
  // Self-assignment check
  if (this == &rhs) return *this;

  // Clear existing graph
  clearGraph();

  // Copy member variables
  m_numNodes = rhs.m_numNodes;
  m_dataFile = rhs.m_dataFile;

  // Rebuild the graph from the same data file
  loadData();

  return *this;
}

bool Graph::empty() const// is the list empty?
{ return m_head == nullptr; }

// Helper functions

int Graph::getNumNodes() const {
  return m_numNodes;
}
