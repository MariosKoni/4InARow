#include "NPC.h"

#include "../Data/getData.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <memory>

void NPC::setInfo() {
  srand(time(NULL));

  name = names[rand() % names.size()];
  favColor = colours[rand() % colours.size()];
  char f = favColor[0];
  col.first = favColor;
  col.second = f;

  std::cout << "Opponent: " << name << std::endl << "Colour: " << favColor << std::endl;
}

std::pair<int, int> NPC::generateCoordinates(std::shared_ptr<getData> map, char ch, int i) {
  //Checks if there are at least 2 balls next to each other and if the space of the next remaining
  //blocks is sufficient for a win using needToDefend method. If so, it blocks the player's momentum.
  //If not, it places a ball next to its own balls.

  //If it's the first turn of the round then compute a random x,y pos.
  if (!i) {
    srand(time(NULL));

    npcCoords.first = rand() % (rows - 2) + 1;
    npcCoords.second = rand() % (cols - 2) + 1;

    return npcCoords;
  }

  if (needToDefend(map, ch))
    return npcCoords;
  else {
    for (int i = 1; i < map->getRows() - 1; ++i) {
      for (int j = 1; j < map->getCols() - 1; ++j) {
        if (map->checkStage(i, j, col.second)) {
          //North
          if (map->checkStage(i - 1, j, ' ')) {
            npcCoords.first = i - 1;
            npcCoords.second = j;
            return npcCoords;
            //South
          } else if (map->checkStage(i + 1, j, ' ')) {
            npcCoords.first = i + 1;
            npcCoords.second = j;
            return npcCoords;
            //East
          } else if (map->checkStage(i, j + 1, ' ')) {
            npcCoords.first = i;
            npcCoords.second = j + 1;
            return npcCoords;
            //West
          } else if (map->checkStage(i, j - 1, ' ')) {
            npcCoords.first = i;
            npcCoords.second = j - 1;
            return npcCoords;
          }
        }
      }
    }
  }
}

bool NPC::needToDefend(std::shared_ptr<getData> map, char ch) {
  int momentum = 0;
  int x = playerCoords.first;
  int y = playerCoords.second;
  int threshold = 2;
  int win = 4;
  int attackWindow;
  int empty = 0;
  int _x, _y;

  //North
  while (map->checkStage(x, y, ch)) {
    x--;
    momentum++;
  }
  if (momentum >= threshold) {
    _x = playerCoords.first + 1;
    x = playerCoords.first + 1;
    attackWindow = win - momentum;

    for (int i = 0; i < attackWindow; ++i) {
      if (map->checkStage(x, y, ' ')) {
        empty++;
        x++;
      }
    }
    if (empty == attackWindow) {
      npcCoords.first = _x;
      npcCoords.second = y;

      return true;
    }
  }

  //South
  momentum = 0;
  x = playerCoords.first;
  y = playerCoords.second;

  while (map->checkStage(x, y, ch)) {
    x++;
    momentum++;
  }
  if (momentum >= threshold) {
    _x = playerCoords.first - 1;
    x = playerCoords.first - 1;
    attackWindow = win - momentum;

    for (int i = 0; i < attackWindow; ++i) {
      if (map->checkStage(x, y, ' ')) {
        empty++;
        x--;
      }
    }
    if (empty == attackWindow) {
      npcCoords.first = _x;
      npcCoords.second = y;

      return true;
    }
  }

  //East
  momentum = 0;
  x = playerCoords.first;
  y = playerCoords.second;

  while (map->checkStage(x, y, ch)) {
    y++;
    momentum++;
  }
  if (momentum >= threshold) {
    _y = playerCoords.second - 1;
    y = playerCoords.second - 1;
    attackWindow = win - momentum;

    for (int i = 0; i < attackWindow; ++i) {
      if (map->checkStage(x, y, ' ')) {
        empty++;
        y--;
      }
    }
    if (empty == attackWindow) {
      npcCoords.first = x;
      npcCoords.second = _y;

      return true;
    }
  }

  //West
  momentum = 0;
  x = playerCoords.first;
  y = playerCoords.second;

  while (map->checkStage(x, y, ch)) {
    y--;
    momentum++;
  }
  if (momentum >= threshold) {
    _y = playerCoords.second + 1;
    y = playerCoords.second + 1;
    attackWindow = win - momentum;

    for (int i = 0; i < attackWindow; ++i) {
      if (map->checkStage(x, y, ' ')) {
        empty++;
        y++;
      }
    }
    if (empty == attackWindow) {
      npcCoords.first = x;
      npcCoords.second = _y;

      return true;
    }
  }

  return false;
}

void NPC::insertCoords(int x, int y) {
  playerCoords.first = x;
  playerCoords.second = y;
}
