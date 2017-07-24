#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include "stack.h"

using namespace std;

struct Move {
    int numPlates;
    char source, dest, temp;

    Move(){}
    Move(int n, char s, char d, char t): numPlates(n), source(s), dest(d), temp(t) {}
};

void moveTowersOfHanoiWithStack(int n, char source, char dest, char temp);

int main() {
    moveTowersOfHanoiWithStack(3, 'A', 'B', 'C');
    return 0;
}

void moveTowersOfHanoiWithStack(int n, char source, char dest, char temp) {
    Stack<Move> moves;

    moves.push(Move(n, source, dest, temp));
    while (!moves.isEmpty()) {
        Move move = moves.pop();
        if (move.numPlates == 1)
            cout << move.source << " => " << move.dest << endl;
        else if (move.numPlates > 1) {
            moves.push(Move(move.numPlates - 1,
                            move.temp, move.dest, move.source));
            moves.push(Move(1,
                            move.source, move.dest, move.temp));	// move the last plate
            moves.push(Move(move.numPlates - 1,
                            move.source, move.temp, move.dest));
        }
    }
}
