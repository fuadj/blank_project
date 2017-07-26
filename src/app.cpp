#include <iostream>
#include <string>
#include "console.h"
#include "set.h"
#include "simpio.h"
#include "time.h"
#include "stack.h"

using namespace std;

void listPermutations(string str);

int main() {
    string str = getLine("Enter a string: ");
    listPermutations(str);

    return 0;
}

void swapChars(string & str, int i, int k) {
    char temp = str[i];
    str[i] = str[k];
    str[k] = temp;
}

void listPermutationsRecursive(string & str, int index) {
    if (index == (str.size() - 1)) {
        cout << str << endl;
        return;
    }
    for (int i = index; i < str.size(); i++) {
        bool duplicate = false;
        for (int k = i - 1; k >= index; k--) {
            if (str[i] == str[k]) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) continue;

        swapChars(str, i, index);

        listPermutationsRecursive(str, index + 1);

        swapChars(str, i, index);
    }
}

void listPermutations(string str) {
    listPermutationsRecursive(str, 0);
}
