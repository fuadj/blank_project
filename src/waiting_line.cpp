#include "waiting_line.h"
#include "gobjects.h"
#include "strlib.h"
#include <cmath>

WaitingLine::WaitingLine() {
    init(NULL, "", 0, 0, 0, 0, 1);
}

WaitingLine::WaitingLine(GWindow *gw, const std::string & name, double x, double y, double width, double height, int numLines) {
    init(gw, name, x, y, width, height, numLines);
}

GLabel *newStatLabel() {
    GLabel *label = new GLabel("");
    label->setFont("SansSerif-14");
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

    this->numCustomers = 0;
    this->totalWaitTime = 0;
    this->avgLineLength = 0;
    this->avgWaitTime = 0;

    for (int i = 0; i < numLines; i++)
        this->queues.push_back(Vector<Customer>());

    wallHeight = height / (
                double(numLines) * (WALL_2_HALLWAY + 1) + 1
                );
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
    double d = double(numPlaces - i)/numPlaces;

    int red = 0xff & int(d * (end_x - start_x) + start_x);
    int color = (red << 16);

    return color;
}

void WaitingLine::addCustomer(int lineNumber, int arrivalTime) {
    double size = CUSTOMER_DIM * hallwayHeight;
    double y_offset = (hallwayHeight - size)/2;

    GOval *profile = new GOval(size, size);

    profile->setFilled(true);
    profile->setFillColor(
                getNthPlaceColor(queues[lineNumber].size(), 1 + queues[lineNumber].size())
                );

    int customers_to_right = queues[lineNumber].size();

    profile->setLocation(
                GPoint(
                    ((x + width - (CUSTOMER_DIM * hallwayHeight)) -
                     (customers_to_right * (CUSTOMER_DIM * hallwayHeight))
                     ),
                    lineBounds[lineNumber].getY() + y_offset)
                );
    gw->add(profile);

    Customer customer;
    customer.arrivalTime = arrivalTime;
    customer.profile = profile;

    queues[lineNumber].push_back(customer);

    labelNumCustomers->setLabel("Num Customers: " + integerToString(++numCustomers));
}

int WaitingLine::removeCustomer(int lineNumber, void (*fn)(void)) {
    Vector<Customer> &customerQueue = queues[lineNumber];
    Customer customer = customerQueue[0];
    customerQueue.remove(0);		// "dequeue"

    gw->remove(customer.profile);
    delete customer.profile;

    // if there are still other customers, shift them to the right
    for (int i = 0; i < customerQueue.size(); i++) {
        if (fn)
            fn();
        customerQueue[i].profile->move(CUSTOMER_DIM * hallwayHeight, 0);
        customerQueue[i].profile->setFillColor(getNthPlaceColor(i, queues[lineNumber].size()));
    }

    return customer.arrivalTime;
}

int WaitingLine::getNumCustomers(int line) {
    return queues[line].size();
}

bool WaitingLine::isLineEmpty(int line) {
    return getNumCustomers(line) == 0;
}

double WaitingLine::heightForNumLines(int numLines, double singleHallwayHeight) {
    return singleHallwayHeight * (numLines + (numLines + 1)/WALL_2_HALLWAY);
}
