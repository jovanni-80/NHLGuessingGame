#include <iostream>
#include <cstdlib>

const std::string statArr[] = {"goals", "assists", "points", "penaltyMinutes", "gamesPlayed", "shots", "powerPlayGoals", "gameWinningGoals", "plusMinus", "overTimeGoals"};

// finishing putting in all the teams names/IDs
const std::string teamArr[] = {"New Jersey Devils", "..."}

std::string getRandStat();

std::string getRandTeam();

int main(int argc, char** argv) {

	srand((unsigned) time(NULL));	// seed


	return 0;
}

std::string getRandStat(){
	int randStatIdx = rand() % sizeof(statArr)/sizeof(statArr[0]);
	return statArr[randStatIdx];
}

std::string getRandTeam() {
	int randTeamIdx = rand() % sizeof(teamArr)/sizeof(teamArr[0])
	return teamArr[randTeamIdx];
}
