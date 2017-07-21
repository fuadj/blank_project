#ifndef _card_h
#define _card_h

#include <string>
#include <ostream>

enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

Suit operator++(Suit & suit, int);

const int ACE = 1;
const int JACK = 11;
const int QUEEN = 12;
const int KING = 13;

class Card {
public:
    Card();
    Card(const std::string & name);
    Card(int rank, Suit suit);

    std::string toString() const;

    int getRank();
    Suit getSuit();

private:
    int rank;
    Suit suit;
};

std::ostream & operator<<(std::ostream & os, const Card & card);

#endif
