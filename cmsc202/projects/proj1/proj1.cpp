/*****************************************
 - File: proj1.cpp
 - Project: CMSC 202 Project 1, Fall 2025
 - Author: Jaylen Jenkins
 - Date: 9/19/25
 - Section: 20/22
 - E-mail: FP31977@gl.umbc.edu

 ********** PROJECT DESCRIPTION **********
 This file contains the driver program for project 1 and does the following:
 - Asks the  user to enter the name of a .txt file
 - Converts each name/vote in the file to lowercase and sums them.
 - Converts candidate names to title case and displays vote results as a number and histogram.
 ****************************************/


#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;


// loadVotes
// Given an empty array of votes
// Returns nothing
void loadVotes(string votes[]);

// toLower
// Given a vote
// Returns a lowercase version of the vote
string toLower(string vote);

// findCandidateIndex
// Given an array of votes, an array of candidates, the current number of candidates,
//   an array of vote counts, and the current index
// Returns either the current candidate amount or the candidate amount plus 1
int findCandidateIndex(string votes[], string candidates[], int candidate_amount, int voteCount[], int index);

// toTitle
// Given a candidate
// Returns a titlecase version of the candidate
string toTitle(string candidate);

// printVoteCounts
// Given the array of candidates, the number of candidates, and an array of vote counts.
// Returns nothing
void printVoteCounts(string candidates[], int numOfCandidates, int votes[]);

// printHistogram
// Given the array of candidates, the number of candidates, and an array of vote counts.
// Returns nothing
void printHistogram(string candidates[], int numOfCandidates, int votes[]);


const int VOTE_FILE_SIZE = 256;                 // size for the votes array
const int CANDIDATE_INDEX_SIZE = 20;            // size for the candidates array and voteCount array

int main(){
  string votes[VOTE_FILE_SIZE];                 // array for the votes from the vote#.txt files
  string candidates[CANDIDATE_INDEX_SIZE];      // array for containing each unqiue candidate
  int voteCount[CANDIDATE_INDEX_SIZE] = {0};    // array for the number of votes each candidate has
  int candidate_amount = 0;                     // the number of candidates

  // Loads the votes from a vote#.txt filees
  loadVotes(votes);

  for(int i = 0; i < VOTE_FILE_SIZE; i++){
    // Converts each vote to lowercase
    votes[i] = toLower(votes[i]);

    // Tallies up the current vote and increases the num of candidates if they are unique
    candidate_amount = findCandidateIndex(votes, candidates, candidate_amount, voteCount, i);
  }

  // Converts candidate names to TitleCase
  for(int i = 0; i < CANDIDATE_INDEX_SIZE; i++){
    candidates[i] = toTitle(candidates[i]);
  }

  // Prints the results
  cout << "\n" << "Vote Counts: " << endl;
  printVoteCounts(candidates, candidate_amount, voteCount);
  cout << "\n" << "Histogram: " << endl;
  printHistogram(candidates, candidate_amount, voteCount);
  
  return 0;
}

// loadVotes
// Given an empty array of votes
// Returns nothing
void loadVotes(string votes[]){
  string fileName;        // The name of the file to be read from
  bool badInput = false;    // Checks if the user failed the input

  //Prompts the user to enter a file to read from.
  do{
    if(badInput){
      cout << "Please enter an appropriate file name: " << endl;
    }
    
    cout << "Enter the name of the file you wish to open: " << endl;
    cin >> fileName;
    
    badInput = true;
  }while(fileName != "votes1.txt" and fileName != "votes2.txt" and fileName != "votes3.txt");

  // Opens the entered file and appends each vote to the votes array
  fstream voteFile(fileName);
  if(voteFile.is_open()){

    for(int i = 0; i < VOTE_FILE_SIZE; i++){
      getline(voteFile, votes[i]);
    }
  }
  voteFile.close();
}

// toLower
// Given a vote
// Returns a lowercase version of the vote
string toLower(string vote){
  int length = vote.length(); // Gets the length of the vote and casts it to an int

  // Converts each char in a vote to lowercase
  for(int j = 0; j < length; j++){
    vote[j] = tolower(vote[j]);
  }
  
  return vote;
}

// findCandidateIndex
// Given an array of votes, an array of candidates, the current number of candidates,
//   an array of vote counts, and the current index
// Returns either the current candidate amount or the candidate amount plus 1
int findCandidateIndex(string votes[], string candidates[], int candidate_amount, int voteCount[],  int index){
  // Base Case: If the index is 0:
  if(candidate_amount == 0){
    // Candidate is added to candidates array and given a vote
    candidates[candidate_amount] = votes[index];
    ++voteCount[candidate_amount];

    return ++candidate_amount;
  }

  // If a candidate already exists, then only their vote count is incremented
  for(int j = 0; j < CANDIDATE_INDEX_SIZE; j++){
    if(votes[index] == candidates[j]){
      ++voteCount[j];
      return candidate_amount;

    }
  }

  // Appends current candidate to candidates list and increments their vote count
  candidates[candidate_amount] = votes[index];
  ++voteCount[candidate_amount];
  
  return ++candidate_amount;
}

// toTitle
// Given a candidate
// Returns a titlecase version of the candidate
string toTitle(string candidate){
  int length = candidate.length(); // Gets the length of the candidate and casts it to an int
  bool capitalize = true;          // Decides if the current letter should be capitalized

  // Goes though each letter of a candidate's name and decides if it should be capitalized
  for(int j = 0; j < length; j++){

    // Capitalizes a letter; always applies to the first letter of a string
    if(capitalize){
      candidate[j] = toupper(candidate[j]);
      capitalize = false;
      }

    // If the current character is either a space or a hyphen, the following character will be capitalized
    if(candidate[j] == ' ' or candidate[j] == '-'){
      capitalize = true;
    }
  }

  return candidate;
}

// printVoteCounts
// Given the array of candidates, the number of candidates, and an array of vote counts.
// Returns nothing
void printVoteCounts(string candidates[], int numOfCandidates, int votes[]){
  for(int i = 0; i < numOfCandidates; i++){
    cout << "\t" << candidates[i] << ": " << votes[i] << " votes" << endl;
  }
  
  return;
}

// printVoteCounts
// Given the array of candidates, the number of candidates, and an array of vote counts.
// Returns nothing
void printHistogram(string candidates[], int numOfCandidates, int votes[]){
  for(int i = 0; i < numOfCandidates; i++){
    string histogramVotes = ""; // Will have *'s concatenated to them to represent votes
    
    for(int j = 0; j < votes[i]; j++){
      histogramVotes += "*";
    }
    cout << "\t" << candidates[i] << ": " << histogramVotes << endl;
  }

  return;
}
