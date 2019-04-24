#pragma once

#include <string>

class Player {
private:
  std::string name;
  std::string favColor;

public:
  Player();
  void showInfo();
};
