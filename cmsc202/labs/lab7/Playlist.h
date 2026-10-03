/**********************************************************************
 * File: Playlist.h
 * Project: CMSC202 Lab 7, Fall 2025
 * Author: [YOUR NAME HERE]
 * Date:
 * Email:
 * Creates a playlist (linked list) and adds songs(nodes)
 **********************************************************************/
#include <iostream>
#include <iostream>
using namespace std;

// List of known song names (You don't have to worry about this constant)
const string SONG_NAMES[] = {
  "The Girl from Ipanema", "Moon River", "Doralice",
  "One Note Samba", "Rush E", "Solitude", "Sunny Bossa", "Summertime",
  "Misty", "Wave", "Corcovado", "I Wish You Love",
  "Desafinado", "Berimbau", "Dreamer", "Agua de Beber",
  "Astigmatic", "Quasimodo", "Cry from the Hills", "Sambinha",
  "Bewitched"
};
const string UNKNOWN_SONG = "Unknown"; // Used for unknown song id

//Song struct is the node for the linked list
struct Song {
public:
  //Overloaded constructor for node
  Song(int id = 0, Song* next = nullptr) {
    m_id = id;
    m_next = next;
  }
  int m_id; //member variable for node
  Song* m_next; //pointer to next node in linked list
};

//Playlist class is the linked list
class Playlist {
public:
  // Name: Playlist (PROVIDED)
  // Desc: Default constructor (sets m_head to nullptr and m_size to 0;
  Playlist();
  // Name: ~Playlist (destructor) (PROVIDED)
  // Desc: Iterates through nodes and deletes all nodes.
  //       Resets size and m_head
  ~Playlist();
  // Name: AddSong(int)
  // Desc: Inserts new node to front of linked list
  void AddSong(int);
  // Name: RemoveSong
  // PROVIDED
  // Desc: Removes node from front of linked list
  void RemoveSong();
  // Name: CascadeRemove(int)
  // Desc: Removes all nodes after specific location
  //       If a linked list has 5 nodes, and CascadeRemove(3)
  //       is called, nodes 4 and 5 are removed
  void CascadeRemove(int);
  // Name: DisplayID (PROVIDED)
  // Desc: Iterates over linked list and displays the song id for each node
  void DisplayID();
  // Name: Display (PROVIDED)
  // Desc: Iterates over linked list and displays the song name
  //       associated with each node
  void Display();
  // Name: GetSong (PROVIDED)
  // Desc: Converts a given int representing song ID, into
  //       the song name associated with that ID
  string GetSong(int);
private:
  int m_size; //Number of songs in playlist
  Song* m_head; //Head (ie: the beginning) of playlist
};
