#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <iomanip>
#include <string>
#include "vector.h"
#include "math.h"
using namespace std;

/**
 * @brief findPrimes searches for primes till the number n included and stores the result
 */
void findPrimes(int n, Vector<int> & primes) {
    primes.clear();
    const int START = 2;

    Vector<bool> numbers;

    numbers.add(true);	// these 2 are dummy place holders for numbers 0 & 1
    numbers.add(true);  // we wanted the array index to match the number directly

    // all number start out "primes"
    for (int i = START; i <= n; i++) {
        numbers.add(true);
    }

    for (int i = START; i <= n; i++) {
        // ignore the number, start with its next multiple and cross the rest off
        for (int j = 2 * i; j <= n; j += i) {
            numbers[j] = false;
        }
    }

    for (int i = START; i <= n; i++) {
        if (numbers[i])
            primes.add(i);
    }
}

int main() {
    Vector<int> primes;

    findPrimes(1000, primes);

    int print_width = int(log10(primes[primes.size() - 1])) + 1;

    cout << "These numbers are primes: " << endl;
    for (int prime : primes) {
        cout << right << setw(print_width) << prime << endl;
    }

    return 0;
}
