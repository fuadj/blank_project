#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <iomanip>
#include "vector.h"
#include "queue.h"
#include "random.h"
#include "simpio.h"
using namespace std;

//const double ARRIVAL_PROBABILITY = 0.05;
const double ARRIVAL_PROBABILITY = 0.1;
const int MIN_SERVICE_TIME = 5;
const int MAX_SERVICE_TIME = 15;
const int SIMULATION_TIME = 2000;

void runSimulation(int nCashiers, int & nServed, int & totalWait, int & totalLength);
void printReport(int nCashiers, int nServed, int totalWait, int totalLength);

int main() {
    int nServed;
    int totalWait;
    int totalLength;
    Vector<int> cashiers;
    cashiers += 1, 2, 3, 5, 10, 15, 20, 30, 50, 100;

    for (int num_cashier : cashiers) {
        runSimulation(num_cashier, nServed, totalWait, totalLength);
        cout << "Simulation with " << num_cashier << endl;
        printReport(num_cashier, nServed, totalWait, totalLength);
        cout << endl << endl << endl;
    }

    return 0;
}

void runSimulation(int nCashiers, int &nServed, int &totalWait, int &totalLength) {
    Queue<int> customers;
    Vector<int> cashiers(nCashiers);

    nServed = 0;
    totalWait = 0;
    totalLength = 0;

    for (int t = 0; t < SIMULATION_TIME; t++) {
        if (randomChance(ARRIVAL_PROBABILITY)) {
            customers.enqueue(t);
        }

        for (int i = 0; i < cashiers.size(); i++) {
            if (cashiers[i] > 0) {
                cashiers[i]--;
            } else if (!customers.isEmpty()) {
                totalWait += t - customers.dequeue();
                nServed++;
                cashiers[i] = randomInteger(MIN_SERVICE_TIME, MAX_SERVICE_TIME);
            }

            totalLength += customers.size();
        }
    }
}

void printReport(int nCashiers, int nServed, int totalWait, int totalLength) {
    cout << "Simulation results given the following constants:" << endl;
    cout << fixed << setprecision(2);
    cout << "  SIMULATION_TIME:     " << setw(4)
         << SIMULATION_TIME << endl;
    cout << "  ARRIVAL_PROBABILITY: " << setw(7)
         << ARRIVAL_PROBABILITY << endl;
    cout << "  MIN_SERVICE_TIME:    " << setw(4)
         << MIN_SERVICE_TIME << endl;
    cout << "  MAX_SERVICE_TIME:    " << setw(4)
         << MAX_SERVICE_TIME << endl;
    cout << endl;
    cout << "Customers served:      " << setw(4) << nServed << endl;
    cout << "Average waiting time:  " << setw(7)
         << double(totalWait) / nServed << endl;
    cout << "Average queue length:  " << setw(7)
         << double(totalLength) / (SIMULATION_TIME) << endl;
}
