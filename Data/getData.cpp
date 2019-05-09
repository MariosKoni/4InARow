#include <iostream>
#include <fstream>

#include "getData.h"

getData::getData() {
  std::ifstream f(path);
  std::string tmp;

  std::cout << "Loading map..." << std::endl;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++)
      f.get(stage[i][j]);
  }

  std::cout << "Map loaded!" << std::endl;

  f.close();
}

bool getData::checkStage(int i, int j, char c) {
  if (stage[i][j] == c)
    return true;
  else
    return false;
}

void getData::setToStage(int i, int j, char v) {
  stage[i][j] = v;
}

int getData::getRows() {
  return rows;
}

int getData::getCols() {
  return cols;
}

void getData::showStage() {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j)
      std::cout << stage[i][j];
    std::cout << std::endl;
  }
}
