#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>
#include "filelib.h"
#include "vector.h"

using namespace std;

static const int COLUMNS = 7;

int main() {
    Vector<int> letterCounts(26);
    ifstream infile;
    promptUserForFile(infile, "Input file: ");
    char ch;
    while (infile.get(ch)) {
        if (isalpha(ch)) {
            letterCounts[toupper(ch) - 'A']++;
        }
    }
    infile.close();
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        cout << setw(COLUMNS) << letterCounts[ch - 'A'] << " " << ch << endl;
    }
    return 0;
}
