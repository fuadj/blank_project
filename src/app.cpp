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
        for (int i = 0; i < s.length(); i++) {
            char ch = s[0];
            string rest = s.substr(0, i) + s.substr(i + 1);
            for (string sub : generatePermutations(rest)) {
                result += ch + sub;
            }
        }
    }
    return result;
}
