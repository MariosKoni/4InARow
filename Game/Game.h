#pragma once

#include "../Player/Player.h"
#include "../Data/Data.h"

#include <string>

class Game {
private:
  const std::string gameTitle = "4 in a row";
  int maxRounds;
  int currentRound;
  int choice;

  Player *pls;
  Data *map;

  struct mapStats {
    unsigned int s;
    unsigned int sp[41];
  } ms;

public:
  Game(Player *p, Data *m);

  bool play(unsigned int i); //main game method
  bool updateGame(int pl1, int pl2, int b, char ch); //method to update the score and current round as well as check if the game has ended
  void checkAvailable(); //method that checks the available spots for the balls to be
};
