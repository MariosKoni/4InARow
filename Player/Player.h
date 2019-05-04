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
  std::pair<std::string, char> getColor();
  int getScore();
  void setScore(int s);
};
