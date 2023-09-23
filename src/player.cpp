#include "player.h"

Player::Player() {
  firstName = "";
  lastName = "";
}

Player::Player(std::string first, std::string last, int id, std::string s) {
  firstName = first;
  lastName = last;
  id = id;

  // make api call for stat
  stat = 0;
}