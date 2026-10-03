//Title: proj5.cpp
//Author: Jeremy Dixon
//Date: 11/10/2025
//Description: Creates a new SongPlayer
#include <iostream>
#include "SongPlayer.h"
#include "Song.h"

using namespace std;

// Main can have multiple arguments with it
// argc is the number of arguments (starts at 1)
// argv is an array of the variables passed
//    argv[0] is proj5
//    argv[1] whatever is passed next (proj5_songs.txt in this case)
// To use it, just make sure that SongPlayer(string fileName) sets m_fileName
int main (int argc, char* argv[]) {
  string songFile; //Used to populate the m_fileName in SongPlayer
  cout << "Welcome to UMBC Song Player"<<endl;
  if(argc > 1){ //If there is at least one thing passed, set songFile to argv[1]
    songFile = argv[1];
  } else{
    cout << "One song files required - try again" << endl;
    cout << "./proj5 proj5_songs.txt" << endl;
    return 0;
  }
  SongPlayer* mySong = new SongPlayer(songFile); //Creates a new SongPlayer
  mySong->StartPlayer(); //Calls StartPlayer
  delete mySong; // Deallocates SongPlayer
  return 0;
}
