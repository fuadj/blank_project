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

void readVector(istream & in, Vector<double> & vec);
// you get the point, won't implement the rest
void readVector(istream & in, Vector<int> & vec);
void readVector(istream & in, Vector<string> & vec);

void printVec(Vector<double> & vec);

int main() {
    ifstream infile;
    Vector<double> roots;
    promptUserForFile(infile, "Input file: ");

    for (int i = 1; i <= 3; i++) {
        cout << "Print -------- " << i << endl;
        readVector(infile, roots);
        printVec(roots);
    }

    infile.close();
    return 0;
}

void printVec(Vector<double> & vec) {
    for (double d : vec) {
        cout << d << endl;
    }
}

void readVector(istream & in, Vector<double> & vec) {
    string line;
    double val;

    if (in.peek() == EOF) vec.clear();

    while (getline(in, line)) {
        if (line == "") break;

        std::istringstream stream(line);
        stream >> val;
        if (!stream.fail())
            vec.push_back(val);
    }
}
