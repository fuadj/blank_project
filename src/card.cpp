#include "card.h"
#include "strlib.h"
#include "map.h"

Map<Suit, char> suitToChar();
Map<char, Suit> charToSuit();

Map<int, std::string> rankToStr();
Map<std::string, int> strToRank();

const Map<Suit, char> SUIT_TO_CHAR = suitToChar();
const Map<char, Suit> CHAR_TO_SUIT = charToSuit();

const Map<int, std::string> RANK_TO_STR = rankToStr();
const Map<std::string, int> STR_TO_RANK = strToRank();

Card::Card() {

}

Card::Card(const std::string &s) {
    std::string name = toUpperCase(s);
    if (name.length() < 2)
        return;

    char ch_suit;
    if (name.length() == 2) {
        ch_suit = name[1];
        if (isdigit(name[0])) {
            rank = (name[0] - '0');
        } else if (STR_TO_RANK.containsKey("" + name[0])) {
            rank = STR_TO_RANK["" + name[0]];
        }
    } else if (name.length() == 3) {
        rank = 10;
        ch_suit = name[2];
    }

    if (CHAR_TO_SUIT.containsKey(ch_suit))
        suit = CHAR_TO_SUIT.get(ch_suit);
}

Card::Card(int rank, Suit suit) {
    this->suit = suit;
    this->rank = rank;
}

std::string Card::toString() const {
    std::ostringstream out;
    out << RANK_TO_STR[rank] << SUIT_TO_CHAR[suit];
    return out.str();
}

int Card::getRank() {
    return rank;
}

Suit Card::getSuit() {
    return suit;
}

std::ostream & operator<<(std::ostream & os, const Card & card) {
    return os << card.toString();
}

Map<Suit, char> suitToChar() {
    Map<Suit, char> map;
    map[CLUBS] = 'C';
    map[DIAMONDS] = 'D';
    map[HEARTS] = 'H';
    map[SPADES] = 'S';
    return map;
}

Map<char, Suit> charToSuit() {
    Map<Suit, char> suit_2_char = suitToChar();
    Map<char, Suit> char_2_suit;

    for (Suit s : suit_2_char) {
        char_2_suit[suit_2_char[s]] = s;
    }

    return char_2_suit;
}

Map<int, std::string> rankToStr() {
    Map<int, std::string> map;
    map[ACE] = "A";
    map[JACK] = "J";
    map[QUEEN] = "Q";
    map[KING] = "K";

    map[2] = "2";
    map[3] = "3";
    map[4] = "4";
    map[5] = "5";
    map[6] = "6";
    map[7] = "7";
    map[8] = "8";
    map[9] = "9";
    map[10] = "10";

    return map;
}

Map<std::string, int> strToRank() {
    Map<int, std::string> rank_2_str = rankToStr();
    Map<std::string, int> str_2_rank;

    for (int r : rank_2_str) {
        str_2_rank[rank_2_str[r]] = r;
    }

    return str_2_rank;
}

Suit operator++(Suit & suit, int) {
    Suit old = suit;
    suit = Suit(suit + 1);
    return old;
}
