#include "game.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <cpr/cpr.h>
#include <string>

#define TEAM_FILE_PATH "/home/jovanni/Projects/NHLGuessingGame/src/teamIDs.txt"

int Game::getRandTeamID() {
	// generate a random number from 1-32
	int randLine = std::rand() % 32 + 1;
	std::string teamInfo;
	int teamID = -1;
	std::ifstream teamFile;
	teamFile.open(TEAM_FILE_PATH, std::ios::in);

	// read that many lines into the team ID file
	if (teamFile) {

		// get the random team from the file
		std::string line;
		int lineNumber = 0;
		while(std::getline(teamFile, line) && lineNumber < randLine - 1) {
			lineNumber++;
		}

		teamFile.close();

		// separate the team name and ID
		std::size_t commaSep = line.find(',');
		std::string teamName = line.substr(0, commaSep);
		teamID = std::stoi(line.substr(commaSep+1));

		std::cout << "Team name: " << teamName << std::endl
			<< "Team ID: " << teamID << std::endl;
	}
	else {
		std::cout << "OpenFileError" << std::endl;
	}

	/// return team id
	return teamID;
}

int Game::getRandPlayerID(int teamID) {
	// return player ID
	return 0;
}

std::string Game::generateRandStat() {
	int randStatIdx = std::rand() % sizeof(statArr)/sizeof(statArr[0]);

	return statArr[randStatIdx];
}

std::string Game::generateAPIRequest(int teamID, int playerID, std::string statName) {
	int randSeason = (std::rand() % (yearUpperBound - yearLowerBound + 1)) + yearLowerBound;
	std::string randSeasons = std::to_string(randSeason).append(std::to_string(randSeason + 1));

	return "";
}

Game::Game() {
	std::srand((unsigned) time(0));
	yearUpperBound = 2023;
	yearLowerBound = 1980;
	std::cout << "Game Created" << std::endl;

}

bool Game::playRound() {
 	std::cout << "starting round" << std::endl;
	// get random teams
	std::string randTeam [2];
	
	// get random seasons
	std::string randSeasons [2];
	int randSeason1 = (std::rand() % (yearUpperBound - yearLowerBound + 1)) + yearLowerBound;
	int randSeason2 = (std::rand() % (yearUpperBound - yearLowerBound + 1)) + yearLowerBound;

	randSeasons[PLAYER_1] = std::to_string(randSeason1).append(std::to_string(randSeason1 + 1));
	randSeasons[PLAYER_2] = std::to_string(randSeason2).append(std::to_string(randSeason2 + 1));
	
	getRandTeamID();
	currStat = generateRandStat();

	// choose player from team and season (and potentially based on difficulty)
	// create player

	// create a random player for now
	int p1stat = std::rand() % 100 + 1;
	int p2stat = std::rand() % 100 + 1;

	Player p1("Jovanni", "Rodriguez", p1stat);
	Player p2("Justin", "Lantz", p2stat);

	// prompt user to enter guess
	std::cout << "Who has more " << currStat << "?\n";
	std::cout << "1) " << p1.getName() << " " << p1.getStat() << std::endl;
	std::cout << "2) " << p2.getName() << " " << p2.getStat() << std::endl;


	// return if their guess is correct or not
	// compare player's stats
	int userAnswer;
	std::cin >> userAnswer;
	bool answeredCorrectly = false;
	
	answeredCorrectly = userAnswer == 1 ? p1.getStat() > p2.getStat(): p2.getStat() > p1.getStat(); 
	std::string outputResult = answeredCorrectly ? "correct!": "incorrect.";

	std::cout << "You were " << outputResult << std::endl;

	return answeredCorrectly;
}
