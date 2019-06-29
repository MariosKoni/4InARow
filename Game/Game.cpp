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
#include <fstream>
#include <filesystem>

void Game::save() {
  std::string saveFileName;
  std::string nSave;
  char answ;

  std::cout << "Save file name: ";
  std::getline(std::cin, saveFileName);
  nSave = path + saveFileName;
  if (nSave.find(".txt") == std::string::npos)
    nSave = path + saveFileName + ".txt";
  for(auto& p : std::filesystem::directory_iterator(p)) {
    if (p.path().string().compare(nSave) == 0) {
      std::cout << "\"" << nSave << "\" already exists!" << std::endl << "Do you wish to overwrite it? (y/n): ";
      std::cin >> answ;
      std::cin.ignore();
      switch (answ) {
        case 'Y':
        case 'y': {
          break;
        }
        case 'N':
        case 'n':
          std::cout << "Save file name: ";
          std::getline(std::cin, saveFileName);
          nSave = path + saveFileName;
          if (nSave.find(".txt") == std::string::npos)
            nSave = path + saveFileName + ".txt";
          break;
      }
      break;
    }
  }

  std::ofstream dataFile(nSave);

  if (dataFile.is_open()) {
    if (!dataFile.bad()) {
      // Write whole map in file
      dataFile << "Data" << std::endl;
      for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j)
          dataFile << i << j << map->getArray(i, j) << std::endl;
      }

      // Write game data in file
      dataFile << "Game" << std::endl;
      dataFile << maxRounds << std::endl;
      dataFile << currentRound << std::endl;
      dataFile << choice << std::endl;
      dataFile << i << std::endl;

      // Write player data in file
      dataFile << "Player" << std::endl;
      for (int i = 0; i < pls.size(); ++i) {
        dataFile << pls[i]->getName() << std::endl;
        dataFile << pls[i]->getColF() << std::endl;
        dataFile << pls[i]->getColour() << std::endl;
        dataFile << pls[i]->getScore() << std::endl;
      }
    }
  }

  dataFile.close();
}

bool Game::load() {
  std::ifstream dataFile;
  bool hasFilesToLoad;

  int ch;
  int offset = 0;
  std::vector<std::string> loadFiles;
  std::cout << "Select save file to load (by typing the number)" << std::endl;
  for(auto& p : std::filesystem::directory_iterator(p))
    loadFiles.emplace_back(p.path().string());

  if (loadFiles.size()) {
    hasFilesToLoad = true;
    for (auto const& file : loadFiles)
      std::cout << ++offset << ". " << file << std::endl;
  } else {
      hasFilesToLoad = false;
      std::cout << "There are no files to load from..." << std::endl;
    }

  if (hasFilesToLoad) {
    do {
      std::cout << "Choice: ";
      std::cin >> ch;
      std::cin.ignore();
      if (ch < 1 || ch > loadFiles.size())
        std::cout << "Give a valid number!" << std::endl;
    } while (ch < 1 || ch > loadFiles.size());

    dataFile.open(loadFiles[ch - 1]);

    if (dataFile.is_open()) {
      if (!dataFile.bad()) {
        //Dummy reading
        std::string tmp;
        std::getline(dataFile, tmp);

        //Load map
        std::getline(dataFile, tmp);
        while (tmp.compare("Game") != 0) {
          map->setToStage((tmp[0] - '0'), (tmp[1] - '0'), tmp[2]);
          std::getline(dataFile, tmp);
        }

        //Load the game data
        std::getline(dataFile, tmp);
        maxRounds = std::stoi(tmp, NULL);
        std::getline(dataFile, tmp);
        currentRound = std::stoi(tmp, NULL);
        std::getline(dataFile, tmp);
        choice = std::stoi(tmp, NULL);
        std::getline(dataFile, tmp);
        i = std::stoi(tmp, NULL);

        //Dummy reading
        std::getline(dataFile, tmp);

        //Load the player data
        for (int i = 0; i < pls.size(); ++i) {
          std::getline(dataFile, tmp);
          pls[i]->setName(tmp);
          std::getline(dataFile, tmp);
          pls[i]->setColour1(tmp);
          std::getline(dataFile, tmp);
          pls[i]->setColour2(tmp[0]);
          std::getline(dataFile, tmp);
          pls[i]->setScore(std::stoi(tmp, NULL));
        }
      }
    }

    dataFile.close();

    return true;
  }

  return false;
}

Game::Game(bool isGameNew) {
  //If user selected a new game
  if (isGameNew) {
    char ch;
    currentRound = 1;
    i = 0;

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

        std::shared_ptr<Player> plN(new NPC());
        plN->setInfo();
        ch = plN->getColour();
        pls.emplace_back(plN);

        char c;
        std::shared_ptr<Player> pl(new Player());
        pl->setInfo();
        c = pl->getColour();
        if (c == ch) {
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

  } else { //If user selected load game
    std::shared_ptr<Player> plN(new NPC());
    pls.emplace_back(plN);
    std::shared_ptr<Player> pl(new Player());
    pls.emplace_back(pl);
    map = std::unique_ptr<getData>(new getData());

    if (load()) {
      std::cout << "Game loaded!" << std::endl << "Press any key to play...";
      getchar();
    } else
        canPlay = false;
  }

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
  int opt;

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

      std::cout << "Options:\n1. Type coordinates (continue game)\n2. Save current game and exit\n3. Exit\nChoice: ";
      do {
        std::cin >> opt;
        std::cin.ignore();
        if (opt < 1 || opt > 3)
          std::cout << "Please give a proper option (1 or 2 or 3)!" << std::endl;
      } while(opt < 1 || opt > 3);

      switch (opt) {
        case 1:
          do {
            std::cout << "Type the row followed by a space and a column to place the ball: ";
            std::cin >> x >> y;
            std::cin.ignore();
          } while(!map->setToStage(x, y, pls[turn]->getColour()));

          break;

        case 2:
          save();
          std::cout << "Game saved!" << std::endl << "Press any key to continue...";
          getchar();
          return false;

        case 3:
          return false;
      }

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

          std::cout << "Options:\n1. Type coordinates (continue game)\n2. Save current game and exit\n3. Exit\nChoice: ";
          do {
            std::cin >> opt;
            std::cin.ignore();
            if (opt < 1 || opt > 3)
              std::cout << "Please give a proper option (1 or 2 or 3)!" << std::endl;
          } while(opt < 1 || opt > 3);

          switch (opt) {
            case 1:
              do {
                std::cout << "Type the row followed by a space and a column to place the ball: ";
                std::cin >> x >> y;
                std::cin.ignore();
              } while(!map->setToStage(x, y, pls[turn]->getColour()));

              break;

            case 2:
              save();
              std::cout << "Game saved!" << std::endl << "Press any key to continue...";
              getchar();

              return false;

            case 3:
              return false;
          }
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

    system("clear");
    return true;
}

bool Game::getCanPlay() {
  return canPlay;
}
