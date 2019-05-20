#pragma once

#include <string>
#include <vector>
#include <utility>
#include <memory>

#include "../Player/Player.h"

class NPC : public Player {
private:
  std::vector<std::string> names {"Oliver", "Jack", "Harry", "Jacob", "Charlie", "Amelia", "Olivia", "Isla", "Emily", "Poppy"};
  std::vector<std::string> colours {"Blue", "Red"};

  std::pair<int, int> playerCoords;

public:
  void setInfo();
  std::pair<int, int> generateCoordinates(std::shared_ptr<getData>, char);
  void insertCoords(int, int);
};
