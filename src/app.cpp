#include <iostream>
#include <string>
#include "console.h"
#include "vector.h"
#include "simpio.h"

using namespace std;

bool isMeasurable(int target, const Vector<int> & weights, Vector<int> correctWay);

void printMeasurable(int target, const Vector<int> & weights) {
    cout << "Measuring " << target << ":" << endl;
    isMeasurable(target, weights, Vector<int>());
    //cout << target << " is" << ( ? " " : " not ") << "measurable" << endl;
}

int main() {
    Vector<int> weights;
    weights += 1, 3, 7, 13;
    for (int i = 0; i < 20; i++) {
        printMeasurable(i, weights);
    }
    return 0;
}

bool isMeasurable(int target, const Vector<int> & weights, Vector<int> way) {
    if (weights.size() == 1) {
        bool measured = target == weights[0];
        if (measured) {
            way.add(weights[0]);		// just for printing
            cout << way.toString() << endl;
        }
        return measured;
    } else {
        Vector<int> rest = weights.subList(1, weights.size() - 1);
        Vector<int> asWeight = way;
        Vector<int> asCounterWeight = way;
        asWeight.add(weights[0]);
        asCounterWeight.add(-1 * weights[0]);
        return isMeasurable(target, rest, way) ||	// excluding the weight
                isMeasurable(target - weights[0], rest, asWeight) ||	// using the weight on the "weights" side
                isMeasurable(target + weights[0], rest, asCounterWeight);	// using the weight with the "mass" side
    }
}
