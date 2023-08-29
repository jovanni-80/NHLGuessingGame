#include "player.h"
#include <cpr/cpr.h>
#include <cstdlib>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

#ifndef GAME_H
#define GAME_H

#define PLAYER_1 0
#define PLAYER_2 1

#define TEAM_FILE_PATH "/home/jovanni/Projects/NHLGuessingGame/src/teamIDs.txt"

class Game {
private:
  // helper functions
  int getRandTeamID();
  int getRandPlayerID(int teamID);
  std::string generateRandStat();
  std::string generatePlayerUrl(int teamID, int playerID, std::string statName);

  // member vars
  std::string currStat;
  int yearLowerBound, yearUpperBound, winStreak, correctAnswer, guess;
  Player players[2];

public:
  Game();

  bool playRound();

  int endGame();

  inline int getWinStreak() { return winStreak; };

  inline int getCorrectAnswer() { return correctAnswer; };
};

#endif // GAME_H
