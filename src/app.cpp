#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "random.h"
#include "filelib.h"

using namespace std;

void removeLetters(istream &is, ostream &os, string letters);

int main() {
    ifstream infile;
    ofstream outfile;
    string banished_letters;

    promptUserForFile(infile, "Input file: ");
    //promptUserForFile(outfile, "Output file: ");

    cout << "Letters to banish: ";
    getline(cin, banished_letters);

    for (int i = 0; i < banished_letters.size(); i++) {
        banished_letters[i] = tolower(banished_letters[i]);
    }
    //removeLetters(infile, outfile, banished_letters);
    removeLetters(infile, cout, banished_letters);

    infile.close();
    outfile.close();

    return 0;
}

void removeLetters(istream &is, ostream &os, string letters) {
    int ch;
    while ((ch = is.get()) != EOF) {
        bool skip_letter = false;
        int lower_ch = tolower(ch);
        for (int i = 0; i < letters.size(); i++) {
            if ((char)lower_ch == letters[i]) {
                skip_letter = true;
                break;
            }
        }
        if (!skip_letter) {
            os.put((char)ch);
        }
    }
}
