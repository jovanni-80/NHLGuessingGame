#include "game.h"

const std::string statArr[10] = {"goals", "assists", "points", "penaltyMinutes", "gamesPlayed", "shots", "powerPlayGoals", "gameWinningGoals", "plusMinus", "overTimeGoals"};

const std::string teamArr[32] = {"New Jersey Devils", "..."};

Game::Game() {
	std::srand((unsigned) time(0));
	yearUpperBound = 2023;
	yearLowerBound = 1980;
	std::cout << "Game Created" << std::endl;
}

int Game::playRound() {
 	std::cout << "starting round" << std::endl;
	// get random teams
	std::string randTeam [2];
	
	// get random seasons
	std::string randSeasons [2];
	int randSeason1 = (std::rand() % (yearUpperBound - yearLowerBound + 1)) + yearLowerBound;
	int randSeason2 = (std::rand() % (yearUpperBound - yearLowerBound + 1)) + yearLowerBound;

	randSeasons[PLAYER_1] = std::to_string(randSeason1).append(std::to_string(randSeason1 + 1));
	randSeasons[PLAYER_2] = std::to_string(randSeason2).append(std::to_string(randSeason2 + 1));
	
	// get random stat
	int currStatIdx = std::rand() % sizeof(statArr)/sizeof(statArr[0]);
	currStat = statArr[currStatIdx];

	// compare player's stats

	// prompt user to enter guess

	// return if their guess is correct or not
	int correct = 0;
	std::string seasons = "20202021";

	return correct;
}
