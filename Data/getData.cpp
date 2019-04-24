#include <iostream>
#include <fstream>

#include "getData.h"

getData::getData() {
  std::ifstream f(path);
  std::string tmp;

  std::cout << "Loading map..." << std::endl;

  while (std::getline(f, tmp)) {
    stage += tmp;
    std::cout << stage << std::endl;
    std::cout << "----------" << std::endl;
  }

  std::cout << "Map loaded!" << std::endl;
}

void getData::show() {
  cout << stage << std::endl;
}
