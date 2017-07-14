#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string promptUserForFile(ifstream & infile, string prompt = "");

int main() {
    ifstream infile;
    promptUserForFile(infile, "Input file: ");
    char ch;
    while (infile.get(ch)) {
        cout.put(ch);
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
