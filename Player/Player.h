#pragma once

#include "../Data/getData.h"

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <memory>

class Player {
protected:
  std::string name;
  std::string favColor;
  std::pair<std::string, char> col;

  int score;

public:
  Player();

  virtual void setInfo();
  std::string getName();
  char getColour();
  int getScore();
  void addScore();
  void changeColour(char);
  virtual std::pair<int, int> generateCoordinates(std::shared_ptr<getData>, char, int);
  virtual bool needToDefend(std::shared_ptr<getData>, char);
  virtual void insertCoords(int, int);
};
