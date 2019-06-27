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
  std::cout << "So, " << name << ", what color do you prefer? Blue or Red?" << std::endl;
  do {
    std::cout << "Color: ";
    std::cin >> favColor;
    std::cin.ignore();
    if (favColor.compare("Blue") != 0 && favColor.compare("blue") != 0 && favColor.compare("Red") != 0 && favColor.compare("red") != 0) {
      std::cout << "Type Blue/Red" << std::endl;
      std::cin >> favColor;
    }
  } while (favColor.compare("Blue") != 0 && favColor.compare("blue") != 0 && favColor.compare("Red") != 0 && favColor.compare("red") != 0);
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

std::string Player::getColF() {
  return col.first;
}

void Player::setName(std::string n) {
  name = n;
}

void Player::setColour1(std::string c1) {
  col.first = c1;
}

void Player::setColour2(char c2) {
  col.second = c2;
}

void Player::setScore(int s) {
  score = s;
}

//Dummies
std::pair<int, int> Player::generateCoordinates(std::shared_ptr<getData> map, char ch, int i){
  std::pair<int, int> dummy(-1, -1);
  return dummy;
}
void Player::insertCoords(int x, int y){}
bool Player::needToDefend(std::shared_ptr<getData> map, char ch){return false;}
