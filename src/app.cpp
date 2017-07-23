#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include "map.h"
#include <string>
#include <iomanip>

using namespace std;

int combination(int n, int k);

const int HALF_SPACE = 3;
const int SPACE_WIDTH = 2 * HALF_SPACE; 	// it is defined interms of HALF_SPACE * 2 so it is always even
const int LEFT_OFFSET = 3;

int main() {
    int n = 11;

    for (int i = 0; i <= n; i++) {
        cout << setw(LEFT_OFFSET + (n - i) * HALF_SPACE);
        for (int k = 0; k <= i; k++) {
            cout << combination(i, k);
            cout << setw(SPACE_WIDTH);
        }
        cout << endl;
    }

    return 0;
}

int combination(int n, int k) {
    if ((n < 2) || (k == 0) || (k == n))
        return 1;
    return combination(n-1, k) + combination(n-1, k-1);
}
