/*****************************************
 ** File: SongPlayer.cpp
 ** Project: CMSC 202 Project 5, Fall 2025
 ** Author: Jaylen Jenkins
 ** Date: 11/25/2025
 ** Section: 20/22
 ** E-mail: fp31977@gl.umbc.edu
 **
 ** This file contains the implementation for the Song Player class.
 ** Allows user to add songs from a catalog into their own playlist.
 ** Playlist can be sorted by spotify streams (high -> low)
 ***********************************************/
#include "SongPlayer.h"

// SongPlayer::SongPlayer
// Given nothing — Returns nothing
SongPlayer::SongPlayer(){
  m_filename = FILE_NAME;
}

// SongPlayer::SongPlayer
// Given a filename — Returns nothing
SongPlayer::SongPlayer(string filename){
  m_filename = filename;
}

// SongPlayer::~SongPlayer
// Given nothing — Returns nothing
SongPlayer::~SongPlayer(){
  // Deletes each dynamically allocated song
  for(int i = 0; i < int(m_songCatalog.size()); i++){
    delete m_songCatalog[i];
  }
}

// SongPlayer::ToLower
// Given the string to be lowered — Returns the lowered string
string SongPlayer::ToLower(string word){
  char cWord[word.length()]; // Creates a character array that is the length of the given word
  string lowString= "";      // The lowercase string

  // Iterates through each letter in word and makes it lower
  for(int i = 0; i < int(word.length()); i++){
    cWord[i] = tolower(word[i]);
    lowString += cWord[i];
  }

  return lowString;
}

// SongPlayer::LoadCatalog
// Given nothing — Returns nothing
void SongPlayer::LoadCatalog(){
  string title;        // Song's title
  string album;        // Song's album
  string artist;       // Song's artist
  string spotifyStr;   // Song's spotify streams as string
  string youtubeStr;   // Song's youtube streams as string
  string tiktokStr;    // Song's tiktok streams as string
  int spotify;         // Song's spotify streams
  int youtube;         // Song's youtube streams
  int tiktok;          // Song's tiktok streams
  int counter;         // Counts No. of songs

  if(m_filename == ""){
    return;
  }else{
    fstream catalogue(m_filename);

    // Obtains song info from file
    while(getline(catalogue, title, '|')
	  && getline(catalogue, album, '|')
	  && getline(catalogue, artist, '|')
	  && getline(catalogue, spotifyStr, '|')
	  && getline(catalogue, youtubeStr, '|')
	  && catalogue >> tiktokStr){
      spotify = stol(spotifyStr);
      youtube = stol(youtubeStr);
      tiktok = stol(tiktokStr);

      // Creates new song and adds it to catalog
      Song* song = new Song(title, album, artist, spotify, youtube, tiktok);
      m_songCatalog.push_back(song);
    
      // Ignores unnecessary new lines from the file extraction
      if(catalogue.peek() == '\n'){
	catalogue.ignore();
  }
    counter++;
  }
  catalogue.close();
  }
  cout << counter << "songs loaded." << endl;
}

// SongPlayer::MainMenu
// Given nothing — Returns nothing
void SongPlayer::MainMenu(){
  cout << "What would you like to do?" << endl
       << "1. Display Song by Title, Artist, and Album" << endl
       << "2. Add Song to Playlist" << endl
       << "3. Display Playlist" << endl
       << "4. Sort Playlist by Spotify Streams" << endl
       << "5. Quit" << endl;
}

// SongPlayer::DisplaySong
// Given nothing — Returns No. of songs that meet criteria
int SongPlayer::DisplaySong(){
  int counter = 1;      // Counter to screen
  int matchCounter = 0; // No. of matches
  int choice;           // 1 (Artist) or 2 (Song)
  string type;          // String from choice
  string searchString;  // The string the user wants to find
  string query;         // Superstring compared against searchString

  // Returns if catalog is empty
  if(m_songCatalog.size() == 0){
    cout << "Catalogue is empty." << endl;
    return 0;
  }

  // Prompts the user to search by artist or song
  choice = SearchOptions();
  if(choice == 1){
    type = "artist";
  }else{
    type = "song";
  }
  searchString = ToLower(SearchType(type));

  // Iterates through song catalog and displays songs that meet criteria
  for (vector<Song*>::iterator it = m_songCatalog.begin();
       it != m_songCatalog.end(); it++){
    if(type == "artist"){
      query = (*it)->GetArtist();
    }else{
      query = (*it)->GetTitle();
    }
    query = ToLower(query);
    if(query.find(searchString) != string::npos){
      cout << counter << ". " << *(*it) << endl;
      matchCounter++;
    }
    counter++;
  }
  return matchCounter;
}

// SongPlayer::SearchType
// Given nothing — Returns 1 (for artist) or 2 (for song)
int SongPlayer::SearchOptions(){
  int choice = 0;

  // Prompts the user for their choice
  do{
    cout << "1. Search for artist" << endl
	 << "2. Search for song" << endl;

    cin >> choice;
  }while(choice != 1 && choice != 2);

  return choice;
}

// SongPlayer::SearchType
// Given what the user whishes to search for (artist or song) — Returns desired search term
string SongPlayer::SearchType(string type){
  string search = "";

  // Prompts the user for their choice
  while(search == ""){
    cout << "Which " << type << " would you like to display?" << endl;
    cin >> search;
  }
  
  return search;
}

// SongPlayer::AddSong
// Given nothing — Returns nothing
void SongPlayer::AddSong(){
  int choice;    // The index of the desired song
  int num_songs; // The number of songs that meet criteria

  // Displays songs that meet criteria
  num_songs = DisplaySong();
  cout << num_songs << " songs found." << endl;

  // Prompts user to enter a song and adds it to the playlist if it exists
  cout << "Enter the index of the song you would like to add." << endl;
  cin >> choice;
  --choice;
  if(choice < 0 || choice > int(m_songCatalog.size())){
    cout << "Song not found." << endl;
  }else{
    m_playList.PushBack(m_songCatalog.at(choice));
  }
  
}

// SongPlayer::DisplayPlaylist
// Given nothing — Returns nothing
void SongPlayer::DisplayPlaylist(){
  m_playList.Display();
}

// SongPlayer::SortPlaylist
// Given nothing — Returns nothing
void SongPlayer::SortPlaylist(){
  m_playList.Sort();
}

// SongPlayer::StartPlayer
// Given nothing — Returns nothing
void SongPlayer::StartPlayer(){
  int choice = 0;
  
  LoadCatalog();

  // Prompts the user for their choice
  while(choice != 5){
    MainMenu();
    cin >> choice;

    switch(choice){
    case 1:
      DisplaySong();
      break;
    case 2:
      AddSong();
      break;
    case 3:
      DisplayPlaylist();
      break;
    case 4:
      SortPlaylist();
      break;
    case 5:
      cout << "Auf Wiedersehen" << endl;
      break;
    default:
      cout << "Invalid choice" << endl;
      break;
    } 
  }
}
