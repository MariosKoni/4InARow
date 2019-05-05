#include "Game.h"
#include "../Player/Player.h"
#include "../Data/getData.h"

#include <iostream>
#include <map>
#include <utility>
#include <vector>

Game::Game() {
  currentRound = 1;

  std::cout << "Welcome to " << gameTitle << "!" << std::endl;
  std::cout << "Select number of players\n1. One vs AI\n2. Two\nChoice: ";
  std::cin >> choice;
  for (int i = 0; i < choice; ++i) {
    std::unique_ptr<Player> pl(new Player());
    pls.push_back(pl);
  }
  std::cout << "Insert the number of rounds that will be played: ";
  std::cin >> maxRounds;
  map = std::unique_ptr<getData>(new getData());
}

bool Game::updateGame() {
  currentRound++;
  spaces.clear();

  if (currentRound > maxRounds)
    return false;

  return true;
}

void Game::checkAvailable() {
  for (int i = 0; i < map->getRows(); ++i) {
    for (int j = 0; j < map->getCols(); ++j) {
      if (!map->checkStage(i, j, ' ')) {
        std::pair<int ,int>spot(i, j - 1);
        spaces.push_back(spot);
      }
    }
  }
}

bool Game::checkIfPlayerWon(char ch) {
  int counter = 0;

  for (int i = 0; i < map->getRows(); ++i) {
    for (int j = 0; j < map->getCols(); ++j) {
      if (map->checkStage(i, j, ch)) {
        int x = 0;
        int y = 0;

        while (map->checkStage(x -1, y, ch)) {
          i--;
          counter++;
        }
        if (counter == 4)
          return true;

        counter = 0;
        while (map->checkStage(x + 1, y, ch)) {
          i++;
          counter++;
        }
        if (counter == 4)
          return true;

        counter = 0;
        while (map->checkStage(x, y + 1, ch)) {
          y++;
          counter++;
        }
        if (counter == 4)
          return true;

        counter = 0;
        while (map->checkStage(x, y - 1, ch)) {
          y--;
          counter++;
        }
        if (counter == 4)
          return true;
      }
    }
  }

  return false;
}

bool Game::play(unsigned int i) {
  int pls1 = 0;
  int pls2 = 0;

  int turn;

  if (i % 2 == 0) {
    std::cout << "It's " << pls[0]->getName() << " turn to play" << std::endl;
    turn = 0;
  }
  else {
    std::cout << "It's " << pls[1]->getName() << " turn to play" << std::endl;
    turn = 1;
  }

  checkAvailable();

  int x, y;
  std::cout << "Available spots are:" << std::endl;
  for(auto const& value : spaces)
    std::cout << "[" << value.first << "]" << " [" << value.second << "]" << " ";
  std::cout << std::endl;
  std::cout << "Type the numbers (that corresponds to a place in the map) to place the ball: ";
  std::cin >> x >> y;

  map->setToStage(x, y - 1, pls[turn]->getColor());

  if (checkIfPlayerWon(pls[turn]->getColor())) {
    pls[turn]->addScore();
    if (!updateGame()) {
      std::cout << "The game is over!\n" << pls[turn]->getName() << " has won!" << std::endl;
      std::cout << "Score: " << pls[0]->getScore() << " : " << pls[1]->getScore() << std::endl;

      return false;
    }
  }
  system("clear");

  return true;
}
