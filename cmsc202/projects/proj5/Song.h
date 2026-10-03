//Title: Song.h
//Author: Jeremy Dixon
//Date: 11/10/2025
//Description: Describes the class named Song

#include <iostream>
#include <string>
using namespace std;

#ifndef SONG_H //Header guards
#define SONG_H //Header guards

class Song{
 public:
  //Name: Song - Default Constructor
  //Precondition: None
  //Postcondition: Creates a default song
  Song();
  //Name: Song - Overloaded Constructor
  //Precondition: Requires title, album, artist, Spotify streams
  //              YouTube views, and TikTok views
  //Postcondition: Creates a song entry based on passed parameters
  Song(string title, string album, string artist, long spotify, 
       long youtube, long tiktok);
  //Name: Mutators and Accessors
  //Precondition: None
  //Postcondition: Sets and Gets private member variables
  string GetTitle()const; // return title
  string GetAlbum()const; // return album
  string GetArtist()const; //return artist
  long GetSpotify() const; // returns Spotify streams
  long GetYouTube() const; // returns YouTube views
  long GetTikTok() const; // returns TikTok views
  void SetTitle(string title); //sets title
  void SetAlbum(string album); //sets album
  void SetArtist(string artist); //sets artist
  void SetSpotify(long spotify); //sets spotify streams
  void SetYouTube(long youTube); //sets youtube views
  void SetTikTok(long tikTok); //sets tiktok views
  //Name: Overloaded << operator
  //Precondition: song available
  //Postcondition: Returns output stream including title and artist
  friend ostream& operator<<(ostream& out, Song& m);
  //Name: Overloaded Relational Operator (<)
  //Precondition: Two song objects required
  //Postcondition: if passed song's spotify streams is less than first
  //               return true else false
  bool operator<(const Song& m);
private:
  string m_title; //Title of song
  string m_album; //Album of song
  string m_artist; //Artist of song
  long int m_spotify; //Number of Spotify streams
  long int m_youtube; //Number of YouTube views
  long int m_tiktok; //Number of TikTok views
};

#endif
