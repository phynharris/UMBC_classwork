#include "streak.h"
#include <vector>
#include <random>
using namespace std;
enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
  Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
  {
    if (type == NORMAL){
      //the case of NORMAL to generate integer numbers with normal distribution
      m_generator = std::mt19937(m_device());
      //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
      //the mean and standard deviation can change by passing new values to constructor
      m_normdist = std::normal_distribution<>(mean,stdev);
    }
    else if (type == UNIFORMINT) {
      //the case of UNIFORMINT to generate integer numbers
      // Using a fixed seed value generates always the same sequence
      // of pseudorandom numbers, e.g. reproducing scientific experiments
      // here it helps us with testing since the same sequence repeats
      m_generator = std::mt19937(10);// 10 is the fixed seed value
      m_unidist = std::uniform_int_distribution<>(min,max);
    }
    else{ //the case of UNIFORMREAL to generate real numbers
      m_generator = std::mt19937(10);// 10 is the fixed seed value
      m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
    }
  }
  void setSeed(int seedNum){
    // we have set a default value for seed in constructor
    // we can change the seed by calling this function after constructor call
    // this gives us more randomness
    m_generator = std::mt19937(seedNum);
  }
  int getRandNum(){
    // this function returns integer numbers
    // the object must have been initialized to generate integers
    int result = 0;
    if(m_type == NORMAL){
      //returns a random number in a set with normal distribution
      //we limit random numbers by the min and max values
      result = m_min - 1;
      while(result < m_min || result > m_max)
	result = m_normdist(m_generator);
    }
    else if (m_type == UNIFORMINT){
      //this will generate a random number between min and max values
      result = m_unidist(m_generator);
    }
    return result;
  }

  double getRealRandNum(){
    // this function returns real numbers
    // the object must have been initialized to generate real numbers
    double result = m_uniReal(m_generator);
    // a trick to return numbers only with two deciaml points
    // for example if result is 15.0378, function returns 15.03
    // to round up we can use ceil function instead of floor
    result = std::floor(result*100.0)/100.0;
    return result;
  }

 private:
  int m_min;
  int m_max;
  RANDOM m_type;
  std::random_device m_device;
  std::mt19937 m_generator;
  std::normal_distribution<> m_normdist;//normal distribution
  std::uniform_int_distribution<> m_unidist;//integer uniform distribution
  std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

class Tester{
 public:
  bool testAVLInsert_Balance(Streak &streak);  // Tests if an AVL tree is balanced after insertions
  bool testAVLInsert_BST(Streak &streak);      // Tests if an AVL tree retains BST property
  bool testSplayInsert_Root(Grid &grid);       // Tests to ensure that the newly inserted node becomes the root
  bool testSplayInsert_BST(Grid &grid);        // Tests if a splay tree is balanced after insertions
  bool testAVLFind(Streak &streak);
  //bool testSplayCount(Grid &grid);
  //bool testSplaySetState(Grid &grid);
  //bool testSplayOperations(Grid &grid);

  bool recursAVLBalance(Tiger* root, bool &balanced); // Helper function that make sure an AVL tree is balanced
  bool recursBSTProperty(Tiger* root, bool &retain); // Helper function that verifies AVL trees remain BSTs
  bool recursBSTProperty(Streak* root, bool &retain); // Helper function that verifies splay trees remain BSTs
 private:
};

int main(){
  Tester tester;

  // Test for balanced AVL tree
  {
    Streak streak;
    cout << "\nTesting for balanced AVL Tree after insertions" << endl;
    if(tester.testAVLInsert_Balance(streak)){
      cout << "\tAVL tree is balanced!\n";
    }else{
      cout << "\tAVL tree is unbalanced!\n";
    }
  }
  {
    Streak streak;
    cout << "\nTesting for BST property in AVL Tree after insertions" << endl;
    if(tester.testAVLInsert_BST(streak)){
      cout << "\tAVL tree retains BST property!\n";
    }else{
      cout << "\tAVL tree does not retain BST property!\n";
    }
  }

  {
    Grid grid;
    cout << "\nTesting to ensure most recently added grid goes to root" << endl;
    if(tester.testSplayInsert_Root(grid)){
      cout << "\tRoot is consistent!\n";
    }else{
      cout << "\tRoot is inconsistent!\n";
    }
  }
  
  {
    Grid grid;
    cout << "\nTesting for BST property in splay tree after insertions" << endl;
    if(tester.testSplayInsert_BST(grid)){
      cout << "\tSplay tree retains BST property!\n";
    }else{
      cout << "\tSplay tree does not retain BST property!\n";
    }
  }
  {
    Streak streak;
    cout << "\nTesting findTiger" << endl;
    if(tester.testAVLFind(streak)){
      cout << "\tAll tigers found!\n";
    }else{
      cout << "\tAt least one tiger not found!\n";
    }
  }

  return 0;
}

bool Tester::testAVLInsert_Balance(Streak &streak){
  Random idGen(MINID,MAXID);
  Random ageGen(0,2);
  Random genderGen(0,2);
  int size = 100;
  int id = 0;
  bool balanced = true;

  for(int i = 0; i < size; i++){
    id = idGen.getRandNum();
    
    Tiger tiger(id,
		static_cast<AGE>(ageGen.getRandNum()),
		static_cast<GENDER>(genderGen.getRandNum()));
    streak.insert(tiger);
  } 
  
  if(recursAVLBalance(streak.m_root, balanced)){
    return true;
  }else{
    return false;
  }
}

bool Tester::testAVLInsert_BST(Streak &streak){
  Random idGen(MINID,MAXID);
  Random ageGen(0,2);
  Random genderGen(0,2);
  int size = 100;
  int id = 0;
  bool retain = true;

  for(int i = 0; i < size; i++){
    id = idGen.getRandNum();

    Tiger tiger(id,
		static_cast<AGE>(ageGen.getRandNum()),
		static_cast<GENDER>(genderGen.getRandNum()));
    streak.insert(tiger);
  }

  if(recursBSTProperty(streak.m_root, retain)){
    return true;
  }else{
    return false;
  }
}

bool Tester::testSplayInsert_Root(Grid &grid){
  Random idGen(MINID,MAXID);
  Random ageGen(0,2);
  Random genderGen(0,2);
  int id = 0;

  for (int i = 0; i < 100; i++){
    Tiger tigers[2];
    int size = 2;
    id = idGen.getRandNum();
    
    for(int i = 0; i < size; i++){
      Tiger tiger(idGen.getRandNum(),
		  static_cast<AGE>(ageGen.getRandNum()),
		  static_cast<GENDER>(genderGen.getRandNum()));
      tigers[i] = tiger;
    }
    grid.insert(id, tigers, 2);

    if(grid.m_root->m_gridID != id){
      return false;
    }
  }
  return true;
}

bool Tester::testSplayInsert_BST(Grid &grid){
  Random idGen(MINID,MAXID);
  Random ageGen(0,2);
  Random genderGen(0,2);
  int id = 0;
  bool retain = true;

  for (int i = 0; i < 100; i++){
    Tiger tigers[2];
    int size = 2;
    id = idGen.getRandNum();
    
    for(int i = 0; i < size; i++){
      Tiger tiger(idGen.getRandNum(),
		  static_cast<AGE>(ageGen.getRandNum()),
		  static_cast<GENDER>(genderGen.getRandNum()));
      tigers[i] = tiger;
    }
    grid.insert(id, tigers, 2);
  }

  if(recursBSTProperty(grid.m_root, retain)){
    return true;
  }else{
    return false;
  }
}

bool Tester::testAVLFind(Streak &streak){
  Random idGen(MINID,MAXID);
  Random ageGen(0,2);
  Random genderGen(0,2);
  int size = 100;
  int arrsize = size/2;
  int id = 0;
  int IDs[arrsize] = {0}; 

  for(int i = 0; i < size; i++){
    id = idGen.getRandNum();
    
    
    if(i % 2 == 0){
      IDs[i/2] = id;
    }

    Tiger tiger(id,
		static_cast<AGE>(ageGen.getRandNum()),
		static_cast<GENDER>(genderGen.getRandNum()));
    streak.insert(tiger);
  }

  for(int i = 0; i < arrsize; i++){
    if(!streak.findTiger(id)){
      return false;
    }
  }

  return true;
}

// Helper function that traverses and AVL tree
bool Tester::recursAVLBalance(Tiger* root, bool &balanced){
  int left_h = -1;
  int right_h = -1;
  int diff = 0;

  if (root != nullptr){
    recursAVLBalance(root->m_left, balanced);
    recursAVLBalance(root->m_right, balanced);

    if(root->m_left != nullptr){
      left_h = root->m_left->m_height;
    }

    if(root->m_right != nullptr){
      right_h = root->m_right->m_height;
    }

    diff = left_h - right_h;

    if (abs(diff) > 1){
      balanced = false;
    }
  }

  return balanced;
}

bool Tester::recursBSTProperty(Tiger* root, bool &retain){
  if(root != nullptr){
    if(root->m_left != nullptr){
      if(root->m_id <= root->m_left->m_id){
	retain = false;
      }
    }

    if(root->m_right != nullptr){
      if(root->m_id >= root->m_right->m_id){
	retain = false;
      }     
    }
    
    recursBSTProperty(root->m_left, retain);
    recursBSTProperty(root->m_right, retain);
  }
  
  return retain;
}

bool Tester::recursBSTProperty(Streak* root, bool &retain){
  if(root != nullptr){
    if(root->m_left != nullptr){
      if(root->m_gridID <= root->m_left->m_gridID){
	retain = false;
      }
    }

    if(root->m_right != nullptr){
      if(root->m_gridID >= root->m_right->m_gridID){
	retain = false;
      }
    }

    recursBSTProperty(root->m_left, retain);
    recursBSTProperty(root->m_right, retain);
  }

  return retain;
}
