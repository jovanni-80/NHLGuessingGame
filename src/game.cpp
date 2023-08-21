#include "game.h"
#include <fstream>

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
	
	// choose random stat
	int currStatIdx = std::rand() % sizeof(statArr)/sizeof(statArr[0]);
	currStat = statArr[currStatIdx];

	// choose player from team and season (and potentially based on difficulty)
	// create player

	// create a random player for now
	int p1stats [10];
	int p2stats [10];

	for (int i = 0; i < 10; i++) {
		p1stats[i] = std::rand() % 100 + 1;
		p2stats[i] = std::rand() % 100 + 1;
	}

	Player p1("Jovanni", "Rodriguez", p1stats);
	Player p2("Justin", "Lantz", p2stats);

	// compare player's stats

	// prompt user to enter guess
	std::cout << "Who has more " << currStat << "?\n";
	std::cout << "1) " << p1.getName() << " " << p1.getStat(currStat) << std::endl;
	std::cout << "2) " << p2.getName() << " " << p2.getStat(currStat) << std::endl;


	// return if their guess is correct or not
	int userAnswer;
	std::cin >> userAnswer;
	bool answeredCorrectly = false;
	
	answeredCorrectly = userAnswer == 1 ? p1.getStat(currStat) > p2.getStat(currStat): p2.getStat(currStat) > p1.getStat(currStat); 

	std::string outputResult = answeredCorrectly ? "correct!": "incorrect.";
	std::cout << "You were " << outputResult << std::endl;


	return answeredCorrectly;
}
