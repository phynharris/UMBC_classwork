/*****************************************
 ** File: Song.cpp
 ** Project: CMSC 202 Project 5, Fall 2025
 ** Author: Jaylen Jenkins
 ** Date: 11/25/2025
 ** Section: 20/22
 ** E-mail: fp31977@gl.umbc.edu
 **
 ** This file contains the implementation for the Song class.
 ** Populates a song's title, album, artist, spotfy stream, youtube streams, and tiktok streams.
 ***********************************************/

#include "Song.h"

// Constants
string DEF_TITLE = "songTitle";
string DEF_ALBUM = "albumName";
string DEF_ARTIST = "artistName";
long int DEF_VIEWS = 1;

// Song::Song
// Given nothing — Returns nothing
Song::Song(){
  SetTitle(DEF_TITLE);
  SetAlbum(DEF_ALBUM);
  SetArtist(DEF_ARTIST);
  SetSpotify(DEF_VIEWS);
  SetYouTube(DEF_VIEWS);
  SetTikTok(DEF_VIEWS);
}

// Song::Song
// Given a song title, album name, artist name,
//     Spotfy stream amount, YouTube stream amount, and TikTok stream amount
// Returns nothing
Song::Song(string title, string album, string artist, long spotify,
	   long youtube, long tiktok){
  SetTitle(title);
  SetAlbum(album);
  SetArtist(artist);
  SetSpotify(spotify);
  SetYouTube(youtube);
  SetTikTok(tiktok);
}

// Song::GetTitle
// Given nothing — Returns song title
string Song::GetTitle()const{

  return m_title;
}

// Song::GetAlbum
// Given nothing — Returns album name
string Song::GetAlbum()const{

  return m_album;
}

// Song::GetArtist
// Given nothing — Returns artist name
string Song::GetArtist()const{
  
  return m_artist;
}

// Song::GetSpotify
// Given nothing — Returns spotify streams
long Song::GetSpotify() const{

  return m_spotify;
}

// Song::GetYouTube
// Given nothing — Returns youtube streams
long Song::GetYouTube() const{

  return m_youtube;
}

// Song::GetTikTok
// Given nothing — Returns TikTok streams
long Song::GetTikTok() const{

  return m_tiktok;
}

// Song::SetTitle
// Given a song title — Returns nothing
void Song::SetTitle(string title){
  m_title = title;
}

// Song::SetAlbum
// Given an album name — Returns nothing
void Song::SetAlbum(string album){
  m_album = album;
}

// Song::SetArtist
// Given an artist's name — Returns nothing
void Song::SetArtist(string artist){
  m_artist = artist;
}

// Song::SetSpotify
// Given spotfy streams — Returns nothing
void Song::SetSpotify(long spotify){
  m_spotify = spotify;
}

// Song::SetYouTube
// Given YouTube streams — Returns nothing
void Song::SetYouTube(long youTube){
  m_youtube = youTube;
}

// Song::SetTikTok
// Given tiktok streams — Returns nothing
void Song::SetTikTok(long tikTok){
  m_tiktok = tikTok;
}

// operator<<
// Given output stream and a Song reference — Returns output stream
ostream& operator<<(ostream& out, Song& m){
  out << m.m_title << " by " << m.m_artist;
  return out;
}

// Song::operator<
// Given a Song reference — Returns (t/f) comparison of spotify streams
bool Song::operator<(const Song& m){
  // Returns true if the passed song's spotify streams are less than this songs
  if(m.GetSpotify() < m_spotify){
    return true;
  }else{
    return false;
  }
}
