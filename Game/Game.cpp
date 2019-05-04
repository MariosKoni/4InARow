#include "Game.h"
#include "../Player/Player.h"
#include "../Data/Data.h"

#include <iostream>
#include <map>
#include <utility>
#include <vector>

Game::Game(Player *p, Data *m) {
  pls = &p;
  map = &m;
  currentRound = 1;

  std::cout << "Welcome to " << gameTitle << "!" << std::endl;
  std::cout << "Select number of players\n1. One vs AI\n2. Two\nChoice: ";
  std::cin >> choice;
  std::cout << "Insert the number of rounds that will be played: ";
  std::cin >> maxRounds;
}

bool Game::updateGame(int pl1, int pl2) {
  currentRound++;
  *pls->setScore(pl1);
  *(pls + 1)->setScore(pl2);
  spaces.clear();

  if (currentRound > maxRounds)
    return false;

  return true;
}

void Game::checkAvailable() {
  for (int i = 0; i < *map->getRows(); ++i) {
    for (int j = 0; j < *map->getCols(); ++j) {
      if (!*map->checkStage(i, j, ' ')) {
        spot = make_pair(i, j - 1);
        spaces.push_back(spot);
      }
    }
  }
}

bool Game::checkIfPlayerWon(char ch) {
  int counter = 0;

  for (int i = 0; i < *map->getRows(); ++i) {
    for (int j = 0; j < *map->getCols(); ++j) {
      if (*map->checkStage(i, j, ch)) {
        int x = 0;
        int y = 0;

        while (*map->checkStage(x -1, y, ch)) {
          i--;
          counter++;
        }
        if (counter == 4)
          return true;

          int x = 0;
          int y = 0;
          while (*map->checkStage(x + 1, y, ch)) {
            i++;
            counter++;
          }
          if (counter == 4)
            return true;

          int x = 0;
          int y = 0;
          while (*map->checkStage(x, y + 1, ch)) {
            y++;
            counter++;
          }
          if (counter == 4)
            return true;

          int x = 0;
          int y = 0;
          while (*map->checkStage(x, y - 1, ch)) {
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

  if (i % 2 == 0)
    std::cout << "It's " << *pls->getName() << " to play" << std::endl;
  else
    std::cout << "It's " << *(pls + 1)->getName() << " to play" << std::endl;

  checkAvailable();

  int x, y;
  std::cout << "Available spots are:" << std::endl;
  for(auto const& value : spaces)
    std::cout << "[" << value.first << "]" << " [" << value.second << "]" << " ";
  std::endl;
  std::cout << "Type the numbers (that corresponds to a place in the map) to place the ball: ";
  std::cin >> x >> y;

  *map->setStage(i, j - 1, *(pls + i).getColor());
  if (checkIfPlayerWon(*(pls + i).getColor()) || !updateGame()) {
    std::cout << "The game is over!\n" << *(pls + i)->getName() << " has won!" << std::endl;
    std::cout << "Score: " << *pls->getScore() << " : " << *(pls + 1)->getScore() << std::endl;

    return false;
  }
  system("clear");

  return true;
}
