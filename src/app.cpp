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
#include "error.h"
using namespace std;

void readVector(istream & in, Vector<int> & vec);

void countRanges(Vector<int> & numbers, Vector<int> & ranges);
void printHistogram(Vector<int> & vec);

const int NUM_RANGES = 11;
int main() {
    ifstream infile;
    Vector<int> ints;
    Vector<int> ranges(NUM_RANGES);

    promptUserForFile(infile, "Input file: ");

    readVector(infile, ints);

    countRanges(ints, ranges);
    printHistogram(ranges);

    infile.close();
    return 0;
}

void printVec(Vector<double> & vec) {
    for (double d : vec) {
        cout << d << endl;
    }
}

void countRanges(Vector<int> & numbers, Vector<int> & ranges) {
    if (ranges.size() != NUM_RANGES)
        error("Program only works for the range [0-100]");

    for (int i = 0; i < numbers.size(); i++) {
        int bucket = (numbers[i] / 10);		// we want integer division here, we don't want reminder

        if (bucket >= NUM_RANGES)
            bucket = NUM_RANGES - 1;
        else if (bucket < 0)
            bucket = 0;

        ranges[bucket]++;
    }
}

void printHistogram(Vector<int> &ranges) {
    for (int i = 0; i < NUM_RANGES; i++) {
        if (i == 10)
            cout << "100: ";
        else if (i == 0)
            cout << "00s: ";
        else
            cout << i * 10 << "s: ";

        for (int j = 0; j < ranges[i]; j++)
            cout << "*";
        cout << endl;
    }
}

void readVector(istream & in, Vector<int> & vec) {
    string line;
    int val;

    while (getline(in, line)) {
        std::istringstream stream(line);
        stream >> val;
        if (!stream.fail())
            vec.push_back(val);
    }
}
