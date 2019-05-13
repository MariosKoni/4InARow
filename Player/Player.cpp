#include "Player.h"

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <cctype>

Player::Player() {
  score = 0;

  std::cout << "Hello player what's your name ?" << std::endl;
  std::cout << "Name: ";
  std::cin.ignore();
  std::getline(std::cin, name);
  std::cout << "So, " << name << ", what color do you prefer? Blue or red?" << std::endl;
  std::cout << "Color: ";
  std::cin >> favColor;
  char f = std::toupper(favColor[0]);
  col.first = favColor;
  col.second = f;
}

std::string Player::getName() {
  return name;
}

char Player::getColor() {
  return col.second;
}

int Player::getScore() {
  return score;
}

void Player::addScore() {
  score++;
}
