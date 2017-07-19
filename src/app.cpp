#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include "filelib.h"
#include "map.h"
#include "strlib.h"
#include "vector.h"
using namespace std;

void countWords(istream & stream, Map<string, int> & wordCounts);
void displayWordCounts(Map<string, int> & wordCounts);
void extractWords(string line, Vector<string> & words);

int main() {
    ifstream infile;
    Map<string, int> wordCounts;
    promptUserForFile(infile, "Input file: ");
    countWords(infile, wordCounts);
    infile.close();
    displayWordCounts(wordCounts);
    return 0;
}

void countWords(istream &stream, Map<string, int> &wordCounts) {
    Vector<string> lines, words;
    readEntireFile(stream, lines);
    for (string line : lines) {
        extractWords(line, words);
        for (string word : words) {
            wordCounts[toLowerCase(word)]++;
        }
    }
}

void displayWordCounts(Map<string, int> &wordCounts) {
    for (string word : wordCounts) {
        cout << left << setw(15) << word
             << right << setw(5) << wordCounts[word] << endl;
    }
}

void extractWords(string line, Vector<string> &words) {
    words.clear();
    int start = -1;
    for (int i = 0; i < line.length(); i++) {
        if (isalpha(line[i])) {
            if (start == -1) start = i;
        } else {
            if (start >= 0) {
                words.add(line.substr(start, i - start));
                start = -1;
            }
        }
    }

    if (start >= 0) words.add(line.substr(start));
}
