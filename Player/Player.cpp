#include "Player.h"

#include <iostream>

Player::Player() {
  std::cout << "Hello player what's your name ?" << std::endl;
  std::cout << "Name: ";
  std::getline(std::cin, name);
  std::cout << "So, " << name << ", what color do you prefer? Blue or red?" << std::endl;
  std::cout << "Color: ";
  std::cin >> favColor;
  char f = favColor[0];
  col.insert(std::pair<std::string, char>(favColor, f));
}
