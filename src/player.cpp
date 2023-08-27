#include "player.h"

Player::Player() {
  firstName = "";
  lastName = "";
  stat = 0;
}

Player::Player(std::string first, std::string last, int s) {
  firstName = first;
  lastName = last;
  stat = s;
}