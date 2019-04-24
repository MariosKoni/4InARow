#include "Player.h"

#include <iostream>

Player::Player() {
  std::cout << "Hello player what's your name ?" << std::endl;
  std::cout << "Name: ";
  std::getline(std::cin, name);
  std::cout << "So, " << name << ", what's your favourite color ?" << std::endl;
  std::cout << "Color: ";
  std::cin >> favColor;
}

void Player::showInfo() {
  std::cout << name << std::endl;
  std::cout << favColor << std::endl;
}
