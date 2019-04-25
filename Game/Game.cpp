#include "Game.h"
#include "../Player/Player.h"
#include "../Data/Data.h"

#include <iostream>
#include <list>
#include <iterator>
#include <map>

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

  if (currentRound > maxRounds)
    return false;

  return true;
}

void Game::checkAvailable() {
  for (int i = 0; i < *map->getRows(); ++i) {
    for (int j = 0; j < *map->getCols(); ++j) {
      if (*map->checkStage(i, j, ' ')) {
        ms.spaces.push_back(i);
        ms.numOfSpaces++;
      }
    }
  }
}

void Game::findNearestnPlace(int b, char ch) {
  for (int i = 0; i < *map->getRows(); ++i) {
    for (int j = 0; j < *map->getCols(); ++j) {
      if (!*map->checkStage(i, j, ' ')) {
        *map->setStage(i, j - 1, ch);
      }
    }
  }
}

bool Game::checkIfPlayerWon(char ch) {
  int counter = 0;

  for (int i = 0; i < 41; i++) {
    if (*map->stage[i] == ch) {
      for (int j = 1; j <= 4; j++) {
        int z = 0;
        while (*map->stage[z] == ch) {
          if (++z == 4)
            return true;
        }
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

  list <unsigned int>::iterator it;
  int b;
  std::cout << "Available spots are:" << std::endl;
  for(it = ms.spaces.begin(); it != ms.spaces.end(); ++it)
    std::cout << *it << ", ";
  std::endl;
  std::cout << "Type the number (that corresponds to a place in the map) to place the ball: ";
  std::cin >> b;

  findNearestnPlace(b);
  if (checkIfPlayerWon() && !updateGame()) {
    std::cout << "The game is over!\n" << *(pls + i)->getName() << " has won!" << std::endl;
    std::cout << "Score: " << *pls->getScore() << " : " << *(pls + 1)->getScore() << std::endl;
    return false;
  }
  system("clear");

  return true;
}
