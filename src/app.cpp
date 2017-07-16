#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>
#include "error.h"
#include "simpio.h"
#include "stack.h"
#include "queue.h"
#include "random.h"

using namespace std;

void applyOperator(char op, Stack<double> & operandStack);
void helpCommand();

int main() {
    const int SIMULATION_TIME = 100;
    const int SERVICE_TIME = 13;
    const int ARRIVAL_TIME = 20;

    setRandomSeed(0);

    Queue<int> waitingLine;
    Stack<int> serviceTimes;

    int next_arrival;

    next_arrival = randomInteger(0, ARRIVAL_TIME);
    for (int i = 0; i < SIMULATION_TIME; i++) {
        if (i == next_arrival) {

            // schedule the next arrival time
            next_arrival = i + randomInteger(0, ARRIVAL_TIME);

            int last_service_time = i;
            if (!serviceTimes.isEmpty()) {
                last_service_time = serviceTimes.peek();
                if (last_service_time < i)
                    last_service_time = i;
            }
            int service_end_time = last_service_time + randomInteger(0, SERVICE_TIME);
            waitingLine.enqueue(service_end_time);
            serviceTimes.push(service_end_time);
            cout << "Customer arrived at " << i << " will finish at " << service_end_time << endl;
        }

        if (waitingLine.isEmpty()) continue;

        // if the customer's end time is reached, "finsh" their service
        if (waitingLine.peek() == i) {
            waitingLine.dequeue();
            cout << "Customer Serviced " << i << endl;
        }
    }

    cout << "Line finished" << endl;

    return 0;
}
