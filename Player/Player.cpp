#include "Player.h"

#include "../Data/getData.h"

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <cctype>
#include <memory>

Player::Player() {
  score = 0;
}

void Player::setInfo() {
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

char Player::getColour() {
  return col.second;
}

int Player::getScore() {
  return score;
}

void Player::addScore() {
  score++;
}

void Player::changeColour(char c) {
  col.second = c;
}

//Dummies
std::pair<int, int> Player::generateCoordinates(std::shared_ptr<getData> map, char ch, unsigned int i){
  std::pair<int, int> dummy(-1, -1);
  return dummy;
}
void Player::insertCoords(int x, int y){}
bool Player::needToDefend(std::shared_ptr<getData> map, char ch){return false;}
