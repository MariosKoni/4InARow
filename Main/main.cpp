#include <iostream>

#include "../Data/getData.h"
#include "../Player/Player.h"

int main(int argc, char const *argv[]) {
  getData gd;
  Player pl;

  Game g1(pl, gd);
  return 0;
}
