#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include "gobjects.h"
#include "gwindow.h"
#include "waiting_line.h"
#include "random.h"
#include "vector.h"
#include "queue.h"
#include "strlib.h"

using namespace std;

const double ARRIVAL_PROBABILITY = 0.34;

const int MIN_SERVICE_TIME = 5;
const int MAX_SERVICE_TIME = 15;
const int SIMULATION_TIME = 2000;

const double X_OFFSET = 0.15;
const double LINE_WIDTH = 0.45;

const double SIMULATION_TIME_OFFSET = 0.03;

const double HALLWAY_HEIGHT = 0.02;		// as % of total HEIGHT

const int NUM_LINES = 6;

const int NUM_CASHIER_LINES = 6;
const int NUM_CASHIERS = 14;

const double WIDTH = 1000;
const double HEIGHT = 700;

int main() {
    GWindow gw(WIDTH, HEIGHT);
    /*
    GWindow gw;
    double WIDTH = getScreenWidth(), HEIGHT = getScreenHeight();
    gw.setSize(WIDTH, HEIGHT);
    */

    double single_height = WaitingLine::heightForNumLines(1, HALLWAY_HEIGHT * HEIGHT);
    double multi_independent_height = WaitingLine::heightForNumLines(NUM_LINES, HALLWAY_HEIGHT * HEIGHT);
    double multi_dependent_height = WaitingLine::heightForNumLines(NUM_LINES, HALLWAY_HEIGHT * HEIGHT);
    double multi_cashier_height = WaitingLine::heightForNumLines(NUM_CASHIER_LINES, HALLWAY_HEIGHT * HEIGHT);

    double y_buffer = double(HEIGHT - (single_height + multi_independent_height + multi_dependent_height + multi_cashier_height)) / 5.0;

    double y_single = y_buffer;
    double y_multi_independet = y_buffer + (y_single + single_height);
    double y_multi_dependent = y_buffer + (y_multi_independet + multi_independent_height);
    double y_multi_cashier = y_buffer + (y_multi_dependent + multi_dependent_height);

    double x_offset = X_OFFSET * WIDTH;
    double line_width = LINE_WIDTH * WIDTH;

    GLabel *labelSimTime = new GLabel("");
    labelSimTime->setFont("Console-24");
    labelSimTime->setColor("black");
    gw.add(labelSimTime, SIMULATION_TIME_OFFSET * WIDTH, SIMULATION_TIME_OFFSET * HEIGHT + labelSimTime->getHeight());

    WaitingLine singleLine(&gw,
                           "Single Customer Line",
                           x_offset, y_single, line_width, single_height,
                           1);

    WaitingLine multiIndependentLines(&gw,
                                      "Independent Lines",
                                      x_offset, y_multi_independet, line_width, multi_independent_height,
                                      NUM_LINES);

    // If a customer arrives at a line there won't be another customer
    // for the other lines until the next simulation cycle
    WaitingLine multiDependentLines(&gw,
                                    "Dependent Lines",
                                    x_offset, y_multi_dependent, line_width, multi_dependent_height,
                                    NUM_LINES);

    WaitingLine multiCashiers(&gw,
                              "Multi Cashiers (" + integerToString(NUM_CASHIERS) + ")",
                              x_offset, y_multi_cashier, line_width, multi_cashier_height,
                              NUM_CASHIER_LINES);

    int time_single = 0;
    Vector<int> time_multi_independent(NUM_LINES);
    Vector<int> time_multi_dependent(NUM_LINES);

    Vector<int> cashiers(NUM_CASHIERS);

    // for the dependent lines, if we always start from the 0-th line and we 'break' when a customer
    // arrives at some line, it won't be actually fair distribution of customers.
    // The conclusion was reached after seeing the simulation result.
    // So, we now do a round-robin style "handing" out of customers.
    int last_dependent_line = 0;

    int last_cashier_line = 0;		// again like what was happening to "last_dependent_line"

    gw.setRepaintImmediately(false);

    for (int t = 0; t < SIMULATION_TIME; t++) {
        labelSimTime->setLabel("Time: " + integerToString(t));

        /**
         * ========================
         * Customer Arrival Section
         * ========================
         */

        if (randomChance(ARRIVAL_PROBABILITY)) {
            singleLine.addCustomer(0, t);
        }

        bool customer_arrived = false;
        for (int i = 0; i < NUM_LINES; i++) {
            if (randomChance(ARRIVAL_PROBABILITY))		// the in-dependent(every ile has isn't own "random" customer pool)
                multiIndependentLines.addCustomer(i, t);

            if (!customer_arrived) {
                if (randomChance(ARRIVAL_PROBABILITY)) { // the dependent(it is more realistic)
                    customer_arrived = true;
                    last_dependent_line = (i + last_dependent_line) % NUM_LINES;
                    multiDependentLines.addCustomer(last_dependent_line, t);
                }
            }
        }

        for (int i = 0; i < NUM_CASHIER_LINES; i++) {
            if (randomChance(ARRIVAL_PROBABILITY))
                multiCashiers.addCustomer(i, t);
        }


        /**
         * ========================
         * Customer Service Section
         * ========================
         */

        if (time_single > 0) {
            time_single--;
        } else if (!singleLine.isLineEmpty(0)) {
            singleLine.removeCustomer(0, t);
            time_single = randomInteger(MIN_SERVICE_TIME, MAX_SERVICE_TIME);
        }

        for (int i = 0; i < NUM_LINES; i++) {
            if (time_multi_independent[i] > 0)		// the in-dependent
                time_multi_independent[i]--;
            else if (!multiIndependentLines.isLineEmpty(i)) {
                multiIndependentLines.removeCustomer(i, t);
                time_multi_independent[i] = randomInteger(MIN_SERVICE_TIME, MAX_SERVICE_TIME);
            }

            if (time_multi_dependent[i] > 0)		// the dependent
                time_multi_dependent[i]--;
            else if (!multiDependentLines.isLineEmpty(i)) {
                multiDependentLines.removeCustomer(i, t);
                time_multi_dependent[i] = randomInteger(MIN_SERVICE_TIME, MAX_SERVICE_TIME);
            }
        }

        for (int i = 0; i < NUM_CASHIERS; i++) {
            if (cashiers[i] > 0) {		// if servicing a customer ignore and move-on
                cashiers[i]--;
            } else {
                for (int k = 0; k < NUM_CASHIER_LINES; k++) {
                    int cashier_line = (last_cashier_line + k + 1) % NUM_CASHIER_LINES;

                    if (!multiCashiers.isLineEmpty(cashier_line)) {
                        last_cashier_line = cashier_line;
                        multiCashiers.removeCustomer(cashier_line, t);
                        cashiers[i] = randomInteger(MIN_SERVICE_TIME, MAX_SERVICE_TIME);
                        break;
                    }
                }
            }
        }

        gw.repaint();
        pause(10);
    }

    return 0;
}
