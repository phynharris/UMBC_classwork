// UMBC - CSEE - CMSC 341 - Spring 2026 - Proj5
// Do not write your name or campus ID in files
#include "graph.h"

class Tester{ // Tester class to implement test functions
public:
  bool testOverloadedConstructor(Graph& graph, string dataFile);
  bool testEmptyGraph(Graph& graph);
  bool testManualInsertion(Graph& graph);
  bool testFindPathError(Graph& graph);
  bool testFindPathNorm(Graph& graph);
  bool testFindPathEdge(Graph& graph);
  bool testFindPathErrorNoStart(Graph& graph);
  bool testFindPathErrorNoEnd(Graph& graph);
  bool testAssignmentOperator(Graph& graph, string dataFile);
  
  // Bonus test cases
  bool testFindPathErrorOneNode(Graph& graph);
  bool testAssignmentOperatorEmpty(Graph& graph);
};

int main(){
  Tester tester;

  // Test normal case for the overloaded graph constructor
  {
    Graph graph("testdata.txt");

    cout << "\nTesting normal case for the overloaded graph constructor" << endl;
    if (tester.testOverloadedConstructor(graph, "testdata.txt")) {
      cout << "\tNormal case for the overloaded graph constructor passed!\n";
    } else {
      cout << "\tNormal case for the overloaded graph constructor failed!\n";
    }
  }

  // Test edge case for an empty graph object
  {
    Graph graph;

    cout << "\nTesting edge case for an empty graph object" << endl;
    if (tester.testEmptyGraph(graph)) {
      cout << "\tEdge case for an empty graph object passed!\n";
    } else {
      cout << "\tEdge case for an empty graph object failed!\n";
    }
  }

  // Test normal case for manual node insertion
  {
    Graph graph;

    cout << "\nTesting normal case for manual node insertion" << endl;
    if (tester.testManualInsertion(graph)) {
      cout << "\tNormal case for manual node insertion passed!\n";
    } else {
      cout << "\tNormal case for manual node insertion failed!\n";
    }
  }
  
  // Test error case for findPath — path does not exist
  {
    Graph graph("testdata.txt");

    cout << "\nTesting error case for findPath — path does not exist" << endl;
    if (tester.testFindPathError(graph)) {
      cout << "\tError case for findPath passed!\n";
    } else {
      cout << "\tError case for findPath failed!\n";
    }
  }

  // Test normal case for findPath
  {
    Graph graph("testdata.txt");

    cout << "\nTesting normal case for findPath" << endl;
    if (tester.testFindPathNorm(graph)) {
      cout << "\tNormal case for findPath passed!\n";
    } else {
      cout << "\tNormal case for findPath failed!\n";
    }
  }

  // Test edge case for findPath — start and end are the same node
  {
    Graph graph("testdata.txt");

    cout << "\nTesting edge case for findPath — start and end are the same node" << endl;
    if (tester.testFindPathEdge(graph)) {
      cout << "\tEdge case for findPath passed!\n";
    } else {
      cout << "\tEdge case for findPath failed!\n";
    }
  }

  // Test error case for findPath — start node does not exist
  {
    Graph graph("testdata.txt");

    cout << "\nTesting error case for findPath — start node does not exist" << endl;
    if (tester.testFindPathErrorNoStart(graph)) {
      cout << "\tError case for findPath (no start) passed!\n";
    } else {
      cout << "\tError case for findPath (no start) failed!\n";
    }
  }

  // Test error case for findPath — end node does not exist
  {
    Graph graph("testdata.txt");

    cout << "\nTesting error case for findPath — end node does not exist" << endl;
    if (tester.testFindPathErrorNoEnd(graph)) {
      cout << "\tError case for findPath (no end) passed!\n";
    } else {
      cout << "\tError case for findPath (no end) failed!\n";
    }
  }

  // Test normal case for the overloaded assignment operator
  {
    Graph graph("testdata.txt");

    cout << "\nTesting normal case for the overloaded assignment operator" << endl;
    if (tester.testAssignmentOperator(graph, "testdata.txt")) {
      cout << "\tNormal case for the overloaded assignment operator passed!\n";
    } else {
      cout << "\tNormal case for the overloaded assignment operator failed!\n";
    }
  }

  // Bonus test cases
  // Test error case for findPath — graph has one node and no connections
  {
    Graph graph;

    cout << "\nTesting error case for findPath — one node, no connections" << endl;
    if (tester.testFindPathErrorOneNode(graph)) {
      cout << "\tError case for findPath (one node) passed!\n";
    } else {
      cout << "\tError case for findPath (one node) failed!\n";
    }
  }

  // Test edge case for assignment operator — copying an empty graph
  {
    Graph graph;

    cout << "\nTesting edge case for assignment operator — copying an empty graph" << endl;
    if (tester.testAssignmentOperatorEmpty(graph)) {
      cout << "\tEdge case for assignment operator (empty graph) passed!\n";
    } else {
      cout << "\tEdge case for assignment operator (empty graph) failed!\n";
    }
  }

  return 0;
}

// Test normal case for the overloaded graph constructor
bool Tester::testOverloadedConstructor(Graph& graph, string dataFile) {
  int numNodes;
  int node, n, e, s, w;
  ifstream file;
  file.open(dataFile);

  if (!file.is_open()) return false;

  file >> numNodes;

  // Check that the number of nodes is correct
  if (graph.getNumNodes() != numNodes) return false;

  // For each line, verify the node exists and its connections are correct
  for (int i = 0; i < numNodes; i++) {
    file >> node >> n >> e >> s >> w;

    Node* current = graph.findNode(node);

    // Check that the node exists
    if (current == nullptr) return false;

    // Check each directional connection
    if (n == -1 && current->getNorth() != nullptr) return false;
    if (n != -1 && (current->getNorth() == nullptr ||
		    current->getNorth()->getValue() != n)) return false;

    if (e == -1 && current->getEast() != nullptr) return false;
    if (e != -1 && (current->getEast() == nullptr ||
		    current->getEast()->getValue() != e)) return false;

    if (s == -1 && current->getSouth() != nullptr) return false;
    if (s != -1 && (current->getSouth() == nullptr ||
		    current->getSouth()->getValue() != s)) return false;

    if (w == -1 && current->getWest() != nullptr) return false;
    if (w != -1 && (current->getWest() == nullptr ||
		    current->getWest()->getValue() != w)) return false;
  }

  file.close();
  return true;
}

// Test edge case for an empty graph object
bool Tester::testEmptyGraph(Graph& graph) {
  // Check that the graph is empty and member variables are properly initialized
  return graph.empty() &&
    graph.getNumNodes() == 0 &&
    graph.m_head == nullptr;
}

// Test normal case for manual node insertion
bool Tester::testManualInsertion(Graph& graph) {
  // Manually insert 50 nodes with some connections
  for (int i = 1; i <= 50; i++) {
    // Connect each node to its neighbors in a chain
    // north: i-2, east: i+1, south: i+2, west: i-1
    int n = (i - 2 >= 1)  ? i - 2 : -1;
    int e = (i + 1 <= 50) ? i + 1 : -1;
    int s = (i + 2 <= 50) ? i + 2 : -1;
    int w = (i - 1 >= 1)  ? i - 1 : -1;
    graph.insert(i, n, e, s, w);
    graph.m_numNodes++;
  }
  
  // Check that all 50 nodes exist
  if (graph.getNumNodes() != 50) return false;

  // Check that each node exists and its connections are correct
  for (int i = 1; i <= 50; i++) {
    Node* current = graph.findNode(i);
    if (current == nullptr) return false;

    // Verify directional connections
    int n = (i - 2 >= 1)  ? i - 2 : -1;
    int e = (i + 1 <= 50) ? i + 1 : -1;
    int s = (i + 2 <= 50) ? i + 2 : -1;
    int w = (i - 1 >= 1)  ? i - 1 : -1;

    if (n == -1 && current->getNorth() != nullptr) return false;
    if (n != -1 && (current->getNorth() == nullptr ||
		    current->getNorth()->getValue() != n)) return false;

    if (e == -1 && current->getEast() != nullptr) return false;
    if (e != -1 && (current->getEast() == nullptr ||
		    current->getEast()->getValue() != e)) return false;
    
    if (s == -1 && current->getSouth() != nullptr) return false;
    if (s != -1 && (current->getSouth() == nullptr ||
		    current->getSouth()->getValue() != s)) return false;

    if (w == -1 && current->getWest() != nullptr) return false;
    if (w != -1 && (current->getWest() == nullptr ||
		    current->getWest()->getValue() != w)) return false;
  }

  return true;
}

// Test error case for findPath — path does not exist
bool Tester::testFindPathError(Graph& graph) {
  // Node 3 has no outgoing connections in testdata.txt, so no path can exist from 3 to 13
  int start = 3;
  int end = 13;
  return graph.findPath(start, end) == false;
}

// Test normal case for findPath
bool Tester::testFindPathNorm(Graph& graph) {
  // A path from node 0 to node 14 is known to exist in testdata.txt
  // 0 -> 4 -> 5 -> 1 -> 2 -> 6 -> 7 -> 11 -> 15 -> 14
  int start = 0;
  int end = 14;
  return graph.findPath(start, end) == true;
}

// Test edge case for findPath — start and end are the same node
bool Tester::testFindPathEdge(Graph& graph) {
  // A path from a node to itself should always return true
  int start = 0;
  int end = 0;
  return graph.findPath(start, end) == true;
}

// Test error case for findPath — start node does not exist
bool Tester::testFindPathErrorNoStart(Graph& graph) {
// Node 999 does not exist in testdata.txt, so findPath should return false
int start = 999;
int end = 0;
return graph.findPath(start, end) == false;
}

// Test error case for findPath — end node does not exist
bool Tester::testFindPathErrorNoEnd(Graph& graph) {
  // Node 999 does not exist in testdata.txt, so findPath should return false
  int start = 0;
  int end = 999;
  return graph.findPath(start, end) == false;
}

// Test normal case for the overloaded assignment operator
bool Tester::testAssignmentOperator(Graph& graph, string dataFile) {
  // Create a deep copy of the graph
  Graph copy;
  copy = graph;

  // Check that the number of nodes is the same
  if (copy.getNumNodes() != graph.getNumNodes()) return false;

  // Re-read the data file to verify both graphs have the same structure
  int numNodes;
  int node, n, e, s, w;
  ifstream file;
  file.open(dataFile);

  if (!file.is_open()) return false;

  file >> numNodes;

  for (int i = 0; i < numNodes; i++) {
    file >> node >> n >> e >> s >> w;

    Node* origNode = graph.findNode(node);
    Node* copyNode = copy.findNode(node);

    // Both nodes must exist
    if (origNode == nullptr || copyNode == nullptr) return false;

    // They must have different pointers
    if (origNode == copyNode) return false;

    // Verify north connections
    if (n == -1) {
      if (copyNode->getNorth() != nullptr) return false;
    } else {
      if (copyNode->getNorth() == nullptr) return false;
      if (copyNode->getNorth()->getValue() != n) return false;
      if (copyNode->getNorth() == origNode->getNorth()) return false;
    }

    // Verify east connections
    if (e == -1) {
      if (copyNode->getEast() != nullptr) return false;
    } else {
      if (copyNode->getEast() == nullptr) return false;
      if (copyNode->getEast()->getValue() != e) return false;
      if (copyNode->getEast() == origNode->getEast()) return false;
    }

    // Verify south connections
    if (s == -1) {
      if (copyNode->getSouth() != nullptr) return false;
    } else {
      if (copyNode->getSouth() == nullptr) return false;
      if (copyNode->getSouth()->getValue() != s) return false;
      if (copyNode->getSouth() == origNode->getSouth()) return false;
    }

    // Verify west connections
    if (w == -1) {
      if (copyNode->getWest() != nullptr) return false;
    } else {
      if (copyNode->getWest() == nullptr) return false;
      if (copyNode->getWest()->getValue() != w) return false;
      if (copyNode->getWest() == origNode->getWest()) return false;
    }
  }

  file.close();
  return true;
}

// Bonus test cases
// Test error case for findPath — graph has one node and no connections
bool Tester::testFindPathErrorOneNode(Graph& graph) {
  // Insert a single node with no connections
  graph.insert(0, -1, -1, -1, -1);
  graph.m_numNodes++;

  // A graph with one node and no connections should not find a path to any other node
  int start = 0;
  int end = 1;
  return graph.findPath(start, end) == false;
}

// Test edge case for assignment operator — copying an empty graph
bool Tester::testAssignmentOperatorEmpty(Graph& graph) {
  // Copying an empty graph should produce another empty graph with different pointers
  Graph copy;
  copy = graph;

  // Both should be empty and have the same number of nodes
  if (!copy.empty()) return false;
  if (copy.getNumNodes() != graph.getNumNodes()) return false;

  // They should be distinct objects
  if (&copy == &graph) return false;

  return true;
}
