#include "hist.h"
#include "console.h"
#include "vector.h"
#include <iostream>
#include "error.h"
#include <string>
#include <stdio.h>
#include <iomanip>
#include <math.h>

void countRange(Vector<int> & numbers, Vector<int> & ranges, int min_val, int max_val, int range) {
    if (min_val >= max_val || range <= 0)
        error("Invalid values for histogram");

    ranges.clear();
    for (int i = min_val; i <= max_val; i += range) {
        ranges.add(0);
    }

    for (int i = 0; i < numbers.size(); i++) {
        int num = numbers[i];
        if (num < min_val) num = min_val;
        if (num > max_val) num = max_val;

        int bucket = (num - min_val) / range;

        ranges[bucket]++;
    }
}

void printHistogram(Vector<int> & numbers, int min_val, int max_val, int range, char delim) {
    Vector<int> ranges;
    countRange(numbers, ranges, min_val, max_val, range);

    int width = int(log10(max_val)) + 1;
    for (int i = min_val, k = 0; i <= max_val; i += range, k++) {
        std::cout << std::right << std::setw(width) << i << "s: " ;

        std::cout << std::setfill(delim) << std::setw(ranges[k]) << "";	// the "" is so the rule setfill & setw can apply
        std::cout << std::setfill(' ') << std::endl;		// reset the fill
    }
}
