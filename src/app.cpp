#include <iostream>
#include <string>
#include "console.h"
#include "vector.h"
#include "lexicon.h"
#include "simpio.h"

using namespace std;

void embeddedWords(string sofar, string letters, const Lexicon & lexicon);

int main() {
    Lexicon lexicon("EnglishWords.dat");
    string word;

    word = getLine("Enter starting word: ");
    cout << "The embedded words are:" << endl;
    embeddedWords("", word, lexicon);
    return 0;
}


void embeddedWords(string sofar, string letters, const Lexicon & lexicon) {
    if (letters.size() == 0 &&
            lexicon.contains(sofar)) {
        cout << sofar << endl;
    }
    if (letters.size() > 0) {
        string rest = letters.substr(1);
        embeddedWords(sofar, rest, lexicon);
        embeddedWords(sofar + letters[0], rest, lexicon);
    }
}
