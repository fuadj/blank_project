#include "waiting_line.h"
#include "gobjects.h"
#include "strlib.h"
#include <cmath>
#include <iomanip>
#include <sstream>

WaitingLine::WaitingLine() {
    init(NULL, "", 0, 0, 0, 0, 1);
}

WaitingLine::WaitingLine(GWindow *gw, const std::string & name, double x, double y, double width, double height, int numLines) {
    init(gw, name, x, y, width, height, numLines);
}

GLabel *newStatLabel() {
    GLabel *label = new GLabel("");
    //label->setFont("SansSerif-14");
    label->setFont("Console-14");
    label->setColor("#13258b");
    return label;
}

void WaitingLine::init(GWindow * gw, const std::string & name, double x, double y, double width, double height, int numLines) {
    this->gw = gw;
    this->lineName = name;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->numLines = numLines;

    this->totalCustomersServiced = 0;
    this->totalWaitTime = 0;
    this->customersInLines = 0;

    for (int i = 0; i < numLines; i++) {
        this->queues.push_back(Vector<Customer>());
        this->queueStartIndex.push_back(0);
    }

    wallHeight = height / (double(numLines) * (WALL_2_HALLWAY + 1) + 1);
    hallwayHeight = wallHeight * WALL_2_HALLWAY;

    double currentY = y;
    int i;
    for (i = 0; i < numLines; i++) {
        gw->setColor(COLOR_WALL);
        gw->fillRect(x, currentY, width, wallHeight);
        currentY += wallHeight;

        lineBounds.push_back(GRectangle(x, currentY, width, hallwayHeight));
        currentY += hallwayHeight;
    }

    if (i != 0) {
        gw->fillRect(x, currentY, width, wallHeight);
        currentY += wallHeight;
    }

    GLabel *label = new GLabel(lineName);
    label->setFont("SansSerif-34");
    label->setColor("#3355bb");

#define _MINIMUM_(x,y) ((x) < (y) ? (x) : (y))
    double label_x = x + _MINIMUM_((1.0/12.0) * width, ((width - label->getWidth())/2));
    double label_y = y - label->getFontDescent();
    gw->add(label, label_x, label_y);

    labelNumCustomers = newStatLabel();
    labelTotalWaitTime = newStatLabel();
    labelAvgLineLength = newStatLabel();
    labelAvgWaitTime = newStatLabel();

    double _y_offset = 0;
    GCompound *labelCompound = new GCompound();
    labelCompound->add(labelNumCustomers, 0, _y_offset);
    _y_offset += labelNumCustomers->getHeight();
    labelCompound->add(labelTotalWaitTime, 0, _y_offset);
    _y_offset += labelTotalWaitTime->getHeight();
    labelCompound->add(labelAvgLineLength, 0, _y_offset);
    _y_offset += labelAvgLineLength->getHeight();
    labelCompound->add(labelAvgWaitTime, 0, _y_offset);

    gw->add(labelCompound, x + width + width * 0.05, (y + height/2) - (_y_offset/2));
}

int getNthPlaceColor(int i, int numPlaces) {
    int start_x = 0, end_x = 255;
    //double d = double(numPlaces - i)/numPlaces;
    double d = double(i)/numPlaces;

    //int red = 0xff & int(d * (end_x - start_x) + start_x);
    int red = 0xff & int(end_x - d * (end_x - start_x));
    int color = (red << 16);

    return color;
}

int getNthPlaceColor(int front, int nth, int back) {
    const int START_RED = 0, END_RED = 255;
    double d;

    if (back == front)
        d = 0;
    else
        d = pow(double(nth - front)/(back - front), 1.0);

    int red = 0xff & int(END_RED - d * (END_RED - START_RED));
    int color = (red << 16);

    return color;
}

void WaitingLine::addCustomer(int lineNumber, int arrivalTime) {
    double profile_size = CUSTOMER_DIM * hallwayHeight;
    double y_offset = (hallwayHeight - profile_size)/2;

    GOval *profile = new GOval(profile_size, profile_size);

    profile->setFilled(true);
    double x_offset = double(x + width - (profile_size * (1 + getNumCustomers(lineNumber))));
    profile->setLocation(GPoint(x_offset, lineBounds[lineNumber].getY() + y_offset));

    gw->add(profile);

    Customer customer;
    customer.arrivalTime = arrivalTime;
    customer.profile = profile;

    queues[lineNumber].push_back(customer);

    int front_arrival = queues[lineNumber][queueStartIndex[lineNumber]].arrivalTime;
    profile->setFillColor(getNthPlaceColor(front_arrival, arrivalTime, arrivalTime));

    totalCustomersServiced++;
    customersInLines++;

    updateStat();
}

void WaitingLine::removeCustomer(int lineNumber, int removalTime) {
    Vector<Customer> &customerQueue = queues[lineNumber];
    Customer customer = customerQueue[queueStartIndex[lineNumber]];
    queueStartIndex[lineNumber]++;	// simulate "dequeue"

    gw->remove(customer.profile);
    delete customer.profile;

    // if there are still other customers, shift them to the right
    int start = queueStartIndex[lineNumber];
    int end = customerQueue.size();
    if (start < end) {
        int front_arrival = customerQueue[start].arrivalTime;
        int back_arrival = customerQueue[customerQueue.size() - 1].arrivalTime;
        for (int i = start, k = 0; i < end; i++, k++) {
            customerQueue[i].profile->move(CUSTOMER_DIM * hallwayHeight, 0);
            customerQueue[i].profile->setFillColor(getNthPlaceColor(front_arrival, customerQueue[i].arrivalTime, back_arrival));
        }
    }

    int wait_time = removalTime - customer.arrivalTime;

    totalWaitTime += wait_time;
    customersInLines--;

    updateStat();
}

void WaitingLine::updateStat() {
    std::ostringstream str;

    str << "Total Wait Time:" << std::setw(12) << totalWaitTime;
    labelTotalWaitTime->setLabel(str.str());

    str.str("");		// clear it
    str << "Avg Wait Time:" << std::setw(15) << std::setprecision(2) << (double(totalWaitTime)/totalCustomersServiced);
    labelAvgWaitTime->setLabel(str.str());

    str.str("");
    str << "Avg Line Length:" << std::setw(12) << std::setprecision(2) << (double(customersInLines)/numLines);
    labelAvgLineLength->setLabel(str.str());

    str.str("");
    str << "Num Customers:" << std::setw(10) << std::right << totalCustomersServiced;
    labelNumCustomers->setLabel(str.str());
}

int WaitingLine::getNumCustomers(int line) {
    return queues[line].size() - queueStartIndex[line];
}

bool WaitingLine::isLineEmpty(int line) {
    return getNumCustomers(line) == 0;
}

double WaitingLine::heightForNumLines(int numLines, double singleHallwayHeight) {
    return singleHallwayHeight * (numLines + (numLines + 1)/WALL_2_HALLWAY);
}
