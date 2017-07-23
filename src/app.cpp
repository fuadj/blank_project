#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include "map.h"
#include <string>
#include <iomanip>

using namespace std;

int digitSum(int n);
int digitRoot(int n);

int main() {
    int num = 999999997;

    cout << "The digit root of " << num << " is " << digitRoot(num) << endl;
    return 0;
}

int digitSum(int n) {
    if (n < 10) return n;

    int ones = n - (n / 10) * 10;
    return ones + digitSum(n / 10);
}

int digitRoot(int n) {
    int sum = digitSum(n);
    if (sum < 10) return sum;

    return digitRoot(sum);
}
