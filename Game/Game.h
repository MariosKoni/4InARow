#pragma once

#include "../Player/Player.h"
#include "../Data/Data.h"

#include <string>
#include <list>

class Game {
private:
  const std::string gameTitle = "4 in a row";
  int maxRounds;
  int currentRound;
  int choice;

  Player *pls;
  Data *map;

  struct mapStats {
    unsigned int numOfSpaces;
    list <unsigned int> spaces;
  } ms;

public:
  Game(Player *p, Data *m);

  bool play(unsigned int i); //main game method
  bool updateGame(int pl1, int pl2); //method to update the score and current round as well as check if the game has ended
  void checkAvailable(); //method that checks the available spots for the balls to be
  void findNearestnPlace(int b, char ch); //method that finds the nearst spot in column for the ball to be placed, and places it
  bool checkIfPlayerWon(char ch); //Check if a player has won
};
