#include <cstdlib>
#include "player.h"

#ifndef GAME_H
#define GAME_H

#define PLAYER_1 0
#define PLAYER_2 1

class Game {
	private:
		std::string currStat;
		int yearLowerBound;
		int yearUpperBound;
		int winStreak;
		int correctAnswer;
		int guess;
		Player players[2];

	public:
		Game();

		bool playRound();

		int endGame();

		inline int getWinStreak() {return winStreak;};
		
		inline int getCorrectAnswer() {return correctAnswer;};
		
};

#endif // GAME_H
