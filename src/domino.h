#ifndef _domino_h
#define _domino_h

#include <ostream>

class Domino {
public:
    Domino();
    Domino(int left, int right);

    std::string toString();

    int getLeftDots();
    int getRightDots();

private:
    int leftDot, rightDot;

    void initDomino(int left, int right);
};

std::ostream & operator<<(std::ostream & os, Domino & domino);

#endif
