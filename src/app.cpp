#include <iostream>
#include <string>
#include "console.h"
#include "set.h"
#include "simpio.h"

using namespace std;

Set<string> generatePermutations(string s);

int main() {
    string str = getLine("Enter a string: ");
    cout << "The permutations of \"" << str << "\" are:" << endl;
    for (string s : generatePermutations(str)) {
        cout << "  \"" << s << "\"" << endl;
    }
    return 0;
}

Set<string> generatePermutations(string s) {
    Set<string> result;
    if (s == "") {
        result += "";
    } else {
        char ch = s[0];
        string rest = s.substr(1);
        for (string sub : generatePermutations(rest)) {
            for (int i = 0; i < sub.length(); i++) {
                result += sub.substr(0, i) + ch + sub.substr(i);
            }
            result += sub + ch;
        }
    }
    return result;
}
