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
//const double ARRIVAL_PROBABILITY = 0.1;
const int MIN_SERVICE_TIME = 5;
const int MAX_SERVICE_TIME = 15;
const int SIMULATION_TIME = 2000;

void runSimulation(int nLines, int & nServed, int & totalWait, int & totalLength);
void printReport(int nLines, int nServed, int totalWait, int totalLength);

int main() {
    int nServed;
    int totalWait;
    int totalLength;
    int numLines;

    numLines = getInteger("How many checkout lines: ");
    runSimulation(numLines, nServed, totalWait, totalLength);
    printReport(numLines, nServed, totalWait, totalLength);
    return 0;
}

void runSimulation(int nLines, int &nServed, int &totalWait, int &totalLength) {
    Vector< Queue<int> > lines(nLines);
    Vector<int> waitingTimes(nLines);

    nServed = 0;
    totalWait = 0;
    totalLength = 0;

    for (int t = 0; t < SIMULATION_TIME; t++) {
        for (int i = 0; i < lines.size(); i++) {
            if (randomChance(ARRIVAL_PROBABILITY)) {
                lines[i].enqueue(t);
                break;
            }
        }

        for (int i = 0; i < waitingTimes.size(); i++) {
            if (waitingTimes[i] > 0) {
                waitingTimes[i]--;
            } else {
                if (!lines[i].isEmpty()) {
                    totalWait += t - lines[i].dequeue();
                    nServed++;
                    waitingTimes[i] = randomInteger(MIN_SERVICE_TIME, MAX_SERVICE_TIME);
                }
            }
            totalLength += lines[i].size();
        }
    }
}

void printReport(int nLines, int nServed, int totalWait, int totalLength) {
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
         << double(totalLength) / (nLines * SIMULATION_TIME) << endl;
}
