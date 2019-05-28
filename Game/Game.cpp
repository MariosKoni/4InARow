#include "Game.h"
#include "../Player/Player.h"
#include "../Data/getData.h"
#include "../NPC/NPC.h"

#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <cctype>
#include <chrono>
#include <thread>

Game::Game() {
  char ch;
  currentRound = 1;
  i = 0;

  std::cout << "Welcome to " << gameTitle << "!" << std::endl;
  std::cout << "Select number of players\n1. One vs AI\n2. Two\nChoice: ";
  do {
    std::cin >> choice;
    if (choice < 1 || choice > 2)
      std::cout << "Please give a proper option (1 or 2)!" << std::endl;
  } while(choice < 1 || choice > 2);

  switch (choice) {
    //Player vs AI
    case 1: {
      char ch;

      std::shared_ptr<Player> pl(new NPC());
      pl->setInfo();
      ch = pl->getColour();
      pls.emplace_back(pl);

      for (int i = 0; i < choice; ++i) {
        char c;
        std::shared_ptr<Player> pl(new Player());
        pl->setInfo();
        if (i == 0)
          c = pl->getColour();
        if ((i == 1 && (pl->getColour() == c)) || (pl->getColour() == ch)) {
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

      break;
    }

    //Two (physical) players
    case 2:
      for (int i = 0; i < choice; ++i) {
        char c;
        std::shared_ptr<Player> pl(new Player());
        pl->setInfo();
        if (i == 0)
          c = pl->getColour();
        if ((i == 1 && (pl->getColour() == c)) || (pl->getColour() == ch)) {
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

      break;
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
  i++;

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
  i = 0;
}

void Game::checkWinner() {
  std::cout << "The game is over!" << std::endl;
  if (pls[0]->getScore() > pls[1]->getScore())
    std::cout << pls[0]->getName() << " has won!" << std::endl;
  else if (pls[0]->getScore() < pls[1]->getScore())
    std::cout << pls[1]->getName() << " has won!" << std::endl;
  else
    std::cout << "Its a draw!" << std::endl;
  std::cout << "Score: " << pls[0]->getScore() << " : " << pls[1]->getScore() << std::endl;
}

bool Game::play() {
  int x, y;
  int turn;

  std::cout << "\033[1;31mRound:\033[0m " << currentRound << std::endl;

  switch(choice) {
    //Two (physical) players
    case 2:
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

        if (!updateGame()) {
          checkWinner();
          return false;
        } else {
          resetGame();
          return true;
        }
      }

      std::cout << "Available spots are:" << std::endl;
      for(auto const& value : spaces)
        std::cout << "[" << value.first << "]" << "[" << value.second << "]" << ", ";
      std::cout << std::endl;

      do {
        std::cout << "Type the row followed by a space and a column to place the ball: ";
        std::cin >> x >> y;
      } while(!map->setToStage(x, y, pls[turn]->getColour()));

      if (checkIfPlayerWon(pls[turn]->getColour())) {
        pls[turn]->addScore();
        resetGame();
      }
      if (!updateGame()) {
        checkWinner();

        return false;
      }

      break;

      //Player vs AI
      case 1:
        if (i % 2 == 0) {
          std::cout << "It's " << pls[0]->getName() << " turn to play" << std::endl;
          turn = 0;
        }
        else {
          std::cout << "It's " << pls[1]->getName() << " turn to play" << std::endl;
          turn = 1;
        }

        if (turn == 1) {
          std::cout << std::endl;
          map->showStage();
          std::cout << std::endl;
        }

        checkAvailable();

        if (!spaces.size()) {
          std::cout << "\033[1;31mNo spots are available!\033[0m" << std::endl;

          if (!updateGame()) {
            checkWinner();
            return false;
          } else {
            resetGame();
            return true;
          }
        }

        if (turn == 1) {
          std::cout << "Available spots are:" << std::endl;
          for(auto const& value : spaces)
            std::cout << "[" << value.first << "]" << "[" << value.second << "]" << ", ";
          std::cout << std::endl;

          do {
            std::cout << "Type the row followed by a space and a column to place the ball: ";
            std::cin >> x >> y;
          } while(!map->setToStage(x, y, pls[turn]->getColour()));
          pls[0]->insertCoords(x, y);
        } else {
            std::cout << pls[0]->getName() << " is thinking...kinda..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            std::pair<int, int> tmp;

            do {
              tmp = pls[0]->generateCoordinates(map, pls[1]->getColour(), i);
            } while(!map->setToStage(tmp.first, tmp.second, pls[0]->getColour()));
        }

        if (checkIfPlayerWon(pls[turn]->getColour())) {
          pls[turn]->addScore();
          resetGame();

          return true;
        }
        if (!updateGame()) {
          checkWinner();

          return false;
        }

        break;
    }

    //system("clear");
    return true;
}
