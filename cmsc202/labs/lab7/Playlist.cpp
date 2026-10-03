#include "Playlist.h"

//Playlist default constructor
//PROVIDED

Playlist::Playlist() {
  m_size = 0;
  m_head = nullptr;
}

//Playlist destructor
//PROVIDED

Playlist::~Playlist() {
  Song* temp;
  while (m_head) {
    temp = m_head;
    m_head = m_head->m_next;
    delete temp;
  }
  m_head = nullptr;
  m_size = 0;
}

//Write Playlist AddSong function here (insert front):
//Write this function first
// (and test by commenting out other functions in lab7.cpp)
void Playlist::AddSong(int id){
  Song *temp = new Song();
  temp->m_id = id;
  temp->m_next = m_head;
  m_head = temp;
  m_size++;
  

}




//Write Playlist RemoveSong (Removes the song in the front of the playlist)
//Write this function second
// (and test by commenting out other functions in lab7.cpp)
//Make sure to test for memory leaks (don't forget to use delete)
void Playlist::RemoveSong(){
  Song *curr = m_head;
  if (m_size == 0){
    cout << "The playlist is empty." << endl;
    return;
  }else{
    m_head = m_head->m_next;
    delete curr;
    curr = nullptr;
  }
}




//Write Playlist CascadeRemove here
// (removes all songs after the passed index)
//Write this function third (and test - check for memory leaks)
//Challenging function!
void Playlist::CascadeRemove(int index){
  Song *curr = m_head;
  Song *prev = curr;
  if (m_size == 0){
    cout << "The playlist is empty" << endl;
    return;
  }else{
      while(curr != nullptr){
	if(curr->m_id >= index){
	  curr = curr->m_next;
	  prev->m_next = nullptr;
	}else{
	  prev = curr;
	  curr = curr->m_next;
      }
    }
  }
}



//Playlist DisplayID function
//PROVIDED

void Playlist::DisplayID() {
  Song* cur = m_head;
  while (cur) {
    cout << cur->m_id << "->";
    cur = cur->m_next;
  }
  cout << "END" << endl;
}

//Playlist Display function
//PROVIDED

void Playlist::Display() {
  Song* cur = m_head;
  while (cur) {
    cout << GetSong(cur->m_id) << "->";
    cur = cur->m_next;
  }
  cout << "END" << endl;
}


// GetSong function
// PROVIDED

string Playlist::GetSong(int id) {
  // This helper function converts a song id into a song name 
  if (id >= 0 and id < int(sizeof(SONG_NAMES))){
    return SONG_NAMES[id];
  } else {
    return UNKNOWN_SONG;
  }
}

