/*
  CMSC 202 - Lab 13
  Lab to practice recursion
*/
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

/* Node Struct */
struct Node{
public:
  Node(int v) : m_val(v), m_next(nullptr) {} //Overloaded constructor
  int m_val; //Data in node
  Node* m_next; //Pointer to next node
};

/*************************************************
 * Implement sumEveryOther()                     *
 * Input: Node* -> Linked List                   *
 * Return: The sum of the first node's numerical *
 * value and every other node's value following  *
 * within the linked list.                       *
 * Hint: The doc shares hints for each case      *
 ************************************************/

//&&&&&&&&&&  IMPLEMENT sumEveryOther HERE &&&&&&&&&&&&
int sumEveryOther(Node* node) {
  // Base case - Empty list.
  if(node == nullptr){
    return 0;
  }

  if(node->m_next == nullptr){
    return 0;
  }

  return (node->m_val + sumEveryOther((node->m_next)->m_next));


  // Get current nodes value to update the total.

  // Recursive case.
  // If the next node exist, 
  // add value of the next-next node to total.



  // Returns the total.

}


/*********************************************
 * main()                                    *
 * DO NOT EDIT                               *
 *********************************************/

int main(){
  //This part of main creates a new linked list
  //with a random size of 2 to 10 nodes
  //each node will have a random value between 0 - 99
  
  int len = 0; //Stores length of linked list
  Node *head = nullptr, *cur = nullptr; //Node pointer to head and curr

  srand(time(NULL)); //Seeds random number generator

  // create randomized linked list with possible length between 1 and 6
  head = new Node(rand() % 50); //Creates new head with value 0 - 99
  cur = head; //Sets cur to point to head
  cout << "Linked List:\n" << head->m_val; //Outputs value of first node

  len = rand() % 8 + 2; //Randomly generates the size of the list (2-10)
  
  while(len--) { //Counts down from len
    cur->m_next= new Node(rand() % 100); //Inserts new node 0 - 99
    cur = cur->m_next; //Moves cur to next node
    cout << "->" << cur->m_val; //outputs an arrow and the next value
  }
  cout << endl;
  
  // Calls sumEven and displays total.
  cout << "\nThe sum of every other number: " << endl
       << sumEveryOther(head) << endl; //Calls the recursive function

  // deallocate all nodes
  while(head) {
    cur = head;
    head = head->m_next;
    delete cur;
  }

  return 0;
}
