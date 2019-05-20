#include "NPC.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

void NPC::setInfo() {
  srand(time(NULL));

  name = names[rand() % names.size()];
  std::cout << "NPC name -> " << name << std::endl; //debug
  favColor = colours[rand() % colours.size()];
  std::cout << "NPC colour -> " << favColor << std::endl; //debug
  char f = favColor[0];
  col.first = favColor;
  col.second = f;
}

void NPC::generateCoordinates(std::vector<std::pair<int, int>> c) {
  srand(time(NULL));

  coords.first = rand() % findMax(1, c) + 1; //for x coordinates
  coords.second = rand() % findMax(2, c) + 1; //for y coordinates
}

int NPC::findMax(int i, std::vector<std::pair<int, int>> c) {
  int max;

  switch (i) {
    case 1:
      max = c[0].first;
      for(auto const& value : c) {
        if (value.first > max)
          max = value.first;
      }

      break;

    case 2:
      max = c[0].second;
      for(auto const& value : c) {
        if (value.second > max)
          max = value.second;
      }

      break;
  }

  return max;
}

std::pair<int, int> NPC::getCoords() {
  return coords;
}
