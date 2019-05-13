#pragma once

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

  void setToStage(int i, int j, char v);
  int getRows();
  int getCols();
  bool checkStage(int i, int j, char c);
  void showStage();
  void resetStage();
};
