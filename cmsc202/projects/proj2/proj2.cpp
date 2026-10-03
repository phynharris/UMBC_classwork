#include "Game.h"
#include "Squad.h"
#include "Unit.h"
#include <iostream>
using namespace std;

int main() {
  Game game;
  game.LoadSquadNamesFromFile("squad_names.txt");
  game.Setup();
  game.Run();
  return 0;
}
