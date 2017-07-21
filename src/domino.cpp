#include "domino.h"
#include <string>
#include "strlib.h"

Domino::Domino() {
    initDomino(0, 0);
}

Domino::Domino(int left, int right) {
    initDomino(left, right);
}

void Domino::initDomino(int left, int right) {
    leftDot = left; rightDot = right;
}

std::string Domino::toString() {
    return integerToString(leftDot) + "-" + integerToString(rightDot);
}

int Domino::getLeftDots() {
    return leftDot;
}

int Domino::getRightDots() {
    return rightDot;
}

std::ostream& operator<<(std::ostream & os, Domino & domino) {
    return os << domino.toString();
}
