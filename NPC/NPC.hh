#pragma once

#include <string>
#include <vector>
#include <utility>
#include <memory>

#include "../Player/Player.hh"
#include "../Data/getData.hh"

class NPC : public Player {
private:
  std::vector<std::string> names {"Oliver", "Jack", "Harry", "Jacob", "Charlie", "Marios", "Amelia", "Olivia", "Isla", "Emily", "Poppy", "Deppy", "Philip"};
  std::vector<std::string> colours {"Blue", "Red"};

  std::pair<int, int> playerCoords;
  std::pair<int, int> npcCoords;
  //I could potentially have a best strategy, a set of coords of the best momentum here just to be more competitive

public:
  void setInfo();
  std::pair<int, int> generateCoordinates(std::unique_ptr<getData>&, char, int);
  bool needToDefend(std::unique_ptr<getData>&, char);
  void insertCoords(int, int);
};
