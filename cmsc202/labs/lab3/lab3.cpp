#include <iostream>
using namespace std;

bool isUnique(int array[], int arr_value, int index);
void getEvenCount (int array[]);

const int NUM_NUMBERS = 4;

int main(){
  int arr[NUM_NUMBERS] = {0};

  for(int i = 0; i < NUM_NUMBERS; i++){
    do{
      cout << "\nEnter a number for the array: " << endl;
      cin >> arr[i];
      cout << endl;
    }while((arr[i] == 0) || !isUnique(arr, arr[i], i));
  }

  cout << "Your numbers are: ";
  for(int k = 0; k < NUM_NUMBERS; k++){
    cout << arr[k] << " ";
  }
  cout << endl;

  getEvenCount(arr);
  
  return 0;
}

bool isUnique(int array[], int arr_value, int index){
  if(index == 0){
    return true;
  }else{
    for(int j = 0; j < index; j++){
      if(array[j] == arr_value){
	cout << "That number is not unique" << endl
	     << "Please enter a different number. " << endl;
	return false;
      }
    }
  }
  return true;
}

void  getEvenCount(int array[]){
  int numEvens = 0;
  
  for(int l = 0; l < NUM_NUMBERS; l++){
    if(array[l] % 2 == 0){
      ++numEvens;
    }
  }
   cout << "There are " << numEvens << " even numbers." << endl;
}

