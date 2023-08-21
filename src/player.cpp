#include "player.h"

Player::Player() {
	firstName = "";
	lastName = "";
}

Player::Player(std::string first, std::string last, int stats[sizeof(statArr)/sizeof(statArr[0])]) {
	firstName = first;
	lastName = last;

	for(int i = 0; i < sizeof(statArr)/sizeof(statArr[0]); i++) {
		statsMap[statArr[i]] = stats[i];
	}
}

int Player::getStat(std::string statName) {
	int ret = -1;

	if (firstName != "") {
		return statsMap[statName];
	}

	return -1;
}
