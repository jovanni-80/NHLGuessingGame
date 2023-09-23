#include <iostream>
#include <map>

#ifndef PLAYER_H
#define PLAYER_H

const std::string statArr[10] = {
    "goals",       "assists",      "points",         "penaltyMinutes",
    "gamesPlayed", "shots",        "powerPlayGoals", "gameWinningGoals",
    "plusMinus",   "overTimeGoals"};

class Player {
private:
  std::string firstName;
  std::string lastName;
  unsigned int id;
  unsigned int stat;

public:
  Player();
  Player(std::string first, std::string last, int id, std::string stat);
  inline int getStat() { return stat; };
  inline std::string getName() { return (firstName += " ") += lastName; };
};

#endif // PLAYER_H
