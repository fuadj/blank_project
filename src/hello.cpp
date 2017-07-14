#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string promptUserForFile(ifstream & infile, string prompt = "");

int stringToInteger(string s) {
    return atoi(s.c_str());
}

int main() {
    ifstream infile;
    promptUserForFile(infile, "Input file: ");

    int total = 0;
    string line;
    while (getline(infile, line)) {
        total += stringToInteger(line);
    }
    infile.close();
    cout << "The sum is " << total << endl;
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
