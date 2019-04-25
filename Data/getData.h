#pragma once

class getData {
private:
  const int rows = 6;
  const int cols = 7;
  const std::string path = "/home/toomlg4u/4InARow/Data/initData.txt";
  char stage[rows][cols];

public:
  getData();

  char[] getStage();
  void setToStage(int i, int j, char v);
  int getRows();
  int getCols();
};
