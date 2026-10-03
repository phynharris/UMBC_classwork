#include "art.h"

class Tester{
public:
  bool testConstructEdge(Art &art);
  bool testConstructError(Art &art);

  bool testCreateNormal(Art &art);
  bool testCopyConstructNormal(Art &art);

private:
  
};

int main(){

  Tester tester;
  {
    Art art(0,0);
    cout << "\nTesting the edge case of create function:\n\n";
    if (tester.testConstructEdge(art) == true)
      cout << "\tEdge case of default constructor passed!\n";
    else
      cout << "\tEdge case of default constructor failed!\n";
  }
  
  {
    Art art(0,1);
    cout << "\nTesting the edge case of create function:\n\n";
    if (tester.testConstructEdge(art) == true)
      cout << "\tEdge case of default constructor passed!\n";
    else
      cout << "\tEdge case of default constructor failed!\n";
  }

  {
    Art art(4,0);
    cout << "\nTesting the edge case of create function:\n\n";
    if (tester.testConstructEdge(art) == true)
      cout << "\tEdge case of default constructor passed!\n";
    else
      cout << "\tEdge case of default constructor failed!\n";
  }

  {
    Art art(-1,-1);
    cout << "\nTesting the edge case of create function:\n\n";
    if (tester.testConstructError(art) == true)
      cout << "\tError case of default constructor passed!\n";
    else
      cout << "\tError case of default constructor failed!\n";
  }

  {
    // testing create function for normal case (provided from driver.cpp)
    Art art(10,10);
    art.create(2);
    cout << "\nTesting the normal case of create function:\n\n";
    if (tester.testCreateNormal(art) == true)
      cout << "\tNormal case of create passed!\n";
    else
      cout << "\tNormal case of create failed!\n";


    cout << "\nTesting the normal case of a copy constructor:\n\n";
    if(tester.testCopyConstructNormal(art) == true){
      cout << "\t Normal case of copy constructor passed!\n";
    }else{
      cout << "\t Normal case of copy constructor failed!\n";
    }

    Art art2(7, 4);
    art2.create(10);
    cout << "\nTesting the normal case of a copy constructor 2:\n\n";
    if(tester.testCopyConstructNormal(art2) == true){
      cout << "\t Normal case of copy constructor 2 passed!\n";
    }else{
      cout << "\t Normal case of copy constructor 2 failed!\n";
    }
  }

  cout << endl;
  return 0;
}

bool Tester::testConstructEdge(Art &art){
  if((art.m_height != 0 && art.m_width != 0) && art.m_painting != nullptr){
    cout << "Empty object not created\n";
    return false;
  }else{
    return true;
  }
}

bool Tester::testConstructError(Art & art){
  if((art.m_height < 0 || art.m_width < 0) && art.m_painting != nullptr){
    cout << "Negative object created." << endl;
    return false;
  }else{
    return true;
  }
}

bool Tester::testCreateNormal(Art & art){
  // this function assumes the art object is not empty
  // all color codes must be within the correct range
  bool result = true;
  art.create(10);
  if (art.m_height > 0 && art.m_width > 0 && art.m_painting != nullptr){
    for (int i=0; i < art.m_height; i++){
      for (int j=0; j < art.m_width; j++){
	if(art.m_painting[i][j] < 10 ||
	   art.m_painting[i][j] > 99)
	  result = false;
      }
    }
  }
  else{
    result = false;
    cout << "\tA proper object is not passed to testCreateNormal()\n";
  }
  return result;
}

bool Tester::testCopyConstructNormal(Art &art){
  Art art2(art);
  if(art.m_painting != nullptr && art2.m_painting != nullptr && art.m_painting == art2.m_painting){
    cout << "\t object not properly copied in copy constructor\n";
    return false;
  }
  return true;
}
