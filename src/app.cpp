#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include "map.h"
#include <string>
#include <iomanip>

using namespace std;

int digitSum(int n);

int main() {
    int num = 1729;

    cout << "The digit sum of " << num << " is " << digitSum(num) << endl;
    return 0;
}

int digitSum(int n) {
    if (n < 10) return n;

    int ones = n - (n / 10) * 10;
    return ones + digitSum(n / 10);
}
