#include <iostream>

#include "../Game/Game.hh"

int main() {
  int choice;

  do {
    #if defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
    system("clear");
    #elif _WIN32
    system("cls");
    #endif
    std::cout << "Welcome to 4 in a row!" << std::endl;
    std::cout << "1. New game" << std::endl;
    std::cout << "2. Load game" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << "\nChoice: ";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
      case 1: {
        Game g1(true);

        while(g1.play()){}

        g1.getwConnThread().join();

        break;
      }
      case 2: {
        Game g2(false);

        if (g2.getCanPlay()) {
          while(g2.play()){}
        }

        break;
      }
      case 3:
        std::cout << "Goodbye..." << std::endl;
        break;
    }
  } while (choice != 3);

  return 0;
}
