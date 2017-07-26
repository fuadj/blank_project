#include <iostream>
#include <string>
#include "console.h"
#include "vector.h"
#include "simpio.h"
#include "card.h"

using namespace std;

int countFifteens(Vector<Card> & cards);

int main() {
    Vector<Card> cards;
    cards += Card("5C"), Card("5D"), Card("5H"), Card("5S"), Card("JC");
    cout << "Num fifteen " << countFifteens(cards) << endl;
    return 0;
}

int getCardValue(Card & card) {
    int rank = card.getRank();
    if (rank == ACE)
        return 1;
    else if (rank >= JACK)
        return 10;
    else
        return rank;
}

int countFifteensRecursive(Vector<Card> chosenCards, Vector<Card> & cards) {
    if (cards.isEmpty()) {
        int sum = 0;
        for (Card card : chosenCards) {
            sum += getCardValue(card);
        }

        if (sum == 15) {
            for (int i = 0; i < chosenCards.size(); i++) {
                if (i != 0) cout << " + ";
                cout << chosenCards[i].toString();
            }
            cout << endl;
        }
        return sum == 15 ? 1 : 0;
    } else {
        Vector<Card> rest;
        if (cards.size() > 1)	// calling subList(1, n) on Vector of size 1 causes Exception
            rest = cards.subList(1, cards.size() - 1);

        int count = countFifteensRecursive(chosenCards, rest);		// exclude the card
        chosenCards.add(cards[0]);
        count += countFifteensRecursive(chosenCards, rest);		// include it
        return count;
    }
}

int countFifteens(Vector<Card> & cards) {
    Vector<Card> chosenCards;
    return countFifteensRecursive(chosenCards, cards);
}
