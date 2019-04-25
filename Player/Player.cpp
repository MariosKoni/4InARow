#include "Player.h"

#include <iostream>
#include <string>

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

std::string Player::getName() {
  return name;
}

std::map<std::string, char> Player::getMap() {
  return col;
}

int Player::getScore() {
  return score;
}

void Player::setScore(int s) {
  score = s;
}
