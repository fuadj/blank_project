#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include <string>
#include "set.h"
#include "strlib.h"
#include "error.h"

using namespace std;

bool subSetSum(Set<int> & nums, int target);
bool subsetSumExists(Set<int> & set, int target);

int main() {
    Set<int> nums;
    nums.add(-2);
    nums.add(1);
    nums.add(8);
    nums.add(7);
    nums.add(13);
    nums.add(18);

    for (int i = 0; i < 30; i++) {
        if (subSetSum(nums, i) != subsetSumExists(nums, i))
            error("" + integerToString(i) + "th sum don't match");
    }

    cout << "Comparision Done!!!" << endl;

    return 0;
}

bool subSetSum(Set<int> & nums, int target) {
    if (nums.isEmpty()) return target == 0;

    int sum = 0;
    for (int n : nums) {
        sum += n;
    }
    if (sum == target) return true;

    for (int n : nums) {
        Set<int> rest = nums - n;
        if (subSetSum(rest, target))
            return true;
    }
    return false;
}

bool subsetSumExists(Set<int> & set, int target) {
    if (set.isEmpty()) {
        return target == 0;
    } else {
        int element = set.first();
        Set<int> rest = set - element;
        return subsetSumExists(rest, target)
                || subsetSumExists(rest, target - element);
    }
}
