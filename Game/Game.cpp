#include "Game.h"
#include "../Player/Player.h"
#include "../Data/Data.h"

#include <iostream>

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

bool Game::updateGame(int pl1, int pl2, int b, char ch) {
  for (int i = 0; i < 41; i++) {
    if (i == b)
      *map->stage[i] = ch;
  }
  currentRound++;
  *pls->score = pl1;
  *(pls + 1)->score = pl2;

  if (currentRound > maxRounds)
    return false;

  return true;
}

void Game::checkAvailable() {
  //int i;
  unsigned int spaces[41];
  unsigned int space;

  for (int i = 0; i < 41; i++) {
    if (*map->stage[i] == ' ')
      spaces[i] = i;
      space++;
  }

  ms.s = space;
  ms.sp = spaces;
}

bool Game::play(unsigned int i) {
  if (i % 2 == 0)
    std::cout << "It's " << *pls->name << " to play" << std::endl;
  else
    std::cout << "It's " << *(pls + 1)->name << " to play" << std::endl;

  checkAvailable();
  //int j;
  int b;
  std::cout << "Available spots are:" << std::endl;
  for (int j = 0; j < ms.s; j++)
    std::cout << ms.sp[j] << ", ";
  std::endl;
  std::cout << "Type the number to place the ball: ";
  std::cin >> b;

}
