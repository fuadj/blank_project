#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include <string>
#include "vector.h"

using namespace std;

struct Move {
    char src, dest;
    int level;

    Move(){}
    Move(char s, char d, int l): src(s), dest(d), level(l) {}
};

void towersOfHannoi(int n, char source, char dest, char temp, Vector<Move> & moves);

ostream& printTower(const Vector<int> & tower, const string & delim) {
    for (int l : tower) cout << l << delim;
    return cout;
}

const int TOWER_HEIGHT = 8;

int main() {
    char SOURCE = 'A';
    char DEST = 'B';
    char TEMP = 'C';

    Vector<Move> moves;
    Vector<int> destTower;

    towersOfHannoi(TOWER_HEIGHT, SOURCE, DEST, TEMP, moves);

    for (Move move : moves) {
        if (move.dest == DEST) {
            destTower.push_back(move.level);

            printTower(destTower, "  ") << endl;
        } else if (move.src == DEST) {
            destTower.remove(destTower.size() - 1);

            printTower(destTower, "  ") << (destTower.isEmpty() ? "||" : "<=") << endl;
        }
    }

    return 0;
}

void towersOfHannoi(int n, char source, char dest, char temp, Vector<Move> & moves) {
    if (n == 1) {
        moves.push_back(Move{source, dest, n});
    } else {
        towersOfHannoi(n-1, source, temp, dest, moves);
        moves.push_back(Move{source, dest, n});
        towersOfHannoi(n-1, temp, dest, source, moves);
    }
}
