#include <iostream>
#include <fstream>

#include "getData.h"

getData::getData() {
  std::ifstream f(path);
  std::string tmp;

  std::cout << "Loading map..." << std::endl;

  int i = 0;
  while (f.get(stage[i])) {
    i++;
  }

  std::cout << "Map loaded!" << std::endl;

  f.close();
}
