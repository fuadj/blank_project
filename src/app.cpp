#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <sstream>
#include <iomanip>
#include "vector.h"
#include "queue.h"
#include "random.h"
#include "simpio.h"
#include "grid.h"
#include "map.h"
using namespace std;

string convertToMorse(const string & line);
string translateMorse(const string & line);

Map<char, string> alphaToMorse();
Map<string, char> morseToAlpha();

const Map<char, string> ALPHA_TO_MORSE = alphaToMorse();
const Map<string, char> MORSE_TO_ALPHA = morseToAlpha();

int main() {
    cout << "Morse code translator" << endl;

    while (true) {
        string line;
        cout << "> ";
        getline(cin, line);
        if (line == "") break;
        if (isalpha(line[0])) {
            cout << convertToMorse(line) << endl;
        } else {
            cout << translateMorse(line) << endl;
        }
    }
    return 0;
}

string convertToMorse(const string &line) {
    ostringstream out;
    for (char ch : line) {
        out << " " << ALPHA_TO_MORSE[toupper(ch)];
    }
    return out.str();
}

string translateMorse(const string &line) {
    ostringstream out;
    int start = 0;
    for (int i = 1; i <= line.size(); i++) {
        if (i > start &&
                !MORSE_TO_ALPHA.containsKey(line.substr(start, i - start))) {		// we could also add && MORSE_TO_ALPHA.containsKey(sub_str_1)
            out << MORSE_TO_ALPHA[line.substr(start, i - (start + 1))];
            start = i;
        }
    }

    if (start < line.size())
        out << MORSE_TO_ALPHA[line.substr(start)];

    return out.str();
}

Map<char, string> alphaToMorse() {
    Map<char, string> map;
    map['A'] = ".-";
    map['B'] = "-...";
    map['C'] = "-.-.";
    map['D'] = "-..";
    map['E'] = ".";
    map['F'] = "..-.";
    map['G'] = "--.";

    map['H'] = "....";
    map['I'] = "..";
    map['J'] = ".---";
    map['K'] = "-.-";
    map['L'] = ".-..";
    map['M'] = "--";
    map['N'] = "-.";

    map['O'] = "---";
    map['P'] = ".--.";
    map['Q'] = "--.-";
    map['R'] = ".-.";
    map['S'] = "...";
    map['T'] = "-";
    map['U'] = "..-";

    map['V'] = "...-";
    map['W'] = ".--";
    map['X'] = "-..-";
    map['Y'] = "-.--";
    map['Z'] = "--..";
    map[' '] = " ";
    return map;
}

Map<string, char> morseToAlpha() {
    Map<string, char> morse_to_alpha;
    Map<char, string> alpha_to_morse = alphaToMorse();

    for (char ch : alpha_to_morse.keys()) {
        morse_to_alpha[alpha_to_morse[ch]] = ch;
    }

    return morse_to_alpha;
}
