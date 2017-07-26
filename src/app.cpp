#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "vector.h"
#include "map.h"

using namespace std;

void listMnemonics(const string & number, int index = 0, string result = "");

Map<int, Vector<char> > KEY_MAPPING;

void addMapping(int key, const string & number) {
    for (char ch : number) {
        KEY_MAPPING[key].push_back(ch);
    }
}

int main() {
    addMapping(0, " ");
    addMapping(1, " ");
    addMapping(2, "ABC");
    addMapping(3, "DEF");
    addMapping(4, "GHI");
    addMapping(5, "JKL");
    addMapping(6, "MNO");
    addMapping(7, "PQRS");
    addMapping(8, "TUV");
    addMapping(9, "WXYZ");

    string number = getLine("Enter number to call: ");

    listMnemonics(number);

    return 0;
}

void listMnemonics(const string & number, int index, string result) {
    if (index == number.length()) {
        cout << result << endl;
        return;
    }
    int index_val = int(number[index] - '0');
    for (int i = 0; i < KEY_MAPPING[index_val].size(); i++) {
        listMnemonics(number, index + 1, result + KEY_MAPPING[index_val][i]);
    }
}
