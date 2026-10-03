/* Title: lab11a.cpp
   Course: CMSC 202 - Fall 2025
   Description: This introduces templated functions.
*/
#include <iostream>
using namespace std;

// This is a templated class that can hold any items inside a dynamically
// allocated array.
template <class T>
class DynamicArray {
public:
  //Name: Default Constructor
  //Pre:  None
  //Post: Creates an empty array
  DynamicArray() {
    m_size = 0;
    m_arr = new T[m_size];
  }

  //Name: Destructor
  //Pre:  None
  //Post: Deallocates array
  ~DynamicArray() {
    delete[] m_arr;
    m_arr = nullptr;
  }

  // ****** IMPLEMENT THE PUSH FUNCTION ******

  //Name: Push
  //Pre:  Updates current array
  //Post: Resizes array and inserts item passed into back of array
  void Push(T val) {
  // This function should add an element to the end of the dynamic array

  //HINTS:
  // - Create a temporary array with size + 1 elements
  // - Copy arr values to temporary array
  // - Insert the new value at the end of the temporary array
  // - Deallocate the old array
  // - Reinitialize with size + 1 elements
  // - Copy temporary array values to arr
  // - Increase the size variable
    T *temp = new T[m_size + 1];

    
    for(int i = 0; i < m_size; i++){
      cout << "mri " << m_arr[i] << endl;
      temp[i] = m_arr[i];
    }

    temp[m_size] = val;

    delete[] m_arr;

    
    m_arr = temp;
    m_size++;
  }
  //Name: Pop
  //Pre:  Has existing array with a size greater than 0
  //Post: Resizes array and removes last item in array
  //      If size == 0, displays "Array empty"
  void Pop() {
    if (m_size == 0){
      cout << "Array empty" << endl;
      return;
    }
    T *temp = new T[m_size + 1];
    
    for (int i = 0; i < m_size - 1; ++i) {
      temp[i] = m_arr[i];
    }
    delete[] m_arr;
    
    m_arr = temp;
    m_size--;
  }

  //Name: Display
  //Pre:  Displays data from each index in the array
  //Post: None
  void Display() {
    if (m_size == 0){
      cout << "Array empty" << endl;
      return;
    }
      
    cout << "Dynamic Array Elements:" << endl;
    for (int i = 0; i < m_size; ++i) {
      cout << m_arr[i] << " ";
    }
    cout << endl;
  }
  
private:
  T* m_arr;   // Pointer to the array
  int m_size; // Size of the array
};

int main() {
  DynamicArray<int> darr; // Calls constructor
  darr.Display(); // Displays empty array
  darr.Push(1);   // Adds 1 to array
  darr.Display(); // Displays array
  darr.Push(2);   // Adds 2 to array
  darr.Push(3);   // Adds 3 to array
  darr.Push(4);   // Adds 4 to array
  darr.Display(); // Displays array
  darr.Pop();     // Removes last entry in array (4)
  darr.Display(); // Displays array
  
  return 0;
}
