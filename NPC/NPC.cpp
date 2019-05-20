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

std::pair<int, int> NPC::generateCoordinates(std::shared_ptr<getData> map, char ch) {
  //Checks if there are at least 2 balls next to each other and if the space of the next remaining
  //blocks is sufficient for a win. If so, it blocks the player's momentum. If not, it places a ball next to its
  //own balls.
  int momentum = 0;
  int x = playerCoords.first;
  int y = playerCoords.second;
  bool defend = false;
  int threshold = 2;
  int win = 4;
  int attackWindow;
  int empty = 0;
  int _x, _y;

  std::pair<int, int> tmp;

  //North
  while (map->checkStage(x, y, ch)) {
    x--;
    momentum++;
  }
  if (momentum >= threshold) {
    _x = playerCoords.first + 1;
    x = playerCoords.first + 1;
    attackWindow = win - momentum;
    std::cout << attackWindow << std::endl;

    for (int i = 0; i < attackWindow; ++i) {
      if (map->checkStage(x, y, ' ')) {
        empty++;
        x++;
      }
    }
    if (empty == attackWindow) {
      defend = true;
      tmp.first = _x;
      tmp.second = y;

      return tmp;
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
    std::cout << attackWindow << std::endl;

    for (int i = 0; i < attackWindow; ++i) {
      if (map->checkStage(x, y, ' ')) {
        empty++;
        x--;
      }
    }
    if (empty == attackWindow) {
      defend = true;
      tmp.first = _x;
      tmp.second = y;

      return tmp;
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
      defend = true;
      tmp.first = x;
      tmp.second = _y;

      return tmp;
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
      defend = true;
      tmp.first = x;
      tmp.second = _y;

      return tmp;
    }
  }

  //Add attack mode to AI
  tmp.first = -1;
  tmp.second = -1;
  return tmp;
}

void NPC::insertCoords(int x, int y) {
  playerCoords.first = x;
  playerCoords.second = y;
}
