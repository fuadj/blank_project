/**
 * This program simulates a simple variant of the game of NIm. In this
 * version, the game starts with a pile of 13 coins on a table. Players
 * then take turns removing 1, 2, or 3 coins from the pile. The player
 * who takes the last coin loses.
 */
#include <iostream>
#include <string>
#include "error.h"
#include "simpio.h"
#include "strlib.h"
#include "console.h"
using namespace std;

const int N_COINS = 13;
const int MAX_MOVE = 3;
const int NO_GOOD_MOVE = -1;

enum Player { HUMAN, COMPUTER };

Player opponent(Player player) {
    return (player == HUMAN) ? COMPUTER : HUMAN;
}

const Player STARTING_PLAYER = HUMAN;

class SimpleNim {
public:
    void play() {
        nCoins = N_COINS;
        whoseTurn = STARTING_PLAYER;
        while (nCoins > 1) {
            cout << "There are " << nCoins << " coins in the pile." << endl;
            if (whoseTurn == HUMAN) {
                nCoins -= getUserMove();
            } else {
                int nTaken = getComputerMove();
                cout << "I'll take " << nTaken << "." << endl;
                nCoins -= nTaken;
            }
            whoseTurn = opponent(whoseTurn);
        }
        announceResult();
    }

    void printInstructions() {
        cout << "Welcome to the game of Nim!" << endl;
        cout << "In this game, we will start with a pile of" << endl;
        cout << N_COINS << " coins on the table. On each turn, you" << endl;
        cout << "and I will alternately taken between 1 and" << endl;
        cout << MAX_MOVE << " coins from the table. The player who" << endl;
        cout << "takes the last coin loses." << endl << endl;
    }

private:
    int getComputerMove() {
        int nTaken = findGoodMove(nCoins);
        return (nTaken == NO_GOOD_MOVE) ? 1 : nTaken;
    }

    int findGoodMove(int nCoins) {
        int limit = (nCoins < MAX_MOVE) ? nCoins : MAX_MOVE;
        for (int nTaken = 1; nTaken <= limit; nTaken++) {
            if (isBadPosition(nCoins - nTaken)) return nTaken;
        }
        return NO_GOOD_MOVE;
    }

    bool isBadPosition(int nCoins) {
        if (nCoins == 1) return true;
        return findGoodMove(nCoins) == NO_GOOD_MOVE;
    }

    int getUserMove() {
        while (true) {
            int nTaken = getInteger("How many would you like? ");
            int limit = (nCoins < MAX_MOVE) ? nCoins : MAX_MOVE;
            if (nTaken > 0 && nTaken <= limit) return nTaken;
            cout << "That's cheating! Please choose a number";
            cout << " between 1 and " << limit << "." << endl;
            cout << "There are " << nCoins << " coins in the pile." << endl;
        }
    }

    void announceResult() {
        if (nCoins == 0) {
            cout << "You took the last coin. You loose." << endl;
        } else {
            cout << "There is only one coin left." << endl;
            if (whoseTurn == HUMAN)
                cout << "I win." << endl;
            else
                cout << "I lose." << endl;
        }
    }

    int nCoins;
    Player whoseTurn;
};

int main() {
    SimpleNim game;
    game.printInstructions();
    game.play();
    return 0;
}
