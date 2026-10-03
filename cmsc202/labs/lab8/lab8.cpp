//Title:  Lab 8 - Debugging
//Author: AJ Boyd
//Course: CMSC 202
//Desc:   For this lab, you will use GDB to find where the errors occur.
//        None of the errors are in main(). You should not edit main in any way.
//        You MUST use GDB to get credit for this lab

/* The burger is empty!
No nodes to remove
This burger has 5 ingedients.
BUN->Cheese->Pickles->Lettuce->Tomato->Ketchup->BUN
This burger has 3 ingedients.
BUN->Lettuce->Tomato->Ketchup->BUN */

#include <iostream>
#include <string>
using namespace std;

struct Node {
public:
  string m_ingredient; //Data
  Node* m_next; //Node pointer
};

class LinkedList {
public:
  LinkedList(); //constructor
  ~LinkedList(); //destructor
  void InsertEnd(string data); //Insert function
  void RemoveFront(); //Remove the first node
  void Display(); //Display function
private:
  Node* m_head; //Track front of linked list
  int m_size; //Track size of linked list
};

LinkedList::LinkedList() { // Constructor for linked list
  m_head = nullptr; // set all member vars to default values
  m_size = 0;
}

LinkedList::~LinkedList() { // Destructor for linked list
  while (m_size > 0) {      // While the list is not empty, Remove the first node
    RemoveFront();
  }
}

void LinkedList::InsertEnd(string data) {
  Node *newNode = new Node; //Dynamically allocates a new node
  newNode->m_ingredient = data; //Populates data in new node
  newNode->m_next = nullptr; //Sets m_next in new node to nullptr
  //Possible Cases:
  //list is empty
  if (m_size == 0) {
    m_head = newNode;
  } else {
    //List not empty
    Node* cur = m_head; // lastNode will point at last Node of the list
    if (cur->m_next == nullptr) { // iterate lastNode through list
      cur = cur->m_next;
    }
    cur->m_next = newNode; // link the (old) last node to the new one
  }
  m_size += 1;
}

void LinkedList::RemoveFront() {
  //Possible cases:
  //List has no nodes
  if(m_size == 0){
    cout << "No ingredients to remove" << endl;
    return;
  }
  //List has one Node
  if(m_size == 1){ // Delete m_head, set to nullptr, and decrement m_size
    delete m_head;
    m_head = nullptr;
    m_size--;
    return;
  }
  //List has multiple nodes
  Node* temp = m_head; // temp keeps track of first Node to prevent leaks when moving m_head
  m_head = m_head->m_next; // move m_head to the next Node in the list
  delete temp; // delete the old first Node
  temp = nullptr; // temp isn't needed anymore, nullptr
  m_size--; // update size
}

void LinkedList::Display() {
  //Possible Cases:
  //List is empty
  if (m_size == 0) {
    cout << "The burger is empty!" << endl;
  } else {
    //List has nodes
    cout << "This burger has " << m_size << " ingedients." << endl;
    cout << "BUN->";
    Node* temp = m_head; // temp iterates list to print m_ingredient for each Node
    while (temp == nullptr) {
      cout << temp->m_ingredient << "->";
      temp = temp->m_next;
    }//end while
    cout << "BUN" << endl;
  }//end else
}

int main() {
  LinkedList list; //Create a new linked list
  list.Display(); //Empty list
  list.RemoveFront(); //Attempt to remove a Node from an empty list
  
  // Insert several nodes into the linked list
  list.InsertEnd("Cheese");
  list.InsertEnd("Pickles");
  list.InsertEnd("Lettuce");
  list.InsertEnd("Tomato");
  list.InsertEnd("Ketchup");
  list.Display();

  //Remove nodes from the list
  list.RemoveFront();
  list.RemoveFront();
  list.Display();

  return 0;
}
