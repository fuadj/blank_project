#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include <string>
#include "set.h"
#include "simpio.h"

using namespace std;

Set<string> generatePermutations(const string & s);
Set<string> generatePermutationsBook(string s);

int main() {
    string str = getLine("Enter a string: ");
    cout << "The permutations of \"" << str << "\" are:" << endl;
    for (string s : generatePermutationsBook(str)) {
        cout << "   \"" << s << "\"" << endl;
    }

    return 0;
}

void generatePermutationsRecursive(const string & sofar, const Set<char> & chars, Set<string> & permutations) {
    if (chars.isEmpty()) {
        permutations.add(sofar);
    } else {
        for (char ch : chars) {
            generatePermutationsRecursive(sofar + ch, chars - ch, permutations);
        }
    }
}

Set<string> generatePermutations(const string & s) {
    Set<char> chars;
    Set<string> permutations;
    for (char ch : s) {
        chars.add(ch);
    }
    generatePermutationsRecursive("", chars, permutations);
    return permutations;
}

Set<string> generatePermutationsBook(string str) {
    Set<string> result;
    if (str == "") {
        result += "";
    } else {
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];
            string rest = str.substr(0, i) + str.substr(i+1);
            for (string s : generatePermutationsBook(rest)) {
                result += ch + s;
            }
        }
    }

    return result;
}
