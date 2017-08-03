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
#include "random.h"
#include <iomanip>
#include <cmath>
using namespace std;

const int N_COINS = 23;
const int MAX_MOVE = 7;
const int NO_GOOD_MOVE = -1;

const double LUCK_FACTOR = 0.4;

enum Player { HUMAN, COMPUTER };

Player opponent(Player player) {
    return (player == HUMAN) ? COMPUTER : HUMAN;
}

string playerTurn(int turnCount) {
    if ((turnCount % 2) == 0)
        return "[A]";
    return "[B]";
}

class SimpleNim {
public:
    void play() {
        int turn = 0;
        nCoins = N_COINS;
        int width = int(log10(N_COINS)) + 1;
        while (nCoins > 1) {
            cout << playerTurn(turn) << " ";
            cout << "There are " << setw(width) << nCoins << " coins in the pile";
            int nTaken = getComputerMove();
            cout << " Takes " << nTaken << "." << endl;
            nCoins -= nTaken;
            turn++;
        }

        if (nCoins == 0) {
            cout << "No coin left ";
        } else {
            cout << "1 coin left ";
        }
        cout << playerTurn(turn) << " looses." << endl;
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
        return randomChance(LUCK_FACTOR) ?
                    (findGoodMove(nCoins) == NO_GOOD_MOVE) :
                    false;
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
