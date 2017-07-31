#include "waiting_line.h"
#include "gobjects.h"
#include "strlib.h"

WaitingLine::WaitingLine() {
    init(NULL, 0, 0, 0, 0, 1);
}

WaitingLine::WaitingLine(GWindow *gw, double x, double y, double width, double height, int numLines) {
    init(gw, x, y, width, height, numLines);
}

void WaitingLine::init(GWindow *gw, double x, double y, double width, double height, int numLines) {
    this->gw = gw;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
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
