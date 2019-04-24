#pragma once

#include <string>

class Player {
private:
  std::string name;
  std::string favColor;
  std::map<std::string, char> col;

  int score;

public:
  Player();
};
