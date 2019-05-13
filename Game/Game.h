#pragma once

#include "../Player/Player.h"
#include "../Data/getData.h"

#include <string>
#include <list>
#include <utility>
#include <vector>
#include <memory>

class Game {
private:
  const std::string gameTitle = "4 in a row";
  int maxRounds;
  int currentRound;
  int choice;

  std::vector<std::shared_ptr<Player>> pls;
  std::unique_ptr<getData> map;

  std::vector<std::pair<int, int>> spaces;

public:
  Game();

  bool play(unsigned int i); //main game method
  bool updateGame(); //method to erase vector and current round as well as check if the game has ended
  void checkAvailable(); //method that checks the available spots for the balls to be
  bool checkIfPlayerWon(char ch); //Check if a player has won
  void resetGame(); //Calls map.reset() and increments the round
};
