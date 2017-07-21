#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <sstream>
#include <iomanip>
#include "lexicon.h"
#include "strlib.h"
#include "vector.h"
#include "math.h"
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

    int max_len = 0;
    Vector<int> wordLen;
    wordLen.add(0);		// add a dummy place holder for the 0-th position
    for (string s : lexicon) {
        while (s.length() >= wordLen.size())
            wordLen.add(0);
        wordLen[s.length()]++;
        if (max_len < wordLen[s.length()])
            max_len = wordLen[s.length()];
    }

    int w_index = int(log10(wordLen.size() - 1)) + 1;
    int w_len = int(log10(max_len)) + 1;
    for (int i = 1; i < wordLen.size(); i++)
        if (wordLen[i] != 0)
            cout << right << setw(w_index) << i << "   " << setw(w_len) << wordLen[i] << endl;

    return 0;
}
