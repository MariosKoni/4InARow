#include "Player.h"

#include <iostream>
#include <string>
#include <map>
#include <utility>

Player::Player() {
  std::cout << "Hello player what's your name ?" << std::endl;
  std::cout << "Name: ";
  std::cin.ignore();
  std::getline(std::cin, name);
  std::cout << "So, " << name << ", what color do you prefer? Blue or red?" << std::endl;
  std::cout << "Color: ";
  std::cin >> favColor;
  char f = favColor[0];
  col.first = favColor;
  col.second = f;
  std::cout << col.second << std::endl;
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
