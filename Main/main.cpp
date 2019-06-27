#include <iostream>

#include "../Game/Game.h"

int main() {
  int choice;

  do {
    system("clear");
    std::cout << "Welcome to 4 in a row!" << std::endl;
    std::cout << "1. New game" << std::endl;
    std::cout << "2. Load game" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << "Choice: ";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
      case 1: {
        Game g1(true);

        while(g1.play()){}

        break;
      }
      case 2: {
        Game g2(false);

        while(g2.play()){}

        break;
      }
      case 3:
        std::cout << "Goodbye..." << std::endl;
        break;
    }
  } while (choice != 3);

  return 0;
}
