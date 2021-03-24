#pragma once

#include "../Data/getData.hh"

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

  bool isFirst = false;

public:
  Player();
  Player(std::string&, std::pair<std::string, char>); // For multi

  std::string getName();
  char getColour();
  void addScore();
  void changeColour(char);
  std::string getColF();
  int getScore();
  void setName(std::string&);
  void setColour1(std::string&);
  void setColour2(char);
  void setScore(int);
  void setStatus(bool);

  virtual void setInfo();
  virtual std::pair<int, int> generateCoordinates(std::unique_ptr<getData>&, char, int);
  virtual bool needToDefend(std::unique_ptr<getData>&, char);
  virtual void insertCoords(int, int);
};
