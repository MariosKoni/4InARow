#pragma once

#include <string>

#define rows 6
#define cols 7

class getData {
private:
  const std::string path = "/home/toomlg4u/4InARow/Data/initData.txt";
  char stage[rows][cols] = {'#', '#', '#', '#', '#', '#', '#',
                            '#', ' ', ' ', ' ', ' ', ' ', '#',
                            '#', ' ', ' ', ' ', ' ', ' ', '#',
                            '#', ' ', ' ', ' ', ' ', ' ', '#',
                            '#', ' ', ' ', ' ', ' ', ' ', '#',
                            '#', '#', '#', '#', '#', '#', '#'};

public:
  getData();

  bool setToStage(int, int, char);
  int getRows();
  int getCols();
  bool checkStage(int, int, char);
  void showStage();
  void resetStage();
};
