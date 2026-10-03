// UMBC - CMSC 341 - Spring 2026 - Proj0
/*
** File: art.cpp
** Author: Jaylen Jenkins
** Date: 02/10/2026
** E-mail: fp31977@gl.umbc.edu
**
** This file provides the implementation for creating a grid of randomized colored squares.
** Grids can be populated, cleared, and appended.
** Cells can be rotated and reversed.
*/
#include "art.h"

// Art::Art
// Given nothing — Returns nothing
Art::Art(){
  // Sets default values to grid height, width, and array.
  m_height = 0;
  m_width = 0;
  m_painting = nullptr;
}

// Art::Art
// Given grid height and width — Returns nothing
Art::Art(int height, int width){
  // If either the height or width are less than or equal to 0, set both to 0
  // Otherwise, initialize with given values.
  if(height <= 0 || width <= 0){
    m_height = 0;
    m_width = 0;
  }else{
    m_height = height;
    m_width = width;
  }

  // Create 2D Structure with a 1D-size of m_height
  // Each m_height cell contains an array of size width
  m_painting = new int*[m_height]{};
  for(int i = 0; i < m_height; i++){
    (m_painting)[i] = new int[m_width]{0};
  }

  for(int i = 0; i < m_height; i++){
    for(int j = 0; j < m_width; j++){
    } 
  }
}

// Art:~Art
// Given nothing — Returns nothing
Art::~Art(){
  // Cycles through m_painting and deletes each dynamically allocated pointer
  for(int i = 0; i < m_height; i++){
    m_painting[i] = nullptr;
    delete m_painting[i];
  }
  m_painting = nullptr;
  delete m_painting;
}

// Art::clear
// Given nothing — Returns nothing
void Art::clear(){
  // Cycles through m_painting and deletes each dynamically allocated pointer
  for(int i = 0; i < m_height; i++){
    m_painting[i] = nullptr;
    delete m_painting[i];
  }
  m_painting = nullptr;
  delete m_painting;

  // Defaults member variables
  m_width = 0;
  m_height = 0;
  m_painting = nullptr;
}

// Art::create
// Given a seed — Returns nothing
void Art::create(int initiate){
  // Creates a Random object with bounds 10–99 and initiates the seed
  Random randObj(10, 99);
  randObj.setSeed(initiate);

  // Cycles through m_painting and populates each cell with a random number
  for(int i = 0; i < m_height; i++){
    for(int j = 0; j < m_width; j++){
      m_painting[i][j] = randObj.getRandNum();
    }
  }
}

void Art::dumpColors(string pixel) const{
  if (m_height > 0 && m_width > 0 && m_painting != nullptr){
    for (int i=1;i <= m_height;i++){
      for (int j=1;j<=m_width;j++){
	std::cout << "\x1b[38;5;" << to_string(m_painting[i-1][j-1]) << "m" << pixel << pixel << RESET;
      }
      cout << endl;
    }
    cout << endl;
  }
}
void Art::dumpValues() const{
  if (m_height > 0 && m_width > 0 && m_painting != nullptr){
    for (int i=1;i <= m_height;i++){
      for (int j=1;j<=m_width;j++){
	cout << m_painting[i-1][j-1] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
}

// Art::Art
// Given an Art object to be copied — Returns nothing
Art::Art(const Art& rhs){
  // Sets current member variables equal to the given's
  m_height = rhs.m_height;
  m_width = rhs.m_width;

  // Cycles through m_painting and populates each cell with the value in the given's
  m_painting = new int*[m_height]{};
  for(int i = 0; i < m_width; i++){
    m_painting[i] = new int[m_width]{0};
  }
  
  for(int i = 0; i < m_height; i++){
    for(int j = 0; j < m_width; j++){
      m_painting[i][j] = rhs.m_painting[i][j];
    }
  }
}

// Art::operator=
// Given an art object to be copied from — Returns nothing
const Art& Art::operator=(const Art& rhs){
  // If the given and current Art object are the same, return
  if(&rhs == this){
    return *this;
  }
  
  // Equates m_vars with the given's
  m_height = rhs.m_height;
  m_width = rhs.m_width;

  // Resets m_painting and populates it with the given's values
  m_painting = nullptr;
  delete m_painting;

  m_painting = new int*[m_height]{};
  for(int i = 0; i < m_width; i++){
    m_painting[i] = new int[m_width]{0};
  }

  for(int i = 0; i < m_height; i++){
    for(int j = 0; j < m_width; j++){
      m_painting[i][j] = (rhs.m_painting)[i][j];
    }
  }

  return *this;
}

// Art::left2Right
// Given the Art object to be appended — Returns whether operation succeeded
bool Art::left2Right(const Art& rhs){
  // If the objects do not have the same height, operation fails
  if(m_height != rhs.m_height){
    return false;
  }

  // If the objects size is 0, the operation fails
  if(m_height * m_width == 0 && rhs.m_height * rhs.m_width == 0){
    return false;
  }

  // Create a temporary art object with a modified width
  Art tempArt(m_height, m_width + rhs.m_width);

  // Adds the cells from the original object to a temp object
  for(int i = 0; i < m_height; i++){
    for(int j = 0; j < m_width; i++){
      (tempArt.m_painting)[i][j] = m_painting[i][j];
    }

    tempArt.clear();
  }

  // Adds the cells from rhs to the rhs of the temp object
  for(int i = 0; i < int(sizeof(m_painting)); i++){
    for(int j = 0; j < int(sizeof(m_painting[i])); i++){
      (tempArt.m_painting)[i+m_width][j] = m_painting[i][j];
    }
  }

  // Sets the current Art object equal to the temp object
  *this = tempArt;

  return true;
}

// Art::top2Bottom
// Given the Art object to be appended — Returns whether operation succeeded
bool Art::top2Bottom(const Art& bottom){
  // If the objects do not have the same width, the operation fails
  if(m_width != bottom.m_width){
    return false;
  }

  // If the objects' sizes are 0, then the operation fails
  if(m_height * m_width == 0 && bottom.m_height * bottom.m_width == 0){
    return false;
  }

  //Creates a temporary art object with a modified height
  Art tempArt(m_height + bottom.m_height, m_width);

  // Adds the cells from the original object to a temp object
  for(int i = 0; i < m_height; i++){
    for(int j = 0; j < m_width; j++){
      (tempArt.m_painting)[i][j] = m_painting[i][j];
    }
  }

  // Adds the cells from rhs to the rhs of the temp object
  for(int i = 0; i < bottom.m_height; i++){
    for(int j = 0; j < bottom.m_width; j++){
      (tempArt.m_painting)[i+m_height][j] = bottom.m_painting[i][j];
    }
  }

  *this = tempArt;
  tempArt.clear();

  return true;
}

// Art::reverse
// Given nothing — Returns whether operation succeeded
bool Art::reverse(){
  if(m_height * m_width == 0 || m_height * m_width == 1){
    return false;
  }

  Art tempArt = *this;

  for(int i = 0; i < m_height; i++){
    for(int j = 0; j < m_width; j++){
      m_painting[i][j] = (tempArt.m_painting)[m_height - 1 - i][(m_width - 1 - j)];
    }
  }
  tempArt.clear();
  return true;
}

// Art::rotate
// Given nothing — Returns whether operation succeeded
bool Art::rotate(){
  if(m_height * m_width <= 4 || m_painting == nullptr){
    return false;
  }

  if((m_height * m_width) % 2 == 1){
    return false;
  }

  int temp;

  //for(int i = 0; i < m_height/2 -1...
  // Swap Q1 and Q2
  for(int i = 0; i < m_height/2; i++){
    for(int j = 0; j < m_width/2; j++){
      temp = m_painting[i][j];
      m_painting[i][j] = m_painting[i][j + m_width/2];
      m_painting[i][j + m_width/2] = temp;
    }
  }

  // Swap Q1 and Q3
  for(int i = 0; i < m_height/2; i++){
    for(int j = 0; j < m_width/2; j++){
      temp = m_painting[i + m_height][j];
      m_painting[i + m_height/2][j] = m_painting[i][j];
      m_painting[i][j] = temp;
    }
  }

// Swap Q3 and Q4
  for(int i = 0; i < m_height/2; i++){
    for(int j = 0; j < m_width/2; j++){
      temp = m_painting[i + m_height/2][j + m_width/2];
      m_painting[i + m_height/2][j + m_width/2] = m_painting[i + m_height/2][j];
      m_painting[i + m_height/2][j] = temp;
    }
  }

  return true;
}
