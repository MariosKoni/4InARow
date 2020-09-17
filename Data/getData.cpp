#include "getData.hh"

#include <iostream>

getData::getData() {}

bool getData::checkStage(int i, int j, char c) {
  if (stage[i][j] == c)
    return true;
  else
    return false;
}

bool getData::setToStage(int i, int j, char v) {
  if (checkStage(i, j, ' ')) {
      stage[i][j] = v;
      return true;
  }

  return false;
}

int getData::getRows() {
  return rows;
}

int getData::getCols() {
  return cols;
}

void getData::showStage() {
  int h = 0;
  for (int k = 0; k < cols; ++k)
    std::cout << k;
  std::cout << std::endl;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (stage[i][j] == 'B')
        std::cout << "\033[1;34m" << stage[i][j] << "\033[0m";
      else if (stage[i][j] == 'R')
        std::cout << "\033[1;31m" << stage[i][j] << "\033[0m";
      else
        std::cout << stage[i][j];
    }
    std::cout << " " << h;
    h++;
    std::cout << std::endl;
  }
}

void getData::resetStage() {
  for (int i = 1; i < rows - 1; ++i) {
    for (int j = 1; j < cols - 1; ++j)
      stage[i][j] = ' ';
  }
}

char getData::getArray(int i, int j) {
  return stage[i][j];
}
