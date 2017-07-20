#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iomanip>
#include <iostream>
#include <string>
#include "strlib.h"
using namespace std;

bool checkParenthesis(string & line);

int main() {
    string line_a = "{ s = 2 * (a[2] + 3); x = (1 + (2)); }";
    string line_incorrect_1 = "(([])";
    string line_incorrect_2 = ")(";
    string line_incorrect_3 = "{(})";

    cout << right << setw(5) << boolToString(checkParenthesis(line_a)) << " " << line_a << endl;;
    cout << right << setw(5) << boolToString(checkParenthesis(line_incorrect_1)) << " " << line_incorrect_1 << endl;;
    cout << right << setw(5) << boolToString(checkParenthesis(line_incorrect_2)) << " " << line_incorrect_2 << endl;;
    cout << right << setw(5) << boolToString(checkParenthesis(line_incorrect_3)) << " " << line_incorrect_3 << endl;;

    return 0;
}

bool checkParenthesis(string & line) {
    int parenthesis = 0, curly = 0, bracket = 0;
    for (int i = 0; i < line.size(); i++) {
        char ch = line[i];
        if (ch == '{') {
            curly++;
        } else if (ch == '}') {
            if (bracket != 0 || parenthesis != 0)
                return false;
            if (curly-- == 0) return false;
        } else if (ch == '(') {
            parenthesis++;
        } else if (ch == ')') {
            if (bracket != 0)
                return false;
            if (parenthesis-- == 0) return false;
        } else if (ch == '[') {
            bracket++;
        } else if (ch == ']') {
            if (bracket-- == 0) return false;
        }
    }

    return (parenthesis == 0) && (curly == 0) && (bracket == 0);
}
