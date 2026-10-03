//Title: SongPlayer.h
//Author: Jeremy Dixon
//Date: 11/10/2025
//Description: Describes the class named SongPlayer

#ifndef SONG_PLAYER_H //Header guards
#define SONG_PLAYER_H //Header guards

#include <iostream>
#include <vector>
#include <string>
#include <fstream> //For files
#include <cctype> //For tolower or toupper
#include "Song.h"
#include "Queue.cpp"

using namespace std;

//**********Project 5 Constants**************
const string FILE_NAME = "proj5_songs.txt"; //Used in default SongPlayer constructor

class SongPlayer{
 public:
  //Name: SongPlayer - Default Constructor
  //Precondition: None
  //Postcondition: Creates a new SongPlayer with m_filename of FILE_NAME
  SongPlayer();
  //Name: SongPlayer - Overloaded Constructor
  //Precondition: None
  //Postcondition: Creates a new SongPlayer with passed filename
  SongPlayer(string filename);
  //Name: ~SongPlayer - Destructor
  //Precondition: None
  //Postcondition: Deallocates songs from m_songCatalog
  ~SongPlayer();
  //Name: ToLower()
  //Precondition: Requires a string to be passed
  //Postcondition: Makes word lowercase (used for finding an artist or title)
  string ToLower(string word);
  //Name: LoadCatalog()
  //Precondition: Requires m_filename to be populated
  //Postcondition: Dynamically allocates each song and inserts into m_songCatalog
  //Hint:          Allowed to use stoi (string to integer) if needed
  //Hint:          Allowed to use stoll or stoul (string to long) if needed
  void LoadCatalog();
  //Name: MainMenu
  //Precondition: None
  //Postcondition: Manages the menu
  void MainMenu();
  //Name: DisplaySong
  //Desc: Asks user to search by artist or title (1 for Artist and 2 for Title)
  //      Asks user for search string (converts to lower case)
  //      If 1 chosen, displays all artists with the search string (or all titles if 2)
  //      Uses iterators
  //Precondition: m_songCatalog is populated
  //Postcondition: Returns count of songs meeting search criteria else 0
  //Hint: Allowed to use ** if necessary
  int DisplaySong();
  //Name: SearchType
  //Desc: Helper function for DisplaySong
  //      Asks the user if they want search by artist or title
  //Precondition: m_songCatalog is populated
  //Postcondition: Returns 1 for artist and 2 for title
  int SearchOptions();
  //Name: SearchType
  //Desc: Prompts the user for what string they want to search for (can be artist or title)
  //Precondition: m_songCatalog is populated
  //Postcondition: Returns string to search for
  string SearchType(string type);
  //Name: AddSong
  //Desc: Calls DisplaySong where user chooses artist or title and search string
  //      User enters index of song to choose
  //      Validates for number to be between 0 - m_songCatalog size
  //      Does NOT validate that song chosen was from results of search
  //      Uses overloaded << operator to display the example below
  //Example: Someone You Loved by Lewis Capaldi from Breach added to the playlist.
  //Precondition: m_songCatalog is populated
  //Postcondition: Adds pointer from m_songCatalog and inserts into m_playList
  void AddSong();
  //Name: DisplayPlaylist
  //Precondition: None (will indicate if list is empty)
  //Postcondition: Displays the playlist using the overloaded << operator
  void DisplayPlaylist();
  //Name: SortPlaylist
  //Precondition: None (will indicate if list is empty)
  //Postcondition: Sorts the playlist by Spotify streams
  void SortPlaylist();
  //Name: StartPlayer
  //Precondition: None (file name has already been provided)
  //Postcondition: Loads file and calls main menu
  void StartPlayer();
private:
  string m_filename; //Name of input file
  vector<Song*> m_songCatalog; //Holds all songs in file
  Queue<Song*> m_playList; //Holds all songs in play list
};


#endif
