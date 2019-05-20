#pragma once

#include <string>
#include <vector>
#include <utility>

#include "../Player/Player.h"

class NPC : public Player {
private:
  std::vector<std::string> names {"Oliver", "Jack", "Harry", "Jacob", "Charlie", "Amelia", "Olivia", "Isla", "Emily", "Poppy"};
  std::vector<std::string> colours {"Blue", "Red"};
  std::pair<int, int> coords;

public:
  void setInfo();
  void generateCoordinates(std::vector<std::pair<int, int>>);
  int findMax(int, std::vector<std::pair<int, int>>);
  std::pair<int, int> getCoords();
};
