#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <sstream>
#include <iomanip>
#include "lexicon.h"
#include "strlib.h"
using namespace std;

bool isPalindrome(const string & s) {
    for (int i = 0; i < s.size()/2; i++) {
        if (s[i] != s[s.size() - (i+1)])
            return false;
    }
    return true;
}

int main() {
    Lexicon lexicon("EnglishWords.dat");
    for (string s : lexicon) {
        if (isPalindrome(s)) {
            cout << s << endl;
        }
    }
    return 0;
}
