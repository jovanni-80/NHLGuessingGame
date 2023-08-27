#include "game.h"

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
  } else {
    std::cout << "OpenFileError" << std::endl;
  }

  /// return team id
  return teamID;
}

int Game::getRandPlayerID(int teamID) {
  // return player ID

  // request team roster from random team
  std::string rosterRequestUrl = "https://statsapi.web.nhl.com/api/v1/teams/" +
                                 std::to_string(teamID) + "/roster";

  cpr::Response r =
      cpr::Get(cpr::Url{rosterRequestUrl},
               cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
               cpr::Parameters{{"anon", "true"}, {"key", "value"}});

  // status code was successful
  if (r.status_code == 200) {
    json jsonResponse = json::parse(r.text);
    // Extract "fullName" from the JSON
    if (jsonResponse.contains("roster") && jsonResponse["roster"].is_array()) {
      for (const json &player : jsonResponse["roster"]) {
        if (player.contains("person") &&
            player["person"].contains("fullName")) {
          std::string fullName = player["person"]["fullName"];
          int id = player["person"]["id"];
          std::cout << "Player Full Name: " << fullName << " : " << id
                    << std::endl;
        }
      }
    } else {
      std::cerr << "Invalid JSON response format." << std::endl;
      return 1;
    }
  } else {
    std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
  }

  // roster request format:
  // problem: this can return a goalie, to which a regular player cannot be
  // compared get whole roster randomly select member from whole roster until
  // you don't have a goalie

  return 0;
}

// return a random stat from available stats to guess
std::string Game::generateRandStat() {
  int randStatIdx = std::rand() % sizeof(statArr) / sizeof(statArr[0]);

  return statArr[randStatIdx];
}

// generate the actual API request used to get the player name and stats
std::string Game::generateAPIRequest(int teamID, int playerID,
                                     std::string statName) {
  int randSeason =
      (std::rand() % (yearUpperBound - yearLowerBound + 1)) + yearLowerBound;
  std::string randSeasons =
      std::to_string(randSeason).append(std::to_string(randSeason + 1));

  return "";
}

// PUBLIC FUNCTIONS START HERE
// Game initializer
Game::Game() {
  std::srand((unsigned)time(0));
  yearUpperBound = 2023;
  yearLowerBound = 1980;
}

// play one round of the game
bool Game::playRound() {
  // get random teams
  std::string randTeam[2];

  // get team and stat first
  getRandPlayerID(getRandTeamID());
  currStat = generateRandStat();

  // get random seasons to choose roster random season should be in range of
  // team and bounds
  std::string randSeasons[2];
  int randSeason1 =
      (std::rand() % (yearUpperBound - yearLowerBound + 1)) + yearLowerBound;
  int randSeason2 =
      (std::rand() % (yearUpperBound - yearLowerBound + 1)) + yearLowerBound;

  randSeasons[PLAYER_1] =
      std::to_string(randSeason1).append(std::to_string(randSeason1 + 1));
  randSeasons[PLAYER_2] =
      std::to_string(randSeason1).append(std::to_string(randSeason2 + 1));

  // using random season, get roster of team from that season
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

  answeredCorrectly = userAnswer == 1 ? p1.getStat() > p2.getStat()
                                      : p2.getStat() > p1.getStat();
  std::string outputResult = answeredCorrectly ? "correct!" : "incorrect.";

  std::cout << "You were " << outputResult << std::endl;

  return answeredCorrectly;
}
