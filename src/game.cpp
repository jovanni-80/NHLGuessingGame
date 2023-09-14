#include "game.h"
#include <cstdlib>

using json = nlohmann::json;

// PRIVATE FUNCTIONS
// choose a random team ID from the file
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
    while (std::getline(teamFile, line) && lineNumber < randLine - 1) {
      lineNumber++;
    }

    teamFile.close();

    // separate the team name and ID
    std::size_t commaSep = line.find(',');
    std::string teamName = line.substr(0, commaSep);
    teamID = std::stoi(line.substr(commaSep + 1));

    cpr::Response r = cpr::Get(cpr::Url{
        "https://statsapi.web.nhl.com/api/v1/teams/" + std::to_string(teamID)});

    if (r.status_code == 200) {
      json jsonResponse = json::parse(r.text);

      if (jsonResponse["teams"][0].contains("firstYearOfPlay")) {
        yearLowerBound = std::max(
            std::stoi(std::string(jsonResponse["teams"][0]["firstYearOfPlay"])),
            yearLowerBound);
      }

    } else {
      std::cerr << "Error [" << r.status_code
                << "] making request in getRandTeamID()" << std::endl;
    }
  } else {
    std::cerr << "OpenFileError" << std::endl;
  }

  /// return team id
  return teamID;
}

// get random player ID from the API roster
int Game::getRandPlayerID(int teamID) {
  // return player ID
  int playerID = -1;

  // create a vector with years from yearlower to year upper bound;
  std::vector<int> validTeamYears;
  for (int i = yearLowerBound; i < yearUpperBound; i++) {
    validTeamYears.push_back(i);
  }

  // fisher yates swap to ensure no invalid years are tried more than once when making the requests
  int vSize = validTeamYears.size();
  for (int i = 0; i < vSize; i++) {
    int j = i + rand() % (vSize - i);
    // swap entries
    int temp = validTeamYears[j];
    validTeamYears[j] = validTeamYears[i];
    validTeamYears[i] = validTeamYears[j];
  }

  int validYearIdx = 0;
  cpr::Response r;
  while (r.status_code != 200 && validYearIdx < vSize) {
    int randSeason = validTeamYears[validYearIdx];

    std::string randSeasonStr =
        std::to_string(randSeason).append(std::to_string(randSeason + 1));

    // request team roster from random team
    std::string rosterRequestUrl = "https://statsapi.web.nhl.com/api/v1/teams/" +
                                  std::to_string(teamID) + "/roster";

    std::cout << rosterRequestUrl << "?season=" + randSeasonStr << std::endl;
    r =
        cpr::Get(cpr::Url{rosterRequestUrl},
                cpr::Parameters{{"season", randSeasonStr}});

    validYearIdx ++;
  }

  // status code was successful
  if (r.status_code == 200) {
    json jsonResponse = json::parse(r.text);
    // Extract "fullName" from the JSON
    if (jsonResponse.contains("roster") && jsonResponse["roster"].is_array()) {
      bool randPlayerFound = false;

      while (!randPlayerFound) {
        int randPlayerIdx = rand() % jsonResponse["roster"].size();
        if (jsonResponse["roster"][randPlayerIdx]["position"]["code"] != "G") {
          randPlayerFound = true;
          playerID = jsonResponse["roster"][randPlayerIdx]["person"]["id"];
          std::cout
              << jsonResponse["roster"][randPlayerIdx]["person"]["fullName"]
              << std::endl;
        }
      }

    } else {
      std::cerr << "Invalid JSON response format." << std::endl;
      return 1;
    }
  } else {
    std::cerr << "Error [" << r.status_code << "] making request in getRandPlayerID()" << std::endl;
  }

  // roster request format:
  // problem: this can return a goalie, to which a regular player cannot be
  // compared get whole roster randomly select member from whole roster until
  // you don't have a goalie

  return playerID;
}

// return a random stat from available stats to guess
std::string Game::generateRandStat() {
  int randStatIdx = std::rand() % sizeof(statArr) / sizeof(statArr[0]);

  return statArr[randStatIdx];
}

// generate the actual url to perform the request on
std::string Game::generatePlayerUrl(int teamID, int playerID,
                                    std::string statName) {

  std::string playerStatsUrl =
      "https://statsapi.web.nhl.com/api/v1/people/" + std::to_string(playerID);

  return playerStatsUrl;
}

// PUBLIC FUNCTIONS START HERE
// Game initializer
Game::Game() {
  std::srand((unsigned)time(0));
  yearUpperBound = 2022;
  yearLowerBound = 1980;
}

// play one round of the game
bool Game::playRound() {
  // get random teams
  std::string randTeam[2];

  // get random player from random team (from random year) with api
  int firstPlayerID = getRandPlayerID(getRandTeamID());
  int secondPlayerID = getRandPlayerID(getRandTeamID());

  this->currStat = generateRandStat();

  // using random season, get roster of team from that season
  // create player

  // create a random player for now
  int p1stat = std::rand() % 100 + 1;
  int p2stat = std::rand() % 100 + 1;

  Player p1("Player", "1", p1stat);
  Player p2("Player", "2", p2stat);

  // prompt user to enter guess
  std::cout << "Who has more " << currStat << "?\n";
  std::cout << "1) " << p1.getName() << " " << p1.getStat() << std::endl;
  std::cout << "2) " << p2.getName() << " " << p2.getStat() << std::endl;

  // return if their guess is correct or not
  // compare player's stats
  int userAnswer;
  std::cin >> userAnswer;
  bool answeredCorrectly = false;

  answeredCorrectly = userAnswer == 1 ? p1.getStat() > p2.getStat()
                                      : p2.getStat() > p1.getStat();
  std::string outputResult = answeredCorrectly ? "correct!" : "incorrect.";

  std::cout << "You were " << outputResult << std::endl;

  return answeredCorrectly;
}
