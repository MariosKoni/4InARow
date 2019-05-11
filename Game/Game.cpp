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
    std::shared_ptr<Player> pl(new Player());
    pls.emplace_back(pl);
  }
  std::cout << "Insert the number of rounds that will be played: ";
  std::cin >> maxRounds;
  map = std::unique_ptr<getData>(new getData());
}

bool Game::updateGame() {

  if (currentRound > maxRounds)
    return false;

  spaces.clear();

  return true;
}

void Game::checkAvailable() {
  for (int i = 1; i < map->getRows() - 1; ++i) {
    for (int j = 1; j < map->getCols() - 1; ++j) {
      if (map->checkStage(i, j, ' ')) {
        std::pair<int ,int>spot(i, j);
        spaces.emplace_back(spot);
      }
    }
  }
}

bool Game::checkIfPlayerWon(char ch) {
  int counter = 0;

  for (int i = 1; i < map->getRows() - 1; ++i) {
    for (int j = 1; j < map->getCols() - 1; ++j) {
      if (map->checkStage(i, j, ch)) {
        std::cout << "Entered with i = " << i << " j = " << j << " ch = " << ch << std::endl;
        int x = i;
        int y = j;

        //North
        while (map->checkStage(x, y, ch)) {
          x--;
          counter++;
        }
        if (counter == 4)
          return true;

        //South
        x = i;
        y = j;
        counter = 0;
        while (map->checkStage(x, y, ch)) {
          x++;
          counter++;
        }
        if (counter == 4)
          return true;

        //East
        x = i;
        y = j;
        counter = 0;
        while (map->checkStage(x, y, ch)) {
          y++;
          counter++;
        }
        if (counter == 4)
          return true;

        //West
        x = i;
        y = j;
        counter = 0;
        while (map->checkStage(x, y, ch)) {
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

  std::cout << "Round: " << currentRound << std::endl;

  if (i % 2 == 0) {
    std::cout << "It's " << pls[0]->getName() << " turn to play" << std::endl;
    turn = 0;
  }
  else {
    std::cout << "It's " << pls[1]->getName() << " turn to play" << std::endl;
    turn = 1;
  }

  std::cout << std::endl;
  map->showStage();
  std::cout << std::endl;

  checkAvailable();

  int x, y;
  std::cout << "Available spots are:" << std::endl;
  for(auto const& value : spaces)
    std::cout << "[" << value.first << "]" << "[" << value.second << "]" << ", ";
  std::cout << std::endl;
  std::cout << "Type the numbers (that corresponds to a place in the map) to place the ball: ";
  std::cin >> x >> y;

  map->setToStage(x, y, pls[turn]->getColor());

  if (checkIfPlayerWon(pls[turn]->getColor())) {
    currentRound++;
    pls[turn]->addScore();
  }
  if (!updateGame()) {
    std::cout << "The game is over!" << std::endl;
    if (pls[0]->getScore() > pls[1]->getScore())
      std::cout << pls[0]->getName() << " has won!" << std::endl;
    else if (pls[0]->getScore() < pls[1]->getScore())
      std::cout << pls[1]->getName() << " has won!" << std::endl;
    else
      std::cout << "Its a draw!" << std::endl;
    std::cout << "Score: " << pls[0]->getScore() << " : " << pls[1]->getScore() << std::endl;

    return false;
  }
  system("clear");

  return true;
}
