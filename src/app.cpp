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
#include "hist.h"
using namespace std;

void readVector(istream & in, Vector<int> & vec);

int main() {
    ifstream infile;
    Vector<int> numbers;

    promptUserForFile(infile, "Input file: ");

    readVector(infile, numbers);

    printHistogram(numbers);

    infile.close();
    return 0;
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
