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

  std::string getName();
  std::map<std::string, char> getMap();
  int getScore();
  void setScore(int s);
};
