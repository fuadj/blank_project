#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include <iomanip>
#include "domino.h"

using namespace std;

int main() {
    for (int left = 1; left <= 6; left++) {
        for (int right = 1; right <= 6; right++) {
            Domino domino(left, right);
            cout << domino << endl;
        }
    }
    return 0;
}
