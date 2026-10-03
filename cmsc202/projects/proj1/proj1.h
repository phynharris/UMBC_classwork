/*****************************************
 - File: proj1.cpp
 - Project: CMSC 202 Project 1, Fall 2025
 - Author: Jaylen Jenkins
 - Date: 9/19/25
 - Section: 20/22
 - E-mail: FP31977@gl.umbc.edu

 ********** PROJECT DESCRIPTION **********
 This file contains the header program for project 1 and does the following:
 - Asks the  user to enter the name of a .txt file
 - Converts each name/vote in the file to lowercase and sums them.
 - Converts candidate names to title case and displays vote results as a number and histogram.
****************************************/


/*****************************************
 - Name:loadVotes
 - Pre-Condition: None
 - Post-Condition: Inputs all votes into a list; returns nothing
*****************************************/
void loadVotes(string votes[]);

/*****************************************
 - Name: toLower
 - Pre-Condition: None
 - Post-Condition: Returns a lowercase version of a vote
*****************************************/
string toLower(string vote);

/*****************************************
 - Name: findCandidateIndex
 - Pre-Condition: The first vote is always added to the candidates list
 - Post-Condition: Returns either the number of candidates or the number of candidates +1
*****************************************/
int findCandidateIndex(string votes[], string candidates[], int candidate_amount, int voteCount[], int index);

/*****************************************
 - Name: toTitle
 - Pre-Condition: None
 - Post-Condition: Returns a candidate name in titlecase form (e.g. jaylen jenkins --> Jaylen Jenkins)
*****************************************/
string toTitle(string candidate);

/*****************************************
 - Name: printVoteCounts
 - Pre-Condition: None
 - Post-Condition: Prints the number of votes each candidate has recieved
*****************************************/
void printVoteCounts(string candidates[], int numOfCandidates, int votes[]);

/*****************************************
 - Name: printHistogram
 - Pre-Condition: None
 - Post-Condition: Prints the number of votes each candidate has recieved via asteriks
*****************************************/
void printHistogram(string candidates[], int numOfCandidates, int votes[]);
