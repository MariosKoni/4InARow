#pragma once

#include "../Player/Player.hh"
#include "../Data/getData.hh"
#include "../NPC/NPC.hh"

#include <string>
#include <list>
#include <utility>
#include <vector>
#include <memory>
#include <filesystem>

class Game {
private:
  std::filesystem::path p = std::filesystem::current_path();
  std::string path;
  int maxRounds;
  int currentRound;
  int choice;
  int i;
  bool canPlay = true;

  std::vector<std::shared_ptr<Player>> pls;
  std::shared_ptr<getData> map;

  std::vector<std::pair<int, int>> spaces;

public:
  Game(bool); //Constructor of the main class. Takes a bool that determines if it's a new or an old game

  bool play(); //main game method
  bool updateGame(); //method to erase vector and current round as well as check if the game has ended (round wise)
  void checkAvailable(); //method that checks the available spots for the balls to be
  bool checkIfPlayerWon(char); //Check if a player has won
  void resetGame(); //Calls map.reset() and increments the round
  void checkWinner(); //Checks who has won the game
  void save(); //Saves data of current game to file
  bool load(); //Loads a snapshot of the game and continues from there
  bool getCanPlay(); //Returns the value of the attribute
  void remindPlayer(); //Reminds player/players of the info they gave to the system
  int getChoice(); //Returns the value of the choice
};
