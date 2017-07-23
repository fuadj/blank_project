#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include "map.h"
#include <string>
#include <iomanip>

using namespace std;

double getTitiusBodeDistance(int n);

int main() {
    Map<int, string> planetName;
    planetName.put(1, "Mercury");
    planetName.put(2, "Venus");
    planetName.put(3, "Earth");
    planetName.put(4, "Mars");
    planetName.put(5, "?");
    planetName.put(6, "Jupiter");
    planetName.put(7, "Saturn");
    planetName.put(8, "Uranus");

    int longest_planet_name = 0;
    for (int planet : planetName) {
        if (planetName[planet].length() > longest_planet_name)
            longest_planet_name = planetName[planet].length();
    }

    for (int i = 1; i <= 8; i++) {
        cout << left << setw(longest_planet_name) << planetName[i];
        cout << "\t" << right << setw(3) << setprecision(3) << getTitiusBodeDistance(i);
        cout << endl;
    }
    return 0;
}

int getPlanetSequence(int n) {
    if (n == 1) return 1;
    if (n == 2) return 3;

    return 2 * getPlanetSequence(n - 1);
}

double getTitiusBodeDistance(int n) {
    return double(4 + getPlanetSequence(n)) / 10;
}
