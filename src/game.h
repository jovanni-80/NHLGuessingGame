#include <iostream>
#include <cstdlib>

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
		int guess;
		int correctAnswer;

	public:
		Game();

		int playRound();

		int endGame();

		inline int getWinStreak() {return winStreak;};
		
		inline int getCorrectAnswer() {return correctAnswer;};
		
};

#endif // GAME_H
