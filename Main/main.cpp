#include <iostream>

#include "../Data/getData.h"
#include "../Player/Player.h"
#include "../Game/Game.h"

int main(int argc, char const *argv[]) {
  getData gd;
  Player pl;
  Game g1(&pl, &gd);

  unsigned int i = 0;

  while(g1.play(i))
    ++i;
  return 0;
}
