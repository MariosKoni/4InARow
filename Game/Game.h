#pragma once

#include "../Player/Player.h"
#include "../Data/getData.h"
#include "../NPC/NPC.h"

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
  std::shared_ptr<getData> map;

  std::vector<std::pair<int, int>> spaces;

public:
  Game();

  bool play(unsigned int); //main game method
  bool updateGame(); //method to erase vector and current round as well as check if the game has ended (round wise)
  void checkAvailable(); //method that checks the available spots for the balls to be
  bool checkIfPlayerWon(char); //Check if a player has won
  void resetGame(); //Calls map.reset() and increments the round
};
