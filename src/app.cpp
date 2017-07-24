#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include "set.h"

using namespace std;

int countSubsetSumWays(const Set<int> & set, int target);
int countSubsetSumWays2(const Set<int> & set, int target);

void printWays(const Set<int> & set, int n) {
    cout << "Func1: Searching for " << n << " " << countSubsetSumWays(set, n) << "ways" << endl;
    cout << "Func2: Searching for " << n << " " << countSubsetSumWays2(set, n) << "ways" << endl;
}

int main() {
    Set<int> sampleSet;
    sampleSet += 1, 3, 4, 5;
    printWays(sampleSet, 5);
    printWays(sampleSet, 11);
    return 0;
}

void countSubsetSumWaysRecurse(const Set<int> & set, int target, int & matchCount) {
    if (set.isEmpty()) {
        bool is_match = target == 0;
        matchCount += is_match ? 1 : 0;
    } else {
        int element = set.first();
        Set<int> rest = set - element;
        countSubsetSumWaysRecurse(rest, target, matchCount);
        countSubsetSumWaysRecurse(rest, target - element, matchCount);
    }
}

int countSubsetSumWays(const Set<int> & set, int target) {
    int matchCount = 0;
    countSubsetSumWaysRecurse(set, target, matchCount);
    return matchCount;
}

int countSubsetSumWays2(const Set<int> & set, int target) {
    if (set.isEmpty()) {
        return target == 0 ? 1 : 0;
    } else {
        int element = set.first();
        Set<int> rest = set - element;
        return countSubsetSumWays2(rest, target) +
                countSubsetSumWays2(rest, target - element);
    }
}
