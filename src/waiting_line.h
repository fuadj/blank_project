#ifndef _waiting_line_h
#define _waiting_line_h

#include "gwindow.h"
#include "queue.h"
#include "vector.h"
#include "gobjects.h"
#include <string>

const double WALL_2_HALLWAY = 5.1;		// hallway is this factor X bigger than the Wall
const double CUSTOMER_DIM = 0.5;	// as % of hallway-height

class WaitingLine {
public:
    WaitingLine();
    WaitingLine(GWindow * gw, const std::string & name,
                double x, double y, double width, double height, int numLines);

    void addCustomer(int line, int arrivalTime);
    int removeCustomer(int line, int removalTime);

    int getNumCustomers(int line);
    bool isLineEmpty(int line);

    static double heightForNumLines(int numLines, double singleHallwayHeight);

private:
    GWindow * gw;

    double x, y;
    double width, height;

    struct Customer {
        GOval *profile;
        int arrivalTime;
    };

    // b/c we want to iterate through the queue, we are forced to use a Vector
    // with 0 being the "front"
    Vector< Vector<Customer> > queues;
    Vector< GRectangle > lineBounds;

    double wallHeight;
    double hallwayHeight;

    std::string lineName;
    int numLines;

    GLabel *labelNumCustomers;
    GLabel *labelTotalWaitTime;
    GLabel *labelAvgLineLength;
    GLabel *labelAvgWaitTime;

    int totalCustomersServiced;
    int totalWaitTime;

    // instead of looping through the lines and summing their lengths, just keep a counter
    // and ++ when adding a customer and -- when removing one.
    int customersInLines;

    void init(GWindow * gw, const std::string & name, double x, double y, double width, double height, int numLines);

    const int COLOR_WALL = 0xff000000;
};

#endif
