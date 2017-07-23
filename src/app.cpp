#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include "map.h"
#include <string>
#include <iomanip>

using namespace std;

int countFib1(int n);
int countFib2(int n);

int main() {
    cout << "This program counts the number of calls made by the two" << endl;
    cout << "algorithms used to compute the Fibonacci sequence." << endl;

    int W_N = 4, W_F_1 = 11, W_F_2 = 7;

    cout << right << setw(W_N) << "n" << setw(W_F_1) << "fib1" << setw(W_F_2) << "fib2" << endl;
    cout << right << setw(W_N) << "--" << setw(W_F_1) << "----" << setw(W_F_2) << "----" << endl;

    for (int n = 0; n <= 33; n++) {
        cout << right << setw(W_N) << n;
        cout << right << setw(W_F_1) << countFib1(n);
        cout << right << setw(W_F_2) << countFib2(n);
        cout << endl;
    }
    return 0;
}

int countFib1(int n) {
    if (n < 2) {
        return 1;
    } else {
        return 1 + countFib1(n - 1) + countFib1(n - 2);
    }
}

int additiveSequence2(int n, int t0, int t1, int & callCounter) {
    callCounter++;
    if (n == 0) return t0;
    if (n == 1) return t1;
    return additiveSequence2(n - 1, t1, t0 + t1, callCounter);
}

int countFib2(int n) {
    int callCounter = 1;		// it starts at 1 b/c this is also a 'wrapper' func call
    additiveSequence2(n, 0, 1, callCounter);
    return callCounter;
}

/**
 * The 2 Fibonacci Implementations
 */
int fib1(int n) {
    if (n < 2) {
        return n;
    } else {
        return fib1(n - 1) + fib1(n - 2);
    }
}

int additiveSequence(int n, int t0, int t1) {
    if (n == 0) return t0;
    if (n == 1) return t1;
    return additiveSequence(n - 1, t1, t0 + t1);
}

int fib2(int n) {
    return additiveSequence(n, 0, 1);
}
