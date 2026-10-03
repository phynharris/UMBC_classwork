/*****************************************
 ** File: Game.cpp
 ** Project: CMSC 202 Project 2, Fall 2025
 ** Author: Jaylen Jenkins
 ** Date: 10/9/2025
 ** Section: 20/22
 ** E-mail: fp31977@gl.umbc.edu
 **
 ** This file contains the cpp file for the Game class.
 ** A random seed is generated, and that is used for the stats of this game's units.
 ** This is also responsible for loading squad names from a .txt file.
 ** The units stats are set up here, setting player and enemy names, as well as randomizing their health and damage.
 ** While both squads are alive, a battle cycle commences and the first unit from each squad will attack the next.
 ** Once the game has ended, the winner will be announced.
 **
 ***********************************************/
#include "Game.h"

const int MAX_PLAYERS = 2;
const int MAX_ENEMIES = 2;

const int MAX_HEALTH = 100;
const int MAX_ATTACK = 29;
const int MIN_HEALTH = 80;
const int MIN_ATTACK = 20;

//Game::Game
//Given nothing — Returns nothing
Game::Game(){
  // Sets random seed for stats
  srand(time(NULL));
}

//Game:LoadSquadNamesFromFile
//Given a filename — Returns nothing.
void Game::LoadSquadNamesFromFile(string filename){
  // Opens a file to get the squad names from it
  ifstream squadFile(filename);
  if(squadFile.is_open()){
    getline(squadFile, m_playerSquadName);
    getline(squadFile, m_enemySquadName);

    if(squadFile.peek() == '\n'){
      squadFile.ignore();
    }
  }
  squadFile.close();
}

//Game::Setup
//Given nothing — Returns nothing.
void Game::Setup(){
  // A unit's health, attack power, and name
  int health;
  int atk;
  string name;

  // Sets the names for each squad
  m_playerSquad.SetName(m_playerSquadName);
  m_enemySquad.SetName(m_enemySquadName);

  // Sets player units stats for unit's squad
  // Populates player's squad
  for(int i = 0; i < MAX_PLAYERS; i++){
    health = (rand() % (MAX_HEALTH + 1 - MIN_HEALTH)) + MIN_HEALTH;
    atk = (rand() % (MAX_ATTACK + 1 - MIN_ATTACK)) + MIN_ATTACK;

    cout << "Enter name of your unit No. " << i + 1 << ": ";
    getline(cin, name);
    Unit unit(name, health, atk);
    m_playerSquad.AddMember(unit);
  }

  // Sets enemy stats and populaes enemy squad
  for(int i = 0; i < MAX_PLAYERS; i++){
    health = (rand() % (MAX_HEALTH + 1 - MIN_HEALTH)) + MIN_HEALTH;
    atk = (rand() % (MAX_ATTACK + 1 - MIN_ATTACK)) + MIN_ATTACK;
    
    cout << "Enter name enemy unit No. " << i + 1 << ": ";
    getline(cin, name);
    Unit unit(name, health, atk);
    m_enemySquad.AddMember(unit);
  }
}

//Game:Run
//Given nothing — Returns nothing
void Game::Run(){
  int turnCounter = 1;
  bool gameRun = true;
  Unit* firstPlayer;
  Unit* firstEnemy;
  string playerName;
  string enemyName;

  // doWhile loop that repeats until a squad is defeated
  do{
    // Starts by displaying turn count and each squad's status every turn
    cout << "=== Turn " << turnCounter << " ===" << endl;
    m_playerSquad.PrintStatus();
    m_enemySquad.PrintStatus();

    // Gets the first alive unit in boths squads
    firstPlayer = m_playerSquad.GetFirstAliveMember();
    firstEnemy = m_enemySquad.GetFirstAliveMember();

    // Has the first alive player of each squad attack the other
    (*firstPlayer).Attack(*firstEnemy);
    (*firstEnemy).Attack(*firstPlayer);

    // Once one team is dead, announce the outcome
    // End the game
    cout << endl;
    if(m_playerSquad.IsDefeated() || m_enemySquad.IsDefeated()){
      cout << endl << "=== Battle Over ===" << endl;
      if(m_playerSquad.IsDefeated() && m_enemySquad.IsDefeated()){
	cout << "Both teams were defeated. Tie!" << endl;
      }else if(m_enemySquad.IsDefeated()){
	cout << m_playerSquadName << " wins!" << endl;
      }else{
	cout << m_enemySquadName << " wins!" << endl;
      }
      gameRun = false;
    }

    turnCounter += 1;
  }while(gameRun);
}
