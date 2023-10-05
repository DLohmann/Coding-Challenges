#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>

using namespace std;


/*********************************************************
 * PLEASE READ:
 * 1) The most important thing is to get a compiled and working solution to each problem, as fast as possible.
 * 2) You may take time-saving shortcuts - but try to verbally indicate the "proper" way to do it
 * 3) You may use any existing language features, libraries, etc.
 * 4) You are not expected to have to read or understand every line this code, only what's necessary
 * 5) You may ask for help with anything - syntax, available library methods, where in the code X happens, etc.
 **********************************************************/


/**
 * The three moves you can throw in Rock, Paper, Scissors.
 * Rock beats scissors.
 * Scissors beats paper.
 * Paper beats rock.
 */
enum RPSMove {
    ROCK,
    SCISSORS,
    PAPER
};

/**
 * Return true iff move A beats move B.
 */
static bool handIsBetter(RPSMove a, RPSMove b) {
    return ((a+1)%3) == b;
}


/**
 * A bot interface for playing Rock, Paper, Scissors.
 */
class Bot {
public:
    virtual ~Bot() {}

    /**
     * An identifier for what type of bot this is.
     */
    virtual string name() const = 0;

    /**
     * Returns this bot's next throw against the current opponent.
     */
    virtual RPSMove makeMove() = 0;

    /**
     * Invoked prior to a series of games with a new opponent.
     */
    virtual void onNewOpponent() {}

    /**
     * Invoked after each hand against an opponent, indicating what move the opponent made.
     */
    virtual void onHandPlayed(RPSMove opponentsMove) {}
};


/**
 * Class for receiving information about what happens during the tournament.
 */
class TournamentObserver {
public:
    virtual ~TournamentObserver() {}

    /**
     * Invoked after a match is played between two bots.
     */
    virtual void onMatchPlayed(const Bot& botA, const Bot& botB, int winsA, int winsB, int ties) = 0;
};

/**
 * Runs a rock paper scissors tournament between a set of bots.
 */
class Tournament {
public:
    Tournament(vector<Bot*> bots)
        : _bots(std::move(bots)) {
    }

    /**
     * Adds an observer to be notified when events happen in the tournament.
     */
    void addObserver(TournamentObserver* observer) {
        _observers.push_back(observer);
    }
    void clearObservers() {
        _observers.clear();
    }

    /**
     * Plays through the tournament, having each bot play against the others in a round-robin format.
     */
    void playTournament() {
        // Go through each unique pair of bots.
        for (size_t i = 0; i < _bots.size(); ++i) {
            for (size_t j = i + 1; j < _bots.size(); ++j) {

                // Play a match
                int winsA, winsB, ties;
                tie(winsA, winsB, ties) = playMatch(*_bots[i], *_bots[j]);

                // Send the results to any observers.
                for (auto* observer : _observers) {
                    observer->onMatchPlayed(*_bots[i], *_bots[j], winsA, winsB, ties);
                }
            }
        }
    }

    int gamesPerMatch = 1000;
private:
    /**
     * Plays a series of games between these two bots, returning how many times each bot won.
     */
    tuple<int, int, int> playMatch(Bot& playerA, Bot& playerB) {
        int winsA = 0;
        int winsB = 0;
        int ties = 0;
        playerA.onNewOpponent();
        playerB.onNewOpponent();

        for (int i = 0; i < gamesPerMatch; ++i) {
            RPSMove moveA = playerA.makeMove();
            RPSMove moveB = playerB.makeMove();
            if (handIsBetter(moveA, moveB)) {
                winsA++;
            } else if (handIsBetter(moveB, moveA)) {
                winsB++;
            } else {
                ties++;
            }

            playerA.onHandPlayed(moveB);
            playerB.onHandPlayed(moveA);
        }

        return make_tuple(winsA, winsB, ties);
    }

    vector<Bot*> _bots;
    vector<TournamentObserver*> _observers;
};

/**
 * Stores and displays the outcome of a tournament - who won, and what happened.
 */
class TournamentResults : public TournamentObserver {
public:

    /**
     * Adds the results of a set of games between two bots to these results.
     * winsA is the number of times botA beat botB.
     * winsB is the number of times botB beat botA.
     */
    void onMatchPlayed(const Bot& botA, const Bot& botB, int winsA, int winsB, int ties) override {
        // printf("onMatchPlayed %20s vs %20s\twith %7d,\twinsA %7d,\twinsB %7d,\tties.\n", botA.name().c_str(), botB.name().c_str(), winsA, winsB, ties);

        _botWins[botA.name()] += winsA;
        _botLosses[botA.name()] += winsB;

        _botWins[botB.name()] += winsB;
        _botLosses[botB.name()] += winsA;

        _botTies[botA.name()] += ties;
        _botTies[botB.name()] += ties;

    }

    /**
     * Prints a summary of the tournament results to the console.
     */
    void printToConsole() {
        printf("%20s | %7s | %7s | %7s | %4s\n", "Name", "Wins", "Losses", "Ties", "Overall");
        printf("--------------------------------------------------------------\n");
        int total_games = 0;
        for (const auto& entry : _botWins) {
            auto botName = entry.first;

            printf("%20s | %7d | %7d | %7d | %4d\n", botName.c_str(), _botWins[botName], _botLosses[botName], _botTies[botName], _botWins[botName] - _botLosses[botName]);
            total_games += _botWins[botName] + _botLosses[botName] + _botTies[botName];
        }
        total_games /= 2;
        printf("Total games: %d\n\n", total_games);
    }

private:
    // Stores total wins across the tournament for each bot, by name.
    map<string, int> _botWins;

    // Stores total losses across the tournament for each bot, by name.
    map<string, int> _botLosses;

    map<string, int> _botTies;
};

/**
 * A bot that randomly chooses what to play each hand.
 */
class RandomBot : public Bot {
public:
    string name() const override {
        return "RandomBot";
    }
    RPSMove makeMove() override {
        return (RPSMove)(rand() % 3);
    }
};


/**
 * A bot that always picks the same move every hand.
 */
class OneMoveBot : public Bot {
public:
    OneMoveBot(RPSMove move) : _move(move) {
    }

    string name() const override {
        return "OneMoveBot";
    }

    RPSMove makeMove() override {
        return _move;
    }

private:
    RPSMove _move;
};


/**
 * A bot that tracks which hand their opponent has played the most, and plays
 * the hand that will beat that.
 *
 * e.g. if their opponent has played more rock than anything else, it will play paper.
 */
class BasicStatsBot : public Bot {
public:
    string name() const override {
        return "BasicStatsBot";
    }

    RPSMove makeMove() override {
        // Find the most played move.
        RPSMove mostPlayedMove = ROCK;
        int mostPlayedMoveCount = 0;
        for (const auto& cnt : _playedCounts) {
            if (cnt.second > mostPlayedMoveCount) {
                mostPlayedMove = cnt.first;
                mostPlayedMoveCount = cnt.second;
            }
        }

        // Find the counter to the most played move.
        for (int i = 0; i < 3; ++i) {
            if (handIsBetter((RPSMove)i, mostPlayedMove)) {
                // Found the counter, return it.
                return (RPSMove)i;
            }
        }

        throw "This should be impossible!";
    }

    void onNewOpponent() override {
        _playedCounts.clear();
    }

    void onHandPlayed(RPSMove opponentsMove) override {
        _playedCounts[opponentsMove]++;
    }

private:
    map<RPSMove, int> _playedCounts;
};

int main() {
    // Initialize our list of bots.
    RandomBot randomBot;
    OneMoveBot scissorsBot(SCISSORS);
    BasicStatsBot basicStatsBot;

    // Setup our tournament.
    Tournament tourny({&randomBot, &scissorsBot, &basicStatsBot});


    vector<int> repititions = {1000, 100, 10};
    for (int rep : repititions) {
      // Keep track of results.
      printf("\n\nUsing %d repetitions:\n", rep);
      TournamentResults results;
      tourny.addObserver(&results);

      tourny.gamesPerMatch = rep;
      // Play the tournament.
      tourny.playTournament();

      // Print out the results.
      results.printToConsole();

      tourny.clearObservers();
    }
}

/*

  | 1  2  3
  ----------
1 |   10  10
2 |       10
3 |


*/
