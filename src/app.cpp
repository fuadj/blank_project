#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include <iomanip>
#include "calendar.h"

using namespace std;

int main() {
    Date moonLanding(JULY, 20, 1969);
    Date a_year_prior = (moonLanding - 365);

    cout << "Count down to appolo" << endl;
    for (int i = 0; i < 365; i++) {
        cout << a_year_prior++ << endl;
    }

    cout << endl;
    for (int i = 0; i < 40; i++) cout << "=";
    cout << endl << "Reverse order" << endl;
    for (int i = 0; i < 40; i++) cout << "=";
    cout << endl;

    for (int i = 0; i < 365; i++) {
        cout << a_year_prior-- << endl;
    }

    return 0;
}
