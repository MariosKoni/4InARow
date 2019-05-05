#pragma once

#include <string>
#include <map>
#include <utility>

class Player {
private:
  std::string name;
  std::string favColor;
  std::pair<std::string, char> col;

  int score;

public:
  Player();

  std::string getName();
  char getColor();
  int getScore();
  void addScore();
};
