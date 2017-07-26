#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "vector.h"
#include "map.h"
#include "lexicon.h"
#include <iomanip>

using namespace std;

void listCompletions(const string & number, int index = 0, string result = "");

Map<int, Vector<char> > KEY_MAPPING;
Lexicon * lexicon;
int countFindingKeyCombinations;
int countFindingWords;

void addMapping(int key, const string & number) {
    for (char ch : number) {
        KEY_MAPPING[key].push_back(ch);
    }
}

int main() {
    lexicon = new Lexicon("EnglishWords.dat");
    countFindingKeyCombinations = 0;
    countFindingWords = 0;

    addMapping(0, " ");
    addMapping(1, " ");
    addMapping(2, "abc");
    addMapping(3, "def");
    addMapping(4, "ghi");
    addMapping(5, "jkl");
    addMapping(6, "mno");
    addMapping(7, "pqrs");
    addMapping(8, "tuv");
    addMapping(9, "wxyz");

    string number = getLine("Enter number to call: ");

    listCompletions(number);

    int totalCall = (countFindingKeyCombinations + countFindingWords);
    cout << "Total # of recursive calls " << totalCall << endl;
    cout << "% of calls finding words " << setprecision(4) << (double(countFindingWords) * 100.0 / totalCall) << "%" << endl;

    delete lexicon;

    return 0;
}

void findCompletions(string str) {
    countFindingWords++;
    if (!lexicon->containsPrefix(str)) return;
    if (lexicon->contains(str))
        cout << str << endl;
    for (char ch = 'a'; ch <= 'z'; ch++) {
        findCompletions(str + ch);
    }
}

void listCompletions(const string & number, int index, string result) {
    countFindingKeyCombinations++;
    if (index == number.length()) {
        findCompletions(result);
        return;
    }
    int index_val = int(number[index] - '0');
    for (int i = 0; i < KEY_MAPPING[index_val].size(); i++) {
        listCompletions(number, index + 1, result + KEY_MAPPING[index_val][i]);
    }
}
