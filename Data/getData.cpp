#include <iostream>
#include <fstream>

#include "getData.h"

getData::getData() {}

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
  int h = 0;
  for (int k = 0; k < cols; ++k)
    std::cout << k;
  std::cout << std::endl;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j)
      std::cout << stage[i][j];
    std::cout << " " << h;
    h++;
    std::cout << std::endl;
  }
}

void getData::resetStage() {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (i == 0 || i == rows)
        stage[i][j] = '#';
      if (j > 1 && j < cols)
        stage[i][j] = ' ';
      if (j == 0 || j == cols)
        stage[i][j] = '#';
    }
  }
}
