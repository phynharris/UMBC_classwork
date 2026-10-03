








// NOTICE: Just in case you are unaware, the Sort function we made based on the code we were given does not function 100% correctly
// This is because the header files use longs instead of long longs, which causes some of the stream values to wrap around and become negative.









//Title: Queue.cpp
//Author: Jeremy Dixon
//Date: 11/10/2025
//Description: Describes the templated class Queue

#ifndef QUEUE_CPP
#define QUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated linked list
//Note: Because the linked list is a templated class,
//      there is only ONE file (Queue.cpp)

//Templated node class
template <class T>
class Node {
public:
  Node( const T& data ); //Constructor
  T GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = nullptr;
}

template <class T>
T Node<T>::GetData() {
  return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Queue {
 public:
  // Name: Queue() Queue from a linked list - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new queue where m_head and m_tail
  //                 point to nullptr and m_size = 0
  Queue();
  // Name: ~Queue() - Destructor
  // Desc: Used to destruct a Queue
  // Preconditions: There is a Queue
  // Postconditions: Queue is deallocated (including dynamically allocated nodes)
  //                 Can just call Clear()
 ~Queue();
  // Name: Queue (Copy Constructor)
  // Preconditions: Creates a copy of existing Queue in separate memory
  //                address (deep copy)
  //                Requires one already existing Queue
  // Postconditions: Copy of existing Queue
  Queue(const Queue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: When two Queue objects exist, sets one to equal another
  //                Requires two Queue objects
  // Postconditions: When completed, you have two Queues in
  //                 separate memory addresses with the same
  //                 number of nodes with the same values in each node
  Queue<T>& operator= (Queue&);
  // Name: PushBack
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Queue
  // Postconditions: Adds a new node to the end of the Queue.
  void PushBack(const T&);
  // Name: PopFront
  // Preconditions: Queue with at least one node. 
  // Postconditions: Removes first node in the queue and
  //                 returns the data in the first node
  T PopFront();
  // Name: Display
  // Preconditions: Outputs the queue.
  // Postconditions: Displays the data in each node of queue
  // Required (used only for queue testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a Queue with at least one node
  // Postconditions: Returns whatever data is pointed at by m_head -
  //                 Does NOT remove node
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a queue
  // Postconditions: Returns if the queue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a queue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a queue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  int Find(T);
  // Name: Clear
  // Preconditions: Requires a queue
  // Postconditions: Deallocates and removes all nodes in a queue. No memory leaks
  void Clear();
  // Name: At
  // Precondition: Existing Queue
  // Postcondition: Returns object from Queue at a specific location
  // Desc: Iterates to node x and returns data from Queue
  T At (int x);
  // Name: Swap(int)
  // Preconditions: Requires a queue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Example: Swap(1) would swap the node 0 with node 1 so
  //          that node 1 would now be m_head
  // Desc: Swaps two nodes by updating the pointers (not just the value)
  // Hint: Think about the special cases! Implement before Sort
  void Swap(int);
  // Name: Sort()
  // Preconditions: Requires a queue with a minimum of 2 nodes
  //                (otherwise notifies user)
  // Postconditions: Sorts the Queue (uses overloaded <).
  // Desc: This is used to sort anything in the Queue assuming the
  //       < is overloaded
  //       Uses bubble sort and Swap function above.
  //       Ensure working with queue_test before rest of project.
  void Sort();
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********Implement Queue Class Here***********
//**********All Functions Are Required Even If Not Used for Project**************
//**********No references to anything from Song/SongPlayer here*****************

// Queue<T>::Queue
// Given nothing — Returns nothing
template <class T>
Queue<T>::Queue(){
  // Creates an empty queue
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}


// Queue<T>::~Queue
// Given nothing — Returns nothing
template <class T>
Queue<T>::~Queue(){
  // Calls Clear() to remove all dynamically allocated nodes
  Clear();
}


// Queue<T>::Queue
// Given a reference to a Queue — Returns nothing
template <class T>
Queue<T>::Queue(const Queue& queue){
  Node<T>* curr = queue.m_head;
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;

  // Copies data int new node
  for(int i = 0; i < queue.m_size; i++){
    PushBack(curr->GetData());
    curr = curr->GetNext();
  }
}

// Queue<T>::operator=
// Given a reference to a Queue — Returns nothing
template <class T>
Queue<T>& Queue<T>::operator= (Queue& queue){
  Node<T>* curr = queue.m_head;
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;

  // Copies data into new node
  for(int i = 0; i < queue.m_size; i++){
    PushBack(curr->GetData());
    curr = curr->GetNext();
  }
  return *this;
}

// Queue<T>::PushBack
// Given the data to push back — Returns nothing
template <class T>
void Queue<T>::PushBack(const T& data){
  
  Node<T>* node = new Node(data); // New node for song queue
  
  // Sets the first node equal to m_head and tail
  if(m_size == 0){
    m_head = node;
    m_tail = node;
    
  // Adds new node to back of the list, makes it the new tail 
  }else{
    m_tail->SetNext(node);
    m_tail = m_tail->GetNext();
  }

  m_size++;
}

// Queue<T>::PopFront
// Given nothing — Returns templated node data
template <class T>
T Queue<T>::PopFront(){
  Node<T>* curr = m_head; // Marks the current node in queue
  T data = curr->GetData(); // Data inhabting m_head

  // Moves m_head to second node, deletes the first node
  m_head = m_head->GetNext();
  curr->SetNext(nullptr);
  curr = nullptr;
  delete curr;

  m_size--;
  return data;
}

// Queue<T>::Display
// Given nothing — Returns nothing
template <class T>
void Queue<T>::Display(){
  Node<T>* curr = m_head; // Marks the current node in queue
  int counter = 1;        // Counter to be displayed

  
  // Checks if queue is empty
  if(IsEmpty() == true){
    cout << "No songs in queue." << endl;
    return;
  }
  

  // Traverses through Queue and displays data in each node
  while(curr != nullptr){
    if constexpr((is_pointer<T>::value) == true){
      cout << counter << ". " << *(curr->GetData()) << endl;
    }else{
      cout << counter << ". " << curr->GetData() << endl;
    }
    counter++;
    curr = curr->GetNext();
  }
}

// Queue<T>::Front
// Give nothing — Returns m_head's data
template <class T>
T Queue<T>::Front(){

  return m_head->GetData();
}

// Queue<T>::IsEmpty
// Given nothing — Returns if LL is empty
template <class T>
bool Queue<T>::IsEmpty(){
  // Checks if Queue is empty
  if(m_size == 0){
    return true;
  }else{
    return false;
  }
}

template <class T>
int Queue<T>::GetSize(){

  return m_size;
}

// Queue<T>::Find
// Given templated node data — Returns index of data, if it exists
template <class T>
int Queue<T>::Find(T data){
  Node<T>* curr = m_head; // Marks the current node in queue
  int counter = 0; // counter/index of data in queue

  // Checks if queue is empty
  if(IsEmpty() == true){
    return -1;
  }

  // Traverse through linked list
  // If data is found, index is returned
  while(curr != nullptr){
    if(*(curr->GetData()) == *data){
      return counter;
    }else{
      curr = curr->GetNext();
      counter++;
    }
  }

  return -1;
}

// Queue<T>::Clear
// Given nothing — Returns nothing
template <class T>
void Queue<T>::Clear(){
  Node<T>* curr = m_head; //Marks the current node in queue
  // Checks if queue is empty
  if(IsEmpty()){
    //cout << "Queue is empty" << endl;
    return;
  }

  // Deletes each node in the queue
  while(m_head != nullptr){
    curr = m_head;
    m_head = m_head->GetNext();
    delete curr;
  }

  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Queue<T>::At
// Given an index — Returns node data at index
template <class T>
T Queue<T>::At(int x){
  Node<T>* curr = m_head; // Marks the current node in queue

  // Cycles through the queue until desired index is reached
  for(int i = 0; i < x; i++){
    curr = curr->GetNext();
  }

  return curr->GetData();
}

// Queue<T>::Swap
// Given an index — Returns nothing
template <class T>
void Queue<T>::Swap(int index){
  Node<T>* curr = m_head; // Marks the current node in queue
  Node<T>* prev = m_head; // Marks the previous node in queue
  Node<T>* prev2 = m_head; // Marks the second previous node in queue
  int counter = 0; // Increments as LL is traversed
  
  // Returns if empty
  if(IsEmpty() == true){
    cout << "Running" << endl;
    return;
  // Returns if index is invalid 
  }else if(index >= m_size || index <= 0){
    cout << "Invalid index" << endl;
    return;
  // Returns if only 1 song is in queue
  }else if(m_size == 1){
    cout << "Only one song in queue." << endl;
    return;
  // If only 2 songs, swaps them
  }else if(m_size == 2){
    Node<T>* temp = m_head;
    m_head = m_tail;
    m_tail = temp;
    return;
  // If the index is 1 (the second song in queue)
  }else if (index == 1){
    curr = curr->GetNext();
    prev->SetNext(curr->GetNext());
    curr->SetNext(prev);
    m_head = curr; 
  }else{
    // Traveses through the queue until curr is at the desired index
    while(curr->GetNext() != nullptr && counter < index){
      prev2 = prev;
      prev = curr;
      curr = curr->GetNext();
      counter++;
    }
    
    // Swaps curr and prev
    prev2->SetNext(curr);
    prev->SetNext(curr->GetNext());
    curr->SetNext(prev);

    // If the last node was swapped places m_tail at the new last node
    if(index == m_size - 1){
      m_tail = prev;
    }
  }
}

// Queue<T>::Sort
// Given nothing — Returns nothing
template <class T>
void Queue<T>::Sort(){
  Node<T>* prev = m_head;  // Marks the previous node
  Node<T>* curr = m_head;  // Marks the current node
  int counter = 1;         // Counter for traversing Queue — starts at 2nd element

  // If less than two songs in queue, does not sort
  if(m_size < 2){
    return;
  }

  while(curr != nullptr && counter < m_size){
    // (if statement provided by Prof. Dixon)
    // Checks if Node holds a pointer
    // Calls Swap to sort the nodes by highest spotify streams
    if constexpr((is_pointer<T>::value) == true){
      prev = curr;
      curr = curr->GetNext();
      if(*(curr)->GetData() < *(prev)->GetData()){
	Swap(counter);
	prev = m_head;
	curr = m_head;
	counter = 0;
      }
    }else{
      prev = curr;
      curr = curr->GetNext();
      if(curr->GetData() < prev->GetData()){
	Swap(counter);
	prev = m_head;
	curr = m_head;
	counter = 0;
      }
    }
    counter++;
  }
}
#endif
