/**********************************************************************
 * File: lab7.cpp
 * Project: CMSC202 Lab 7, Fall 2025
 * Author: [YOUR NAME HERE]
 * Date:
 * Email:
 * Creates a playlist (linked list) and adds songs(nodes)
 **********************************************************************/
#include <iostream>
#include "Playlist.h"

int main() {
  Playlist playlist; //Creates a new linked list
  playlist.AddSong(5); //Adds a new node to linked list (song #5)
  playlist.AddSong(6); //Adds a new node to linked list (song #6)
  playlist.AddSong(7); //Adds a new node to linked list (song #7)
  playlist.AddSong(8); //Adds a new node to linked list (song #8)
  playlist.AddSong(9); //Adds a new node to linked list (song #9)
  playlist.DisplayID(); //Displays the ids of nodes (9->8->7->6->5->END)
  playlist.CascadeRemove(3); //Removes 3rd and 4th nodes in list (start 0)
  playlist.DisplayID(); //Displays the id of all nodes (9->8->7->END)
  playlist.Display(); //Displays all nodes (Wave->Misty->Summertime->END)

  playlist.RemoveSong(); //Removes the first node in linked list
  playlist.DisplayID(); //Displays all nodes (Misty->Summertime->END)
  playlist.Display(); //Displays all ids in linked list (40->30->END)
  
  return 0;
}
