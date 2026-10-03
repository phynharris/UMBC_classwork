// CMSC 341 - Spring 2026 - Project 3
/*
Name: Jaylen Jenkins
  ID: FP31977
Date: 4/8/2026
 */

#include "shop.h"
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL, SHUFFLE};
class Random {
public:
  Random(){}
  Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
  {
    if (type == NORMAL){
      //the case of NORMAL to generate integer numbers with normal distribution
      m_generator = mt19937(m_device());
      //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
      //the mean and standard deviation can change by passing new values to constructor
      m_normdist = normal_distribution<>(mean,stdev);
    }
    else if (type == UNIFORMINT) {
      //the case of UNIFORMINT to generate integer numbers
      // Using a fixed seed value generates always the same sequence
      // of pseudorandom numbers, e.g. reproducing scientific experiments
      // here it helps us with testing since the same sequence repeats
      m_generator = mt19937(10);// 10 is the fixed seed value
      m_unidist = uniform_int_distribution<>(min,max);
    }
    else if (type == UNIFORMREAL) { //the case of UNIFORMREAL to generate real numbers
      m_generator = mt19937(10);// 10 is the fixed seed value
      m_uniReal = uniform_real_distribution<double>((double)min,(double)max);
    }
    else { //the case of SHUFFLE to generate every number only once
      m_generator = mt19937(m_device());
    }
  }
  void setSeed(int seedNum){
    // we have set a default value for seed in constructor
    // we can change the seed by calling this function after constructor call
    // this gives us more randomness
    m_generator = mt19937(seedNum);
  }
  void init(int min, int max){
    m_min = min;
    m_max = max;
    m_type = UNIFORMINT;
    m_generator = mt19937(10);// 10 is the fixed seed value
    m_unidist = uniform_int_distribution<>(min,max);
  }
  void getShuffle(vector<int> & array){
    // this function provides a list of all values between min and max
    // in a random order, this function guarantees the uniqueness
    // of every value in the list
    // the user program creates the vector param and passes here
    // here we populate the vector using m_min and m_max
    for (int i = m_min; i<=m_max; i++){
      array.push_back(i);
    }
    shuffle(array.begin(),array.end(),m_generator);
  }

  void getShuffle(int array[]){
    // this function provides a list of all values between min and max
    // in a random order, this function guarantees the uniqueness
    // of every value in the list
    // the param array must be of the size (m_max-m_min+1)
    // the user program creates the array and pass it here
    vector<int> temp;
    for (int i = m_min; i<=m_max; i++){
      temp.push_back(i);
    }
    shuffle(temp.begin(), temp.end(), m_generator);
    vector<int>::iterator it;
    int i = 0;
    for (it=temp.begin(); it != temp.end(); it++){
      array[i] = *it;
      i++;
    }
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
    result = floor(result*100.0)/100.0;
    return result;
  }

  string getRandString(int size){
    // the parameter size specifies the length of string we ask for
    // to use ASCII char the number range in constructor must be set to 97 - 122
    // and the Random type must be UNIFORMINT (it is default in constructor)
    string output = "";
    for (int i=0;i<size;i++){
      output = output + (char)getRandNum();
    }
    return output;
  }

  int getMin(){return m_min;}
  int getMax(){return m_max;}
private:
  int m_min;
  int m_max;
  RANDOM m_type;
  random_device m_device;
  mt19937 m_generator;
  normal_distribution<> m_normdist;//normal distribution
  uniform_int_distribution<> m_unidist;//integer uniform distribution
  uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

// the followings are sample priority functions to be used by Shop class
// Priority functions compute an integer priority for a order.
int priorityFn1(const Order &order);// works with a MAXHEAP
int priorityFn2(const Order &order);// works with a MINHEAP

class Tester{
public:
  // Test Insertion
  bool testInsertMinNorm(Shop &shop);               // Test that inserted nodes maintain MIN-HEAP property
  bool testInsertMaxNorm(Shop &shop);               // Test that inserted nodes maintain MAX-HEAP property
  bool testInsertNPLProperty(Shop &shop);           // Test that inserted nodes maintain NPL property
  bool testInsertNPLValues(Shop &shop);             // Test that inserted nodes have appropriate NPL values

  // Test structure conversion
  bool testMinSkew2LeftistNorm(Shop &shop);         // Test that SKEW->LEFTIST HEAP maintains MIN-HEAP PROPERTY
  bool testMinSkew2LeftistNPL(Shop &shop);          // Test that SKEW->LEFTIST HEAP maintains NPL PROPERTY in MIN-HEAP
  bool testMinSkew2LeftistNPLV(Shop &shop);         // Test that SKEW->LEFTIST HEAP maintains NPL Values in MIN-HEAP
  bool testMinLeftist2SkewNorm(Shop &shop);         // Test that LEFTIST->SKEW HEAP maintains MIN-HEAP PROPERTY
  bool testMaxSkew2LeftistNorm(Shop &shop);         // Test that SKEW->LEFTIST HEAP maintains MAX-HEAP PROPERTY
  bool testMaxSkew2LeftistNPL(Shop &shop);          // Test that SKEW->LEFTIST HEAP maintains NPL PROPERTY in MAX-HEAP
  bool testMaxSkew2LeftistNPLV(Shop &shop);         // Test that SKEW->LEFTIST HEAP maintains NPL Values in MAX-HEAP
  bool testMaxLeftist2SkewNorm(Shop &shop);         // Test that LEFTIST->SKEW HEAP maintains MAX-HEAP PROPERTY

  // Test heapType conversion
  bool testMinSkew2MaxSkewNorm(Shop &shop);         // Test that MIN->MAX SKEW HEAP maintains HEAP PROPERTY
  bool testMaxSkew2MinSkewNorm(Shop &shop);         // Test that MAX->MIN SKEW HEAP maintains HEAP PROPERTY
  bool testMinLeftist2MaxLeftistNorm(Shop &shop);   // Test that MIN->MAX LEFTIST HEAP maintains HEAP PROPERTY
  bool testMinLeftist2MaxLeftistNPL(Shop &shop);    // Test that MIN->MAX LEFTIST HEAP maintains NPL PROPERTY
  bool testMinLeftist2MaxLeftistNPLV(Shop &shop);   // Test that MIN->MAX LEFTIST HEAP maintains NPL Values
  bool testMaxLeftist2MinLeftistNorm(Shop &shop);   // Test that MAX->MIN LEFTIST HEAP maintains HEAP PROPERTY
  bool testMaxLeftist2MinLeftistNPL(Shop &shop);    // Test that MAX->MIN LEFTIST HEAP maintains NPL PROPERTY
  bool testMaxLeftist2MinLeftistNPLV(Shop &shop);   // Test that MAX->MIN LEFTIST HEAP maintains NPL Values

  // Test removal
  bool testRemoveMinNorm(Shop &shop);               // Test that MIN-HEAP property are maintained after removing nodes
  bool testRemoveMaxNorm(Shop &shop);               // Test that MAX-HEAP property are maintained after removing nodes
  bool testRemoveNPLProperty(Shop &shop);           // Test that HEAP properties are maintained after removing nodes in Leftist Heap
  bool testRemoveNPLValues(Shop &shop);             // Test that HEAP properties are maintained after removing nodes in Leftist Heap

  // Merge Queues
  bool testMergeQueueNorm(Shop &shop, Shop &rhs);       // Test that ensures two populated heaps are merged
  bool testMergeQueueNPL(Shop &shop, Shop &rhs);        // Test that ensures two populated heaps are merged
  bool testMergeQueueNPLV(Shop &shop, Shop &rhs);       // Test that ensures two populated heaps are merged
  bool testMergeQueueEdge(Shop &shop, Shop &rhs);       // Test that ensures shops are properly merged if rhs is not null but lhs is
  bool testMergeQueueEdgeNPL(Shop &shop, Shop &rhs);    // Test that ensures shops are properly merged if rhs is not null but lhs is
  bool testMergeQueueEdgeNPLV(Shop &shop, Shop &rhs);   // Test that ensures shops are properly merged if rhs is not null but lhs is

  // Tests Copy Constructor
  bool testCopyConstructorNorm(Shop &shop);         // Test that a heap created using the CC is the same as the original
  bool testCopyConstructorNPL(Shop &shop);               // NPL Property
  bool testCopyConstructorNPLV(Shop &shop);              // NPL Values
  bool testCopyConstructorEdge(Shop &shop);         // Test that a copied empty heap is consistent

  // Tests Overloaded Assignment Operator
  bool testOvldAssignNorm1(Shop &shop, Shop &rhs);  // Test that a heap is copied into a populated heap
  bool testOvldAssignNPL1(Shop &shop, Shop &rhs);                   // NPL Property
  bool testOvldAssignNPLV1(Shop &shop, Shop &rhs);                  // NPL Values
  bool testOvldAssignNorm2(Shop &shop, Shop &rhs);  // Test that an populated heap is copied into a empty heap
  bool testOvldAssignNPL2(Shop &shop, Shop &rhs);                   // NPL Property
  bool testOvldAssignNPLV2(Shop &shop, Shop &rhs);                  // NPL Values
  bool testOvldAssignEdge(Shop &shop, Shop &rhs);   // Test that an empty heap is copied into a populated heap

  // Error Cases
  bool testDequeueErr(Shop &shop);                  // Test that an empty queue cannot be dequeued with getNextOrder
  bool testMergeQueueErr(Shop &shop, Shop &rhs);               // Test that incompatible queues cannot be merged

  // Helper Functions — Shop
  bool equalityHelper(Order* root, Order* copy, bool &correct);     // Helper function that determines if a copies Shop is the same as its original
  bool findNode(Order* root, Order order, bool &exists);            // Helper function that finds nodes based on orderID
  bool maxHelper(Order* root, bool &retain, prifn_t priorFunc);     // Helper function that determines if a heap is a MAXHEAP
  bool minHelper(Order* root, bool &retain, prifn_t priorFunc);     // Helper function that determines if a heap is a MINHEAP
  bool nplHelper(Order* root, bool &retain);                        // Helper function that determines if a LEFTIST heap has an NPL property
  int nplVHelper(Order* root, bool &retain, int left, int right);   // Helper function that determines if a LEFTIST heap's nodes have an apropriate NPL value

  // Region Tests
  bool testInsertShopsNorm(Region &region);                  // Test that many shops can be inserted into a region

  // Helper Functions — Region
  // findNode(Shop* heap, Shop shop)
  bool minHelperReg(Region region, Shop* heap, bool &retain);

private:
};

int main(){
  Tester tester;

  // Test that inserted nodes maintain MIN-HEAP Property in SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting normal case for inserting nodes in MIN-SKEW Heap" << endl;
    if(tester.testInsertMinNorm(shop)){
      cout << "\tNormal case for inserting nodes in MIN-SKEW Heap passed!\n";
    }else{
      cout << "\tNormal case for inserting nodes in MIN-SKEW Heap failed!\n";
    }
    
  }

  // Test that inserted nodes maintain MAX-HEAP property in SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting normal case for inserting nodes in MAX-SKEW Heap" << endl;
    if(tester.testInsertMaxNorm(shop)){
      cout << "\tNormal case for inserting nodes in MAX-SKEW Heap passed!\n";
    }else{
      cout << "\tNormal case for inserting nodes in MAX-SKEW Heap failed!\n";
    }
  }

  // Test that inserted nodes maintain MIN-HEAP property in LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting normal case for inserting nodes in MIN-LEFTIST Heap" << endl;
    if(tester.testInsertMinNorm(shop)){
      cout << "\tNormal case for inserting nodes in MIN-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNormal case for inserting nodes in MIN-LEFTIST Heap failed!\n";
    }
  }

  // Test that inserted nodes maintain MAX-HEAP property in LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting normal case for inserting nodes in MAX-LEFTIST Heap" << endl;
    if(tester.testInsertMaxNorm(shop)){
      cout << "\tNormal case for inserting nodes in MAX-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNormal case for inserting nodes in MAX-LEFTIST Heap failed!\n";
    }
  }

  // Test that inserted nodes maintain NPL property in MIN LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL property for inserting nodes in MIN-LEFTIST Heap" << endl;
    if(tester.testInsertNPLProperty(shop)){
      cout << "\tNPL property for inserting nodes in MIN-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNPL property for inserting nodes in MIN-LEFTIST Heap failed!\n";
    }
  }

  // Test that inserted nodes maintain NPL property in MAX LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL property for inserting nodes in MAX-LEFTIST Heap" << endl;
    if(tester.testInsertNPLProperty(shop)){
      cout << "\tNPL property for inserting nodes in MAX-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNPL property for inserting nodes in MAX-LEFTIST Heap failed!\n";
    }
  }

  // Test that inserted nodes maintain NPL values in MIN LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL values for inserting nodes in MIN-LEFTIST Heap" << endl;
    if(tester.testInsertNPLValues(shop)){
      cout << "\tNPL values for inserting nodes in MIN-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNPL values for inserting nodes in MIN-LEFTIST Heap failed!\n";
    }
  }

  // Test that inserted nodes maintain NPL values in MAX LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL property for inserting nodes in MAX-LEFTIST Heap" << endl;
    if(tester.testInsertNPLValues(shop)){
      cout << "\tNPL property for inserting nodes in MAX-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNPL property for inserting nodes in MAX-LEFTIST Heap not passed!\n";
    }
  }

  // Test that SKEW->LEFTIST HEAP maintains MIN-HEAP PROPERTY
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting normal case for converting MIN-SKEW to MIN-LEFTIST" << endl;
    if(tester.testMinSkew2LeftistNorm(shop)){
      cout << "\tNormal case for converting MIN-SKEW to MIN-LEFTIST passed!\n";
    }else{
      cout << "\tNormal case for converting MIN-SKEW to MIN-LEFTIST failed!\n";
    }
  }

  // Test that SKEW->LEFTIST HEAP maintains NPL PROPERTY in MIN-HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting NPL property for converting MIN-SKEW to MIN-LEFTIST" << endl;
    if(tester.testMinSkew2LeftistNPL(shop)){
      cout << "\tNPL property for converting MIN-SKEW to MIN-LEFTIST passed!\n";
    }else{
      cout << "\tNPL Property for converting MIN-SKEW to MIN-LEFTIST failed!\n";
    }
  }

  // Test that SKEW->LEFTIST HEAP maintains NPL Values in MIN-HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting NPL values for converting MIN-SKEW to MIN-LEFTIST" << endl;
    if(tester.testMinSkew2LeftistNPLV(shop)){
      cout << "\tNPL values for converting MIN-SKEW to MIN-LEFTIST passed!\n";
    }else{
      cout << "\tNPL values for converting MIN-SKEW to MIN-LEFTIST failed!\n";
    }
  }

  // Test that LEFTIST->SKEW HEAP maintains MIN-HEAP PROPERTY
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting normal case for converting MIN-LEFTIST to MIN-SKEW" << endl;
    if(tester.testMinLeftist2SkewNorm(shop)){
      cout << "\tNormal case for converting MIN-LEFTIST to MIN-SKEW passed!\n";
    }else{
      cout << "\tNormal case for converting MIN-LEFTIST to MIN-SKEW failed!\n";
    }
  }

  // Test that SKEW->LEFTIST HEAP maintains MAX-HEAP PROPERTY
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting normal case for converting MAX-SKEW to MAX-LEFTIST" << endl;
    if(tester.testMaxSkew2LeftistNorm(shop)){
      cout << "\tNormal case for converting MAX-SKEW to MAX-LEFTIST passed!\n";
    }else{
      cout << "\tNormal case for converting MAX-SKEW to MAX-LEFTIST failed!\n";
    }
  }

  // Test that SKEW->LEFTIST HEAP maintains NPL PROPERTY in MAX-HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting NPL property for converting MAX-SKEW to MAX-LEFTIST" << endl;
    if(tester.testMaxSkew2LeftistNPL(shop)){
      cout << "\tNPL property for converting MAX-SKEW to MAX-LEFTIST passed!\n";
    }else{
      cout << "\tNPL Property for converting MAX-SKEW to MAX-LEFTIST failed!\n";
    }
  }

  // Test that SKEW->LEFTIST HEAP maintains NPL Values in MAX-HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting NPL values for converting MAX-SKEW to MAX-LEFTIST" << endl;
    if(tester.testMaxSkew2LeftistNPLV(shop)){
      cout << "\tNPL values for converting MAX-SKEW to MAX-LEFTIST passed!\n";
    }else{
      cout << "\tNPL values for converting MAX-SKEW to MAX-LEFTIST failed!\n";
    }
  }

  // Test that LEFTIST->SKEW HEAP maintains MAX-HEAP PROPERTY
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting normal case for converting MAX-LEFTIST to MAX-SKEW" << endl;
    if(tester.testMaxLeftist2SkewNorm(shop)){
      cout << "\tNormal case for converting MAX-LEFTIST to MAX-SKEW passed!\n";
    }else{
      cout << "\tNormal case for converting MAX-LEFTIST to MAX-SKEW failed!\n";
    }
  }

  // Test that MIN->MAX SKEW HEAP maintains HEAP PROPERTY
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting normal case for converting MIN-SKEW to MAX-SKEW" << endl;
    if(tester.testMinSkew2MaxSkewNorm(shop)){
      cout << "\tNormal case for converting MIN-SKEW to MAX-SKEW passed!\n";
    }else{
      cout << "\tNormal case for converting MIN-SKEW to MAX-SKEW failed!\n";
    }
  }

  // Test that MAX->MIN SKEW HEAP maintains HEAP PROPERTY
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting normal case for converting MAX-SKEW to MIN-SKEW" << endl;
    if(tester.testMaxSkew2MinSkewNorm(shop)){
      cout << "\tNormal case for converting MAX-SKEW to MIN-SKEW passed!\n";
    }else{
      cout << "\tNormal case for converting MAX-SKEW to MIN-SKEW failed!\n";
    }
  }

  // Test that MIN->MAX LEFTIST HEAP maintains HEAP PROPERTY
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting normal case for converting MIN-LEFTIST to MAX-LEFTIST" << endl;
    if(tester.testMinLeftist2MaxLeftistNorm(shop)){
      cout << "\tNormal case for converting MIN-LEFTIST to MAX-LEFTIST passed!\n";
    }else{
      cout << "\tNormal case for converting MIN-LEFTIST to MAX-LEFTIST failed!\n";
    }
  }

  // Test that MIN->MAX LEFTIST HEAP maintains NPL PROPERTY
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL property for converting MIN-LEFTIST to MAX-LEFTIST" << endl;
    if(tester.testMinLeftist2MaxLeftistNPL(shop)){
      cout << "\tNPL property for converting MIN-LEFTIST to MAX-LEFTIST passed!\n";
    }else{
      cout << "\tNPL property for converting MIN-LEFTIST to MAX-LEFTIST failed!\n";
    }
  }

  // Test that MIN->MAX LEFTIST HEAP maintains NPL Values
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL values for converting MIN-LEFTIST to MAX-LEFTIST" << endl;
    if(tester.testMinLeftist2MaxLeftistNPLV(shop)){
      cout << "\tNPL values for converting MIN-LEFTIST to MAX-LEFTIST passed!\n";
    }else{
      cout << "\tNPL values for converting MIN-LEFTIST to MAX-LEFTIST failed!\n";
    }
  }

  // Test that MAX->MIN LEFTIST HEAP maintains HEAP PROPERTY
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting normal case for converting MAX-LEFTIST to MIN-LEFTIST" << endl;
    if(tester.testMaxLeftist2MinLeftistNorm(shop)){
      cout << "\tNormal case for converting MAX-LEFTIST to MIN-LEFTIST passed!\n";
    }else{
      cout << "\tNormal case for converting MAX-LEFTIST to MIN-LEFTIST failed!\n";
    }
  }

  // Test that MAX->MIN LEFTIST HEAP maintains NPL PROPERTY
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL property for converting MAX-LEFTIST to MIN-LEFTIST" << endl;
    if(tester.testMaxLeftist2MinLeftistNPL(shop)){
      cout << "\tNPL property for converting MAX-LEFTIST to MIN-LEFTIST passed!\n";
    }else{
      cout << "\tNPL property for converting MAX-LEFTIST to MIN-LEFTIST failed!\n";
    }
  }

  // Test that MAX->MIN LEFTIST HEAP maintains NPL Values
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL values for converting MAX-LEFTIST to MIN-LEFTIST" << endl;
    if(tester.testMaxLeftist2MinLeftistNPLV(shop)){
      cout << "\tNPL values for converting MAX-LEFTIST to MIN-LEFTIST passed!\n";
    }else{
      cout << "\tNPL values for converting MAX-LEFTIST to MIN-LEFTIST failed!\n";
    }
  }

  // Test that removing nodes in a MIN-SKEW Heap maintains HEAP peoperty
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting MIN-HEAP property when removing multiple nodes in SKEW Heap" << endl;
    if(tester.testRemoveMinNorm(shop)){
      cout << "\tNormal case for removing nodes in a MIN-SKEW Heap passed!\n";
    }else{
      cout << "\tNormal case for removing nodes in a MIN-SKEW Heap failed!\n";
    }
  }

  // Test that removing nodes in a MAX-SKEW Heap maintains HEAP property
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting MAX-HEAP property when removing multiple nodes in SKEW Heap" << endl;
    if(tester.testRemoveMaxNorm(shop)){
      cout << "\tNormal case for removing nodes in a MAX-SKEW Heap passed!\n";
    }else{
      cout << "\tNormal case for removing nodes in a MAX-SKEW Heap failed!\n";
    }
  }

  // Test that removing nodes in a MIN-LEFTIST Heap maintains HEAP property
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting MIN-HEAP property when removing multiple nodes in LEFTIST Heap" << endl;
    if(tester.testRemoveMinNorm(shop)){
      cout << "\tNormal case for removing nodes in a MIN-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNormal case for removing nodes in a MIN-LEFTIST Heap failed!\n";
    }
  }

  // Test that removing nodes in a MAX-LEFTIST Heap maintains HEAP property
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting MAX-HEAP property when removing multiple nodes in LEFTIST Heap" << endl;
    if(tester.testRemoveMaxNorm(shop)){
      cout << "\tNormal case for removing nodes in a MAX-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNormal case for removing nodes in a MAX-LEFTIST Heap failed!\n";
    }
  }

  // Test that removing nodes in a MIN-LEFTIST Heap maintains NPL property
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL property when removing multiple nodes in LEFTIST Heap" << endl;
    if(tester.testRemoveNPLProperty(shop)){
      cout << "\tNPL property for removing nodes in a MIN-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNPL property  for removing nodes in a MIN-LEFTIST Heap failed!\n";
    }
  }

  // Test that removing nodes in a MAX-LEFTIST Heap maintains NPL property
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL property when removing multiple nodes in LEFTIST Heap" << endl;
    if(tester.testRemoveNPLProperty(shop)){
      cout << "\tNPL property for removing nodes in a MAX-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNPL property for removing nodes in a MAX-LEFTIST Heap failed!\n";
    }
  }

  // Test that removing nodes in a MIN-LEFTIST Heap maintains NPL values
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL values when removing multiple nodes in LEFTIST Heap" << endl;
    if(tester.testRemoveNPLValues(shop)){
      cout << "\tNPL values for removing nodes in a MIN-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNPL values for removing nodes in a MIN-LEFTIST Heap failed!\n";
    }
  }

  // Test that removing nodes in a MAX-LEFTIST Heap maintains NPL values
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL values when removing multiple nodes in LEFTIST Heap" << endl;
    if(tester.testRemoveNPLValues(shop)){
      cout << "\tNPL values for removing nodes in a MAX-LEFTIST Heap passed!\n";
    }else{
      cout << "\tNPL values for removing nodes in a MAX-LEFTIST Heap failed!\n";
    }
  }

  // Test that two populated SKEW-MIN heaps are merged
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);
    Shop rhs(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting normal case for merging heaps (SKEW-MIN)" << endl;
    if(tester.testMergeQueueNorm(shop, rhs)){
      cout << "\tNormal case for mergeWithQueue passed (SKEW-MIN)!\n";
    }else{
      cout << "\tNormal case for mergeWithQueue not passed (SKEW-MIN)!\n";
    }
  }

  // Test that two populated SKEW-MAX heaps are merged
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);
    Shop rhs(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting normal case for merging heaps (SKEW-MAX)" << endl;
    if(tester.testMergeQueueNorm(shop, rhs)){
      cout << "\tNormal case for mergeWithQueue passed (SKEW-MAX)!\n";
    }else{
      cout << "\tNormal case for mergeWithQueue not passed (SKEW-MAX)!\n";
    }
  }

  // Test that two populated LEFTIST-MIN heaps are merged
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting normal case for merging heaps (LEFTIST-MIN)" << endl;
    if(tester.testMergeQueueNorm(shop, rhs)){
      cout << "\tNormal case for mergeWithQueue passed (LEFTIST-MIN)!\n";
    }else{
      cout << "\tNormal case for mergeWithQueue failed (LEFTIST-MIN)!\n";
    }
  }

  // Test that two populated LEFTIST-MAX heaps are merged
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting normal case for merging heaps (LEFTIST-MAX)" << endl;
    if(tester.testMergeQueueNorm(shop, rhs)){
      cout << "\tNormal case for mergeWithQueue passed (LEFTIST-MAX)!\n";
    }else{
      cout << "\tNormal case for mergeWithQueue failed (LEFTIST-MAX)!\n";
    }
  }

  // Test that two populated LEFTIST-MIN heaps are merged and maintain the NPL property
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL property for merging heaps (LEFTIST-MIN)" << endl;
    if(tester.testMergeQueueNPL(shop, rhs)){
      cout << "\tNPL property for mergeWithQueue passed (LEFTIST-MIN)!\n";
    }else{
      cout << "\tNPL property for mergeWithQueue failed (LEFTIST-MIN)!\n";
    }
  }

  // Test that two populated LEFTIST-MAX heaps are merged and maintain the NPL property
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL property for merging heaps (LEFTIST-MAX)" << endl;
    if(tester.testMergeQueueNPL(shop, rhs)){
      cout << "\tNPL property for mergeWithQueue passed (LEFTIST-MAX)!\n";
    }else{
      cout << "\tNPL property for mergeWithQueue failed (LEFTIST-MAX)!\n";
    }
  }

  // Test that two populated LEFTIST-MIN heaps are merged and maintain the NPL values
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL values for merging heaps (LEFTIST-MIN)" << endl;
    if(tester.testMergeQueueNPLV(shop, rhs)){
      cout << "\tNPL values for mergeWithQueue passed (LEFTIST-MIN)!\n";
    }else{
      cout << "\tNPL values for mergeWithQueue failed (LEFTIST-MIN)!\n";
    }
  }

  // Test that two populated LEFTIST-MAX heaps are merged and maintain the NPL values
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL values for merging heaps (LEFTIST-MAX)" << endl;
    if(tester.testMergeQueueNPLV(shop, rhs)){
      cout << "\tNPL values for mergeWithQueue passed (LEFTIST-MAX)!\n";
    }else{
      cout << "\tNPL values for mergeWithQueue failed (LEFTIST-MAX)!\n";
    }
  }

  // Test that an empty heap merges with a full MIN-SKEW heap
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop emptyShop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);
    Shop rhs(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting edge case for merging heaps (MIN-SKEW)" << endl;
    if(tester.testMergeQueueEdge(emptyShop, rhs)){
      cout << "\tEdge case for mergeWithQueue passed! (MIN-SKEW)\n";
    }else{
      cout << "\tEdge case for mergeWithQueue failed! (MIN-SKEW)\n";
    }
  }

  // Test that an empty heap merges with a full MAX-SKEW heap
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop emptyShop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);
    Shop rhs(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting edge case for merging heaps (MAX-SKEW)" << endl;
    if(tester.testMergeQueueEdge(emptyShop, rhs)){
      cout << "\tEdge case for mergeWithQueue passed! (MAX-SKEW)\n";
    }else{
      cout << "\tEdge case for mergeWithQueue failed! (MAX-SKEW)\n";
    }
  }

  // Test that an empty heap merges with a full MIN-LEFTIST heap
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop emptyShop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting edge case for merging heaps (MIN-LEFTIST)" << endl;
    if(tester.testMergeQueueEdge(emptyShop, rhs)){
      cout << "\tEdge case for mergeWithQueue passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tEdge case for mergeWithQueue failed! (MIN-LEFTIST)\n";
    }
  }

  // Test that an empty heap merges with a full MAX-LEFTIST heap
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop emptyShop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting edge case for merging heaps (MAX-LEFTIST)" << endl;
    if(tester.testMergeQueueEdge(emptyShop, rhs)){
      cout << "\tEdge case for mergeWithQueue passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tEdge case for mergeWithQueue failed! (MAX-LEFTIST)\n";
    }
  }

  // Test that an empty heap merges with a full MIN-LEFTIST heap — NPL Property
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop emptyShop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL property for merging heaps (MIN-LEFTIST)" << endl;
    if(tester.testMergeQueueEdgeNPL(emptyShop, rhs)){
      cout << "\tNPL property for mergeWithQueue passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tNPL property for mergeWithQueue failed! (MIN-LEFTIST)\n";
    }
  }

  // Test that an empty heap merges with a full MAX-LEFTIST heap — NPL Property
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop emptyShop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL property for merging heaps (MAX-LEFTIST)" << endl;
    if(tester.testMergeQueueEdgeNPL(emptyShop, rhs)){
      cout << "\tNPL property for mergeWithQueue passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tNPL property for mergeWithQueue failed! (MAX-LEFTIST)\n";
    }
  }

  // Test that an empty heap merges with a full MIN-LEFTIST heap — NPL Values
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop emptyShop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL values for merging heaps (MIN-LEFTIST)" << endl;
    if(tester.testMergeQueueEdgeNPLV(emptyShop, rhs)){
      cout << "\tNPL values for mergeWithQueue passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tNPL values for mergeWithQueue failed! (MIN-LEFTIST)\n";
    }
  }

  // Test that an empty heap merges with a full MAX-LEFTIST heap — NPL Values
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();

    Shop emptyShop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting NPL values for merging heaps (MAX-LEFTIST)" << endl;
    if(tester.testMergeQueueEdgeNPLV(emptyShop, rhs)){
      cout << "\tNPL values for mergeWithQueue passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tNPL values for mergeWithQueue failed! (MAX-LEFTIST)\n";
    }
  }

  // Tests normal case for copy constructor for MIN-SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting normal case for copy constructor (MIN-SKEW)" << endl;
    if(tester.testCopyConstructorNorm(shop)){
      cout << "\tNormal case for copy constructor passed! (MIN-SKEW)\n";
    }else{
      cout << "\tNormal case for copy constructor failed! (MIN-SKEW)\n";
    }
  }

  // Tests normal case for copy constructor for MAX-SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting normal case for copy constructor (MAX-SKEW)" << endl;
    if(tester.testCopyConstructorNorm(shop)){
      cout << "\tNormal case for copy constructor passed! (MAX-SKEW)\n";
    }else{
      cout << "\tNormal case for copy constructor failed! (MAX-SKEW)\n";
    }
  }
  
  // Tests normal case for copy constructor for MIN-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting normal case for copy constructor (MIN-LEFTIST)" << endl;
    if(tester.testCopyConstructorNorm(shop)){
      cout << "\tNormal case for copy constructor passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tNormal case for copy constructor failed! (MIN-LEFTIST)\n";
    }
  }

  // Tests normal case for copy constructor for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting normal case for copy constructor (MAX-LEFTIST)" << endl;
    if(tester.testCopyConstructorNorm(shop)){
      cout << "\tNormal case for copy constructor passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tNormal case for copy constructor failed! (MAX-LEFTIST)\n";
    }
  }
  
  // Tests npl property for copy constructor for MIN-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting npl property for copy constructor (MIN-LEFTIST)" << endl;
    if(tester.testCopyConstructorNPL(shop)){
      cout << "\tNPL property for copy constructor passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tNPL property for copy constructor failed! (MIN-LEFTIST)\n";
    }
  }

  // Tests npl property for copy constructor for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting npl property for copy constructor (MAX-LEFTIST)" << endl;
    if(tester.testCopyConstructorNPL(shop)){
      cout << "\tNPL property for copy constructor passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tNPL property for copy constructor failed! (MAX-LEFTIST)\n";
    }
  }

  // Tests npl values for copy constructor for MIN-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting npl values for copy constructor (MIN-LEFTIST)" << endl;
    if(tester.testCopyConstructorNPLV(shop)){
      cout << "\tNPL values for copy constructor passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tNPL values for copy constructor failed! (MIN-LEFTIST)\n";
    }
  }

  // Tests npl values for copy constructor for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting npl values for copy constructor (MAX-LEFTIST)" << endl;
    if(tester.testCopyConstructorNPLV(shop)){
      cout << "\tNPL values for copy constructor passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tNPL values for copy constructor failed! (MAX-LEFTIST)\n";
    }
  }

  // Tests edge case for copy constructor for MIN-SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting edge case for copy constructor (MIN-SKEW)" << endl;
    if(tester.testCopyConstructorEdge(shop)){
      cout << "\tEdge case for copy constructor passed! (MIN-SKEW)\n";
    }else{
      cout << "\tEdge case for copy constructor failed! (MIN-SKEW)\n";
    }
  }
  
  // Tests edge case for copy constructor for MAX-SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    cout << "\nTesting edge case for copy constructor (MAX-SKEW)" << endl;
    if(tester.testCopyConstructorEdge(shop)){
      cout << "\tEdge case for copy constructor passed! (MAX-SKEW)\n";
    }else{
      cout << "\tEdge case for copy constructor failed! (MAX-SKEW)\n";
    }
  }

  // Tests edge case for copy constructor for MIN-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting edge case for copy constructor (MIN-LEFTIST)" << endl;
    if(tester.testCopyConstructorEdge(shop)){
      cout << "\tEdge case for copy constructor passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tEdge case for copy constructor failed! (MIN-LEFTIST)\n";
    }
  }

  // Tests edge case for copy constructor for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting edge case for copy constructor (MAX-LEFTIST)" << endl;
    if(tester.testCopyConstructorEdge(shop)){
      cout << "\tEdge case for copy constructor passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tEdge case for copy constructor failed! (MAX-LEFTIST)\n";
    }
  }

  // Tests normal case for overloaded assignment operator for MIN-SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn2, MINHEAP, SKEW, rndShopR, shopIDR);

    cout << "\nTesting normal case (1) for overloaded assignment operator (MIN-SKEW)" << endl;
    if(tester.testOvldAssignNorm1(shop, rhs)){
      cout << "\tNormal case (1) for overloaded assignment operator passed! (MIN-SKEW)\n";
    }else{
      cout << "\tNormal case (1) for overloaded assignment operator failed! (MIN-SKEW)\n";
    }
  }

  // Tests normal case for overloaded assignment operator for MAX-SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn1, MAXHEAP, SKEW, rndShopR, shopIDR);

    cout << "\nTesting normal case (1) for overloaded assignment operator (MAX-SKEW)" << endl;
    if(tester.testOvldAssignNorm1(shop, rhs)){
      cout << "\tNormal case (1) for overloaded assignment operator passed! (MAX-SKEW)\n";
    }else{
      cout << "\tNormal case (1) for overloaded assignment operator failed! (MAX-SKEW)\n";
    }
  }

  // Tests normal case for overloaded assignment operator for MIN-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting normal case (1) for overloaded assignment operator (MIN-LEFTIST)" << endl;
    if(tester.testOvldAssignNorm1(shop, rhs)){
      cout << "\tNormal case (1) for overloaded assignment operator passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tNormal case (1) for overloaded assignment operator failed! (MIN-LEFTIST)\n";
    }
  }
  
  // Tests normal case for overloaded assignment operator for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting normal case (1) for overloaded assignment operator (MAX-LEFTIST)" << endl;
    if(tester.testOvldAssignNorm1(shop, rhs)){
      cout << "\tNormal case (1) for overloaded assignment operator passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tNormal case (1) for overloaded assignment operator failed! (MAX-LEFTIST)\n";
    }
  }
  
  // Tests NPL property for overloaded assignment operator for MIN-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);
    
    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting NPL property (1) for overloaded assignment operator (MIN-LEFTIST)" << endl;
    if(tester.testOvldAssignNPL1(shop, rhs)){
      cout << "\tNPL property (1) for overloaded assignment operator passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tNPL property (1) for overloaded assignment operator failed! (MIN-LEFTIST)\n";
    }
  }
  
  // Tests NPL property for overloaded assignment operator for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting NPL property (1) for overloaded assignment operator (MAX-LEFTIST)" << endl;
    if(tester.testOvldAssignNPL1(shop, rhs)){
      cout << "\tNPL property (1) for overloaded assignment operator passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tNPL property (1) for overloaded assignment operator failed! (MAX-LEFTIST)\n";
    }
  }

  // Tests NPL values for overloaded assignment operator for MIN-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting NPL values (1) for overloaded assignment operator (MIN-LEFTIST)" << endl;
    if(tester.testOvldAssignNPLV1(shop, rhs)){
      cout << "\tNPL values (1) for overloaded assignment operator passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tNPL values (1) for overloaded assignment operator failed! (MIN-LEFTIST)\n";
    }
  }

  // Tests NPL values for overloaded assignment operator for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting NPL values (1) for overloaded assignment operator (MAX-LEFTIST)" << endl;
    if(tester.testOvldAssignNPLV1(shop, rhs)){
      cout << "\tNPL values (1) for overloaded assignment operator passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tNPL values (1) for overloaded assignment operator failed! (MAX-LEFTIST)\n";
    }
  }

  // Tests normal case for overloaded assignment operator for MIN-SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn2, MINHEAP, SKEW, rndShopR, shopIDR);

    cout << "\nTesting normal case (2) for overloaded assignment operator (MIN-SKEW)" << endl;
    if(tester.testOvldAssignNorm2(shop, rhs)){
      cout << "\tNormal case (2) for overloaded assignment operator passed! (MIN-SKEW)\n";
    }else{
      cout << "\tNormal case (2) for overloaded assignment operator failed! (MIN-SKEW)\n";
    }
  }

  // Tests normal case for overloaded assignment operator for MAX-SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn1, MAXHEAP, SKEW, rndShopR, shopIDR);

    cout << "\nTesting normal case (2) for overloaded assignment operator (MAX-SKEW)" << endl;
    if(tester.testOvldAssignNorm2(shop, rhs)){
      cout << "\tNormal case (2) for overloaded assignment operator passed! (MAX-SKEW)\n";
    }else{
      cout << "\tNormal case (2) for overloaded assignment operator failed! (MAX-SKEW)\n";
    }
  }

  // Tests normal case for overloaded assignment operator for MIN-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting normal case (2) for overloaded assignment operator (MIN-LEFTIST)" << endl;
    if(tester.testOvldAssignNorm2(shop, rhs)){
      cout << "\tNormal case (2) for overloaded assignment operator passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tNormal case (2) for overloaded assignment operator failed! (MIN-LEFTIST)\n";
    }
  }

  // Tests normal case for overloaded assignment operator for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting normal case (2) for overloaded assignment operator (MAX-LEFTIST)" << endl;
    if(tester.testOvldAssignNorm2(shop, rhs)){
      cout << "\tNormal case (2) for overloaded assignment operator passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tNormal case (2) for overloaded assignment operator failed! (MAX-LEFTIST)\n";
    }
  }

  // Tests npl property for overloaded assignment operator for MIN-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting npl property (2) for overloaded assignment operator (MIN-LEFTIST)" << endl;
    if(tester.testOvldAssignNPL2(shop, rhs)){
      cout << "\tNPL property (2) for overloaded assignment operator passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tNPL property (2) for overloaded assignment operator failed! (MIN-LEFTIST)\n";
    }
  }

  // Tests npl property for overloaded assignment operator for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting NPL property (2) for overloaded assignment operator (MAX-LEFTIST)" << endl;
    if(tester.testOvldAssignNPL2(shop, rhs)){
      cout << "\tNPL property (2) for overloaded assignment operator passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tNPL property (2) for overloaded assignment operator failed! (MAX-LEFTIST)\n";
    }
  }

  // Tests edge case for overloaded assignment operator for MIN-SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn2, MINHEAP, SKEW, rndShopR, shopIDR);

    cout << "\nTesting edge case for overloaded assignment operator (MIN-SKEW)" << endl;
    if(tester.testOvldAssignEdge(shop, rhs)){
      cout << "\tEdge case for overloaded assignment operator passed! (MIN-SKEW)\n";
    }else{
      cout << "\tEdge case for overloaded assignment operator failed! (MIN-SKEW)\n";
    }
  }

  // Tests edge case for overloaded assignment operator for MAX-SKEW HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, SKEW, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn1, MAXHEAP, SKEW, rndShopR, shopIDR);

    cout << "\nTesting edge case for overloaded assignment operator (MAX-SKEW)" << endl;
    if(tester.testOvldAssignEdge(shop, rhs)){
      cout << "\tEdge case for overloaded assignment operator passed! (MAX-SKEW)\n";
    }else{
      cout << "\tEdge case for overloaded assignment operator failed! (MAX-SKEW)\n";
    }
  }

  // Tests edge case for overloaded assignment operator for MIN-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn2, MINHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn2, MINHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting edge case for overloaded assignment operator (MIN-LEFTIST)" << endl;
    if(tester.testOvldAssignEdge(shop, rhs)){
      cout << "\tEdge case for overloaded assignment operator passed! (MIN-LEFTIST)\n";
    }else{
      cout << "\tEdge case for overloaded assignment operator failed! (MIN-LEFTIST)\n";
    }
  }

  // Tests edge case for overloaded assignment operator for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn1, MAXHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting edge case for overloaded assignment operator (MAX-LEFTIST)" << endl;
    if(tester.testOvldAssignEdge(shop, rhs)){
      cout << "\tEdge case for overloaded assignment operator passed! (MAX-LEFTIST)\n";
    }else{
      cout << "\tEdge case for overloaded assignment operator failed! (MAX-LEFTIST)\n";
    }
  }

  // Tests error case for getNextOrder for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    cout << "\nTesting error case for getNextOrder" << endl;
    if(tester.testDequeueErr(shop)){
      cout << "\tError case for getNextOrder passed!\n";
    }else{
      cout << "\tError case for getNextOrder failed!\n";
    }
  }

  // Tests error case for merging with a queue for MAX-LEFTIST HEAP
  {
    Random shopGen(10,30);
    Random rndShopID(SHOPMINID, SHOPMAXID);
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    Shop shop(priorityFn1, MAXHEAP, LEFTIST, rndShop, shopID);

    Random shopGenR(10,30);
    Random rndShopIDR(SHOPMINID, SHOPMAXID);
    int rndShopR = shopGenR.getRandNum();
    int shopIDR = rndShopIDR.getRandNum();
    Shop rhs(priorityFn1, MINHEAP, LEFTIST, rndShopR, shopIDR);

    cout << "\nTesting error case for merging with a queue" << endl;
    if(tester.testMergeQueueErr(shop, rhs)){
      cout << "\tError case for merging with a queue passed!\n";
    }else{
      cout << "\tError case for merging with a queue failed!\n";
    }
  }

  //-------------Region Tests--------------
  // Tests error case for merging with a queue for MAX-LEFTIST HEAP

  
  {
    Region region(4);
    cout << "\nTesting normal case for inserting shops" << endl;
    if(tester.testInsertShopsNorm(region)){
      cout << "\tNormal case for inserting shops passed!\n";
    }else{
      cout << "\tNormal case for inserting shops failed!\n";
    }
  }
  
  
  return 0;
}

// Test that inserted nodes maintain MIN-HEAP Property
bool Tester::testInsertMinNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		  static_cast<COUNT>(countGen.getRandNum()),
		  static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		  pointsGen.getRandNum(),
		  customerIDGen.getRandNum(),
		  orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }

  // Verifies m_heap exists
  if(shop.m_heap == nullptr){
    return false;
  }

  // Ensures that the size matches
  if(size != shop.m_size){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      return false;
    }
  }

  // Check for MIN-HEAP Condition
  if(shop.m_heapType == MINHEAP && shop.m_priorFunc == priorityFn2){
    return minHelper(shop.m_heap, retain, shop.m_priorFunc);
  }else{
    return false;
  }
}

// Test that inserted nodes maintain MAX-HEAP Property
bool Tester::testInsertMaxNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }

  // Verifies m_heap exists
  if(shop.m_heap == nullptr){
    return false;
  }

  // Ensures that the size matches
  if(size != shop.m_size){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      return false;
    }
  }

  // Check for MAX-HEAP Condition
  if(shop.m_heapType == MAXHEAP && shop.m_priorFunc == priorityFn1){
    return maxHelper(shop.m_heap, retain, shop.m_priorFunc);
  }else{
    return false;
  }
}

// Test that inserted nodes maintain NPL property in MIN LEFTIST HEAP
bool Tester::testInsertNPLProperty(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  // Check for NPL property
  return nplHelper(shop.m_heap, retain);
}

// Test that inserted nodes maintain NPL property in MAX LEFTIST HEAP
bool Tester::testInsertNPLValues(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  bool retain = true;
  int npl = 0;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  // Check for NPL property
  npl = nplVHelper(shop.m_heap, retain, npl, npl);

  return retain;
}

// Test that SKEW->LEFTIST HEAP maintains MIN-HEAP PROPERTY
bool Tester::testMinSkew2LeftistNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }
  
  // Set structure to LEFTIST
  shop.setStructure(LEFTIST);
  
  // Verifies m_heap exists
  if(shop.m_heap == nullptr){
    return false;
  }

  // Ensures that the size matches
  if(size != shop.m_size){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      return false;
    }
  }

  // Check for MIN-HEAP Condition
  return minHelper(shop.m_heap, retain, shop.m_priorFunc);
}

// Test that SKEW->LEFTIST HEAP maintains NPL PROPERTY in MIN-HEAP
bool Tester::testMinSkew2LeftistNPL(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  // Set structure to LEFTIST
  shop.setStructure(LEFTIST);

  // Check for NPL property
  return nplHelper(shop.m_heap, retain);
}

// Test that SKEW->LEFTIST HEAP maintains NPL Values in MIN-HEAP
bool Tester::testMinSkew2LeftistNPLV(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  int npl = 0;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  // Set structure to LEFTIST
  shop.setStructure(LEFTIST);

  // Check for NPL property
  npl = nplVHelper(shop.m_heap, retain, npl, npl);

  return retain;
}

// Test that LEFTIST->SKEW HEAP maintains MIN-HEAP PROPERTY
bool Tester::testMinLeftist2SkewNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }

  // Set structure to SKEW
  shop.setStructure(SKEW);

  // Verifies m_heap exists
  if(shop.m_heap == nullptr){
    return false;
  }

  // Ensures that the size matches
  if(size != shop.m_size){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      return false;
    }
  }
  
  // Check for MIN-HEAP Condition
  return minHelper(shop.m_heap, retain, shop.m_priorFunc);
}

// Test that SKEW->LEFTIST HEAP maintains MAX-HEAP PROPERTY
bool Tester::testMaxSkew2LeftistNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }

  // Set structure to LEFTIST
  shop.setStructure(LEFTIST);

  // Verifies m_heap exists
  if(shop.m_heap == nullptr){
    return false;
  }

  // Ensures that the size matches
  if(size != shop.m_size){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      return false;
    }
  }
  
  // Check for MAX-HEAP Condition
  return maxHelper(shop.m_heap, retain, shop.m_priorFunc);
}

// Test that SKEW->LEFTIST HEAP maintains NPL PROPERTY in MAX-HEAP
bool Tester::testMaxSkew2LeftistNPL(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  // Set structure to LEFTIST
  shop.setStructure(LEFTIST);
  
  // Check for NPL property
  return nplHelper(shop.m_heap, retain);
}

// Test that SKEW->LEFTIST HEAP maintains NPL Values in MAX-HEAP
bool Tester::testMaxSkew2LeftistNPLV(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  int npl = 0;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  // Set structure to LEFTIST
  shop.setStructure(LEFTIST);

  // Check for NPL property
  npl = nplVHelper(shop.m_heap, retain, npl, npl);

  return retain;
}

// Test that LEFTIST->SKEW HEAP maintains MAX-HEAP PROPERTY
bool Tester::testMaxLeftist2SkewNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }

  // Set structure to SKEW
  shop.setStructure(SKEW);

  // Verifies m_heap exists
  if(shop.m_heap == nullptr){
    return false;
  }

  // Ensures that the size matches
  if(size != shop.m_size){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      return false;
    }
  }
  
  // Check for MAX-HEAP Condition
  return maxHelper(shop.m_heap, retain, shop.m_priorFunc);
}

// Test that MIN->MAX SKEW HEAP maintains HEAP PROPERTY
bool Tester::testMinSkew2MaxSkewNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }

  // Set structure to LEFTIST
  shop.setPriorityFn(priorityFn1, MAXHEAP);

  // Verifies m_heap exists
  if(shop.m_heap == nullptr){
    return false;
  }

  // Ensures that the size matches
  if(size != shop.m_size){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      return false;
    }
  }

  // Check for NPL property
  return maxHelper(shop.m_heap, retain, shop.m_priorFunc);
}

// Test that MIN->MAX SKEW HEAP maintains HEAP PROPERTY
bool Tester::testMaxSkew2MinSkewNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }
  
  // Set structure to LEFTIST
  shop.setPriorityFn(priorityFn2, MINHEAP);

  // Verifies m_heap exists
  if(shop.m_heap == nullptr){
    return false;
  }

  // Ensures that the size matches
  if(size != shop.m_size){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      return false;
    }
  }

  // Check for MIN-HEAP property
  return minHelper(shop.m_heap, retain, shop.m_priorFunc);
}

// Test that MIN->MAX LEFTIST HEAP maintains HEAP PROPERTY
bool Tester::testMinLeftist2MaxLeftistNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }

  // Set heap type to MAXHEAP
  shop.setPriorityFn(priorityFn1, MAXHEAP);

  // Verifies m_heap exists
  if(shop.m_heap == nullptr){
    return false;
  }

  // Ensures that the size matches
  if(size != shop.m_size){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      return false;
    }
  }

  // Check for MAXHEAP property
  return maxHelper(shop.m_heap, retain, shop.m_priorFunc);
}

// Test that MIN->MAX LEFTIST HEAP maintains NPL PROPERTY
bool Tester::testMinLeftist2MaxLeftistNPL(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }
  
  // Set heap type to MAXHEAP
  shop.setPriorityFn(priorityFn1, MAXHEAP);

  // Check for NPL property
  return nplHelper(shop.m_heap, retain);
}

// Test that MIN->MAX LEFTIST HEAP maintains NPL Values
bool Tester::testMinLeftist2MaxLeftistNPLV(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  int npl = 0;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  // Set heap type to MAXHEAP
  shop.setPriorityFn(priorityFn1, MAXHEAP);

  // Check for NPL property
  npl = nplVHelper(shop.m_heap, retain, npl, npl);

  return retain;
}

// Test that MAX->MIN LEFTIST HEAP maintains HEAP PROPERTY
bool Tester::testMaxLeftist2MinLeftistNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }

  // Set heap type to MINHEAP
  shop.setPriorityFn(priorityFn2, MINHEAP);

  // Verifies m_heap exists
  if(shop.m_heap == nullptr){
    return false;
  }

  // Ensures that the size matches
  if(size != shop.m_size){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      return false;
    }
  }

  // Check for MINHEAP property
  return minHelper(shop.m_heap, retain, shop.m_priorFunc);
}

// Test that MAX->MIN LEFTIST HEAP maintains NPL PROPERTY
bool Tester::testMaxLeftist2MinLeftistNPL(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  // Set heap type to MAXHEAP
  shop.setPriorityFn(priorityFn2, MINHEAP);

  // Check for NPL property
  return nplHelper(shop.m_heap, retain);
}

// Test that MAX->MIN LEFTIST HEAP maintains NPL Values
bool Tester::testMaxLeftist2MinLeftistNPLV(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  int npl = 0;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  // Set heap type to MAXHEAP
  shop.setPriorityFn(priorityFn2, MINHEAP);

  // Check for NPL property
  npl = nplVHelper(shop.m_heap, retain, npl, npl);
  
  return retain;
}

// Test normal case for removing nodes from the min-heap
bool Tester::testRemoveMinNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  int removed = 100;
  bool retain = true;
  int removeID = 0;
  int removedID = 0;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  
  for(int i = 0; i < removed; i++){
    removeID = shop.m_heap->getOrderID();
    removedID = (shop.getNextOrder()).getOrderID();
    
    if(removeID != removedID){
      return false;
    }
    
  }
  
  if(shop.m_size != size - removed){
    return false;
  }

  // Check for MINHEAP property
  if(shop.m_heapType == MINHEAP && shop.m_priorFunc == priorityFn2){
    return minHelper(shop.m_heap, retain, shop.m_priorFunc);
  }
  else{
    return false;
  }
}

// Test normal case for removing nodes from the max-heap
bool Tester::testRemoveMaxNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  int removed = 100;
  bool retain = true;
  int removeID = 0;
  int removedID = 0;

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }


  for(int i = 0; i < removed; i++){
    removeID = shop.m_heap->getOrderID();
    removedID = (shop.getNextOrder()).getOrderID();

    if(removeID != removedID){
      return false;
    }

  }

  if(shop.m_size != size - removed){
    return false;
  }

  // Check for MAXHEAP property
  if(shop.m_heapType == MAXHEAP && shop.m_priorFunc == priorityFn1){
    return maxHelper(shop.m_heap, retain, shop.m_priorFunc);
  }
  else{
    return false;
  }
}

// Test that MAX->MIN LEFTIST HEAP maintains NPL PROPERTY
bool Tester::testRemoveNPLProperty(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  int removed = 100;
  bool retain = true;
  int removeID = 0;
  int removedID = 0;

  if(shop.m_structure == SKEW){
    return false;
  }

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  for(int i = 0; i < removed; i++){
    removeID = shop.m_heap->getOrderID();
    removedID = (shop.getNextOrder()).getOrderID();

    if(removeID != removedID){
      return false;
    }

  }

  if(shop.m_size != size - removed){
    return false;
  }

  // Check for NPL property
  return nplHelper(shop.m_heap, retain);
}

bool Tester::testRemoveNPLValues(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  int removed = 200;
  bool retain = true;
  int npl = 0;
  int removeID = 0;
  int removedID = 0;

  if(shop.m_structure == SKEW){
    return false;
  }

  for (int i = 0; i < size; i++){
    // Insert several orders into a shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  for(int i = 0; i < removed; i++){
    removeID = shop.m_heap->getOrderID();
    removedID = (shop.getNextOrder()).getOrderID();

    if(removeID != removedID){
      return false;
    }

  }

  if(shop.m_size != size - removed){
    return false;
  }

  // Check for NPL property
  npl = nplVHelper(shop.m_heap, retain, npl, npl);
  
  return retain;
}

// Test to make sure two populated queues are merged
bool Tester::testMergeQueueNorm(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order ordersL[size];
  Order ordersR[size];
  bool retain = true;
  bool existsL = false;
  bool existsR = false;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order orderL(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    Order orderR(static_cast<ITEM>(itemGen.getRandNum()),
		 static_cast<COUNT>(countGen.getRandNum()),
		 static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		 pointsGen.getRandNum(),
		 customerIDGen.getRandNum(),
		 orderIDGen.getRandNum());

    shop.insertOrder(orderL);
    rhs.insertOrder(orderR);
    ordersL[i] = orderL;
    ordersR[i] = orderR;
  }

  shop.mergeWithQueue(rhs);

  if(!(shop.m_heap)){
    return false;
  }

  if(rhs.m_heap){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, ordersL[i], existsL)){
      return false;
    }
    if(!findNode(shop.m_heap, ordersR[i], existsR)){
      return false;
    }
  }

  if(shop.m_heapType == MINHEAP && shop.m_priorFunc == priorityFn2){
    return minHelper(shop.m_heap, retain, shop.m_priorFunc);
  }else if(shop.m_heapType == MAXHEAP && shop.m_priorFunc == priorityFn1){
    return maxHelper(shop.m_heap, retain, shop.m_priorFunc);
  }else{
    return false;
  }
}

// Test to make sure two populated queues are merged and maintain NPL property
bool Tester::testMergeQueueNPL(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order ordersL[size];
  Order ordersR[size];
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order orderL(static_cast<ITEM>(itemGen.getRandNum()),
		 static_cast<COUNT>(countGen.getRandNum()),
		 static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		 pointsGen.getRandNum(),
		 customerIDGen.getRandNum(),
		 orderIDGen.getRandNum());

    Order orderR(static_cast<ITEM>(itemGen.getRandNum()),
		 static_cast<COUNT>(countGen.getRandNum()),
		 static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		 pointsGen.getRandNum(),
		 customerIDGen.getRandNum(),
		 orderIDGen.getRandNum());

    shop.insertOrder(orderL);
    rhs.insertOrder(orderR);
    ordersL[i] = orderL;
    ordersR[i] = orderR;
  }

  shop.mergeWithQueue(rhs);

  // Check for NPL property
  return nplHelper(shop.m_heap, retain);
}

// Test to make sure two populated queues are merged and maintain NPL values
bool Tester::testMergeQueueNPLV(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order ordersL[size];
  Order ordersR[size];
  int npl = 0;
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order orderL(static_cast<ITEM>(itemGen.getRandNum()),
		 static_cast<COUNT>(countGen.getRandNum()),
		 static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		 pointsGen.getRandNum(),
		 customerIDGen.getRandNum(),
		 orderIDGen.getRandNum());

    Order orderR(static_cast<ITEM>(itemGen.getRandNum()),
		 static_cast<COUNT>(countGen.getRandNum()),
		 static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		 pointsGen.getRandNum(),
		 customerIDGen.getRandNum(),
		 orderIDGen.getRandNum());

    shop.insertOrder(orderL);
    rhs.insertOrder(orderR);
    ordersL[i] = orderL;
    ordersR[i] = orderR;
  }

  shop.mergeWithQueue(rhs);

  // Check for NPL property
  npl = nplVHelper(shop.m_heap, retain, npl, npl);

  return retain;
}

// Testing that an empty heap and populated heap merge
bool Tester::testMergeQueueEdge(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    rhs.insertOrder(order);
    orders[i] = order;
  }

  shop.mergeWithQueue(rhs);

  if(!(shop.m_heap)){
    return false;
  }

  if(rhs.m_heap){
    return false;
  }

  // Verifies each node has been inserted
  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      return false;
    }
  }
  
  return true;
}

// Testing that an empty heap and populated heap merge — NPL Property
bool Tester::testMergeQueueEdgeNPL(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    rhs.insertOrder(order);
    orders[i] = order;
  }

  shop.mergeWithQueue(rhs);

  // Check for NPL property
  return nplHelper(shop.m_heap, retain);
}

// Testing that an empty heap and populated heap merge — NPL values
bool Tester::testMergeQueueEdgeNPLV(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  int npl = 0;
  Order orders[size];
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    rhs.insertOrder(order);
    orders[i] = order;
  }

  shop.mergeWithQueue(rhs);

  // Check for NPL property
  npl = nplVHelper(shop.m_heap, retain, npl, npl);

  return retain;
}

// Tests normal case for copyconstructor
bool Tester::testCopyConstructorNorm(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool correct = true;
  
  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }

  Shop newShop(shop);

  if(!(newShop.m_heap)){
    return false;
  }

  if(shop.m_size != newShop.m_size){
    return false;
  }

  if(shop.m_heap == newShop.m_heap){
    return false;
  }

  for(int i = 0; i < size; i++){
    if(!findNode(newShop.m_heap, orders[i], exists)){
      if(!exists){
	return false;
      }
    }
  }

  return equalityHelper(shop.m_heap, newShop.m_heap, correct);
}

// Tests NPL property for copyconstructor
bool Tester::testCopyConstructorNPL(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }

  Shop newShop(shop);

  // Check for NPL property
  return nplHelper(shop.m_heap, retain);
}

// Tests NPL values for copyconstructor
bool Tester::testCopyConstructorNPLV(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  int npl = 0;
  Order orders[size];
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    orders[i] = order;
  }

  Shop newShop(shop);

  // Check for NPL property
  npl = nplVHelper(shop.m_heap, retain, npl, npl);
  return retain;
}

// Tests edge case for copy constructor by copying empty heap
bool Tester::testCopyConstructorEdge(Shop &shop){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);

  Shop newShop(shop);

  if(newShop.m_heap){
    return false;
  }

  if(shop.m_size != newShop.m_size){
    return false;
  }

  if(newShop.m_size != 0){
    return false;
  }

  return true;  
}

// Tests normal case for overloaded assignment operator (two populated heaps)
bool Tester::testOvldAssignNorm1(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool correct = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    Order orderR(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
    rhs.insertOrder(orderR);
    orders[i] = orderR;
  }

  shop = rhs;

  if(!(shop.m_heap)){
    return false;
  }

  if(shop.m_size != rhs.m_size){
    return false;
  }

  if(shop.m_heap == rhs.m_heap){
    return false;
  }

  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      if(!exists){
	return false;
      }
    }
  }

  return equalityHelper(rhs.m_heap, shop.m_heap, correct);
}

// Tests normal case for overloaded assignment operator (two populated heaps) — NPL Property
bool Tester::testOvldAssignNPL1(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    Order orderR(static_cast<ITEM>(itemGen.getRandNum()),
		 static_cast<COUNT>(countGen.getRandNum()),
		 static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		 pointsGen.getRandNum(),
		 customerIDGen.getRandNum(),
		 orderIDGen.getRandNum());

    shop.insertOrder(order);
    rhs.insertOrder(orderR);
    orders[i] = orderR;
  }

  shop = rhs;

  // Check for NPL property
  return nplHelper(shop.m_heap, retain);
}

// Tests normal case for overloaded assignment operator (two populated heaps) — NPL Property
bool Tester::testOvldAssignNPLV1(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool retain = true;
  int npl = 0;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    Order orderR(static_cast<ITEM>(itemGen.getRandNum()),
		 static_cast<COUNT>(countGen.getRandNum()),
		 static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		 pointsGen.getRandNum(),
		 customerIDGen.getRandNum(),
		 orderIDGen.getRandNum());

    shop.insertOrder(order);
    rhs.insertOrder(orderR);
    orders[i] = orderR;
  }

  shop = rhs;

  // Check for NPL property
  npl = nplVHelper(shop.m_heap, retain, npl, npl);
  return retain;
}

// Tests normal case for overloaded assignment operator (RHS is populated, LHS is not)
bool Tester::testOvldAssignNorm2(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool exists = false;
  bool correct = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order orderR(static_cast<ITEM>(itemGen.getRandNum()),
		 static_cast<COUNT>(countGen.getRandNum()),
		 static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		 pointsGen.getRandNum(),
		 customerIDGen.getRandNum(),
		 orderIDGen.getRandNum());

    rhs.insertOrder(orderR);
    orders[i] = orderR;
  }

  shop = rhs;

  if(!(shop.m_heap)){
    return false;
  }

  if(shop.m_size != rhs.m_size){
    return false;
  }

  if(shop.m_heap == rhs.m_heap){
    return false;
  }

  for(int i = 0; i < size; i++){
    if(!findNode(shop.m_heap, orders[i], exists)){
      if(!exists){
	return false;
      }
    }
  }

  return equalityHelper(rhs.m_heap, shop.m_heap, correct);
}

// Tests NPL property for overloaded assignment operator (RHS is populated, LHS is not)
bool Tester::testOvldAssignNPL2(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  Order orders[size];
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order orderR(static_cast<ITEM>(itemGen.getRandNum()),
		 static_cast<COUNT>(countGen.getRandNum()),
		 static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		 pointsGen.getRandNum(),
		 customerIDGen.getRandNum(),
		 orderIDGen.getRandNum());

    rhs.insertOrder(orderR);
    orders[i] = orderR;
  }

  shop = rhs;

  // Check for NPL property
  return nplHelper(shop.m_heap, retain);
}

// Tests NPL values for overloaded assignment operator (RHS is populated, LHS is not)
bool Tester::testOvldAssignNPLV2(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;
  int npl = 0;
  Order orders[size];
  bool retain = true;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order orderR(static_cast<ITEM>(itemGen.getRandNum()),
		 static_cast<COUNT>(countGen.getRandNum()),
		 static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		 pointsGen.getRandNum(),
		 customerIDGen.getRandNum(),
		 orderIDGen.getRandNum());

    rhs.insertOrder(orderR);
    orders[i] = orderR;
  }

  shop = rhs;

  // Check for NPL property
  npl = nplVHelper(shop.m_heap, retain, npl, npl);

  return retain;
}

// Tests edge case for ovld assignment by copying an empty heap into a populated heap
bool Tester::testOvldAssignEdge(Shop &shop, Shop &rhs){
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  int size = 300;

  for (int i = 0; i < size; i++){
    // Insert several orders into the rhs shop
    Order order(static_cast<ITEM>(itemGen.getRandNum()),
		static_cast<COUNT>(countGen.getRandNum()),
		static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		pointsGen.getRandNum(),
		customerIDGen.getRandNum(),
		orderIDGen.getRandNum());

    shop.insertOrder(order);
  }

  shop = rhs;

  if(shop.m_heap){
    return false;
  }

  if(shop.m_size != rhs.m_size){
    return false;
  }

  if(shop.m_size != 0){
    return false;
  }

  return true;
}

bool Tester::testDequeueErr(Shop &shop){
  try{
    shop.getNextOrder();
  }
  catch(const out_of_range& e){
    return true;
  }
  return false;
  
}

bool Tester::testMergeQueueErr(Shop &shop, Shop &rhs){
  try{
    shop.mergeWithQueue(rhs);
  }
  catch(const domain_error& e){
    return true;
  }
  return false;
  
}

bool Tester::equalityHelper(Order* root, Order* copy, bool &correct){
  if(!root && !copy){
  
    if(root == copy){
      correct = false;
      return correct;
    }

    if(root->m_orderID != copy->m_orderID){
      correct = false;
      return correct;
    }

    equalityHelper(root->m_left, copy->m_left, correct);
    equalityHelper(root->m_right, copy->m_right, correct);
  }
  
  return correct;
}

// Helper function that checks if an order is in the heap
bool Tester::findNode(Order* root, Order order, bool &exists){
  // Only checks while the node is not found and while the root is not null
  if(!exists){
    if(root){
      if(root->getOrderID() == order.getOrderID()){
	exists = true;
      }
      // Traverse the heap
      findNode(root->m_left, order, exists);
      findNode(root->m_right, order, exists);
    }
  }
  
  return exists;
}

// Helper function that verifies MAX-HEAP property
bool Tester::maxHelper(Order* root, bool &retain,  prifn_t priorFunc){
  if(root){
    if(root->m_left){
      // If left node has larger prior than parent, return false;
      if(priorFunc(*(root->m_left)) > priorFunc(*root)){
	retain = false;
      }
    }
    // If left node has larger prior than parent, return false;
    if(root->m_right){
      if(priorFunc(*(root->m_right)) > priorFunc(*root)){
	retain = false;
      }
    }
    // Check subsequent nodes
    retain = maxHelper(root->m_left, retain, priorFunc);
    retain = maxHelper(root->m_right, retain, priorFunc);
  }

  return retain;
}

// Helper function that verifies MIN-HEAP property
bool Tester::minHelper(Order* root, bool &retain,  prifn_t priorFunc){
  if(root){
    // If left node has smaller prior than parent, return false;
    if(root->m_left){
      if(priorFunc(*(root->m_left)) < priorFunc(*root)){
	retain = false;
      }
    }
    // If right node has smaller prior than parent, return false;
    if(root->m_right){
      if(priorFunc(*(root->m_right)) < priorFunc(*root)){
	retain = false;
      }
    }
    // Check subsequent nodes
    retain = minHelper(root->m_left, retain, priorFunc);
    retain = minHelper(root->m_right, retain, priorFunc);
  }

  return retain;
}

// Helper function that verifies NPL-LEFTIST property
bool Tester::nplHelper(Order* root, bool &retain){
  if(root){
    // Check subsequent nodes
    retain = nplHelper(root->m_left, retain);
    retain = nplHelper(root->m_right, retain);

    // If there is a right node, but no left node, return false
    if(!root->m_left && root->m_right){
      retain = false;
    }
    // If the right subtree has a higher npl than the left, return false
    else if(root->m_left && root->m_right){
      if(root->m_left->m_npl < root->m_right->m_npl){
	retain = false;
      }
    } 
  }
  
  return retain;
}

// Helper function that makes sure NPL values are correct
int Tester::nplVHelper(Order* root, bool &retain, int left, int right){
  int npl = 0;

  if(!root){
    return -1;
  }

  left = nplVHelper(root->m_left, retain, left, right) + 1;
  right = nplVHelper(root->m_right, retain, left, right) + 1;

  if(left <= right){
    npl = left;
  }else{
    npl = right;
  }

  if(npl != root->m_npl){
    retain = false;
  }

  return npl;
}

bool Tester::testInsertShopsNorm(Region &region){
  Random shopGen(10,30); // this generates same priority numbers too
  Random orderIDGen(MINORDERID,MAXORDERID);
  Random countGen(ONE, DOZEN);
  Random customerIDGen(MINCUSTID,MAXCUSTID);
  Random membershipGen(TIER1,TIER6);
  Random pointsGen(MINPOINTS,MAXPOINTS);
  Random itemGen(COFFEE,ICEDTEA);
  Random rndShopID(SHOPMINID, SHOPMAXID);
  bool retain = true;
  int size = region.m_capacity;
  
  for (int j = 0; j < size - 1; j++){
    int rndShop = shopGen.getRandNum();
    int shopID = rndShopID.getRandNum();
    // create a Shop object
    Shop aShop(priorityFn2, MINHEAP, SKEW, rndShop, shopID);

    for (int i=0;i<5;i++){
      // create multiple Order objects
      Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
		    static_cast<COUNT>(countGen.getRandNum()),
		    static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
		    pointsGen.getRandNum(),
		    customerIDGen.getRandNum(),
		    orderIDGen.getRandNum());
      // insert orders into shop
      aShop.insertOrder(anOrder);
    }

    region.addShop(aShop);
    /*
    if(region.addShop(aShop) == false){
      return false;
    }
    */
  }

  if(!(region.m_heap)){
    return false;
  }

  if(region.m_capacity - 1 != region.m_size){
    cout << region.m_capacity << endl;
    cout << region.m_size << endl;
    return false;
  }
  
  return minHelperReg(region, region.m_heap, retain);
}

bool Tester::minHelperReg(Region region, Shop* heap, bool &retain){  
  for(int i = ROOTINDEX; i < region.m_size; i++){
    if(i%2 == 0 && i * 2 < region.m_size){
      if(heap[i].m_regPrior > heap[i*2].m_regPrior){
	retain = false;
      }
    }
      
    if(i%2 == 1 && (i * 2)+1 < region.m_size){  
      if(heap[i].m_regPrior > heap[(i * 2)+1].m_regPrior){
	retain = false;
      }
    }
  }
  
  return retain;
}

int priorityFn1(const Order &order) {
  //this function works with a MAXHEAP
  //priority value is determined based on some criteria
  //priority value falls in the range [0-5003]
  //the highest priority would be 3+5000 = 5003
  //the lowest priority would be 0+0 = 0 => 1
  //the larger value means the higher priority
  int priority = static_cast<int>(order.getCount()) + order.getPoints();
  if (priority == 0 ) priority = 1;
  return priority;
}

int priorityFn2(const Order &order) {
  //this function works with a MINHEAP
  //priority value is determined based on some criteria
  //priority value falls in the range [0-10]
  //the highest priority would be 0+0 = 0 => 1
  //the lowest priority would be 5+5 =10
  //the smaller value means the higher priority
  int priority = static_cast<int>(order.getItem()) + static_cast<int>(order.getMemebership());
  if (priority == 0 ) priority = 1;
  return priority;
}
