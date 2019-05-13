#include "Game.h"
#include "../Player/Player.h"
#include "../Data/getData.h"

#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <cctype>

Game::Game() {
  currentRound = 1;

  std::cout << "Welcome to " << gameTitle << "!" << std::endl;
  std::cout << "Select number of players\n1. One vs AI\n2. Two\nChoice: ";
  std::cin >> choice;
  for (int i = 0; i < choice; ++i) {
    char c;
    std::shared_ptr<Player> pl(new Player());
    if (i == 0)
      c = pl->getColour();
    if (i == 1 && (pl->getColour() == c)) {
      std::cout << "\033[1;31mYou cannot have the same color as your opponent!\033[0m" << std::endl;
      do {
        std::string newColour;
        std::cout << "New colour: ";
        std::cin >> newColour;
        std::cin.ignore();
        pl->changeColour(std::toupper(newColour[0]));
      } while(pl->getColour() == c);
    }
    pls.emplace_back(pl);
  }
  std::cout << "Insert the number of rounds that will be played: ";
  std::cin >> maxRounds;
  map = std::unique_ptr<getData>(new getData());

  system("clear");
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
        counter = 0;
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

void Game::resetGame() {
  currentRound++;
  map->resetStage();
}

bool Game::play(unsigned int i) {
  int x, y;
  int turn;

  std::cout << "\033[1;31mRound:\033[0m " << currentRound << std::endl;

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

  if (!spaces.size()) {
    std::cout << "\033[1;31mNo spots are available!\033[0m" << std::endl;
    resetGame();
    return true;
  }

  std::cout << "Available spots are:" << std::endl;
  for(auto const& value : spaces)
    std::cout << "[" << value.first << "]" << "[" << value.second << "]" << ", ";
  std::cout << std::endl;

  do {
    std::cout << "Type the numbers (that corresponds to a place in the map) to place the ball: ";
    std::cin >> x >> y;
  } while(!map->setToStage(x, y, pls[turn]->getColour()));

  if (checkIfPlayerWon(pls[turn]->getColour())) {
    pls[turn]->addScore();
    resetGame();
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
