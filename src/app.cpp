#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "random.h"

using namespace std;

string promptUserForFile(ifstream & infile, string prompt = "");

string scrambleLine1(string & line);
string scrambleLine2(string & line);

int main() {
    ifstream infile;
    promptUserForFile(infile, "Input file: ");

    //setRandomSeed(time(NULL));
    setRandomSeed(0);
    string line;
    while (getline(infile, line)) {
        cout << scrambleLine2(line) << endl;
    }
    infile.close();
    return 0;
}

string promptUserForFile(ifstream & infile, string prompt) {
    while (true) {
        cout << prompt;
        string filename;
        getline(cin, filename);
        infile.open(filename.c_str());
        if (!infile.fail())
            return filename;
        infile.clear();
        cout << "Unable to open that file. Try again. " << endl;
        if (prompt == "")
            prompt = "Input file: ";
    }
}

string UPPER_CASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string LOWER_CASE = "abcdefghijklmnopqrstuvwxyz";
int ALPHABET_SIZE = UPPER_CASE.size();

string scrambleLine1(string &line) {
    ostringstream result;
    istringstream lineStream(line);

    int ch;
    while ((ch = lineStream.get()) != EOF)  {
        if (!isalpha(ch)) {
            result << (char)ch;
            continue;
        }

        int rand_index = randomInteger(0, ALPHABET_SIZE);
        char replacement;
        if (isupper(ch)) {
            replacement = UPPER_CASE[rand_index];
        } else {
            replacement = LOWER_CASE[rand_index];
        }
        result << replacement;
    }

    return result.str();
}

string scrambleLine2(string &line) {
    string result;
    for (int i = 0; i < line.size(); i++) {
        char ch = line[i];
        if (!isalpha(ch)) {
            result += ch;
            continue;
        }

        int rand_index = randomInteger(0, ALPHABET_SIZE);
        char replacement;
        if (isupper(ch)) {
            replacement = UPPER_CASE[rand_index];
        } else {
            replacement = LOWER_CASE[rand_index];
        }
        result += replacement;
    }
    return result;
}
