#include <iostream>

#include "../Game/Game.h"

int main(int argc, char const *argv[]) {
  Game g1;

  unsigned int i = 0;

  while(g1.play(i))
    ++i;
  return 0;
}
