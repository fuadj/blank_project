#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include <cmath>
#include <unistd.h>
#include "gwindow.h"
#include "gtypes.h"
using namespace std;

const double SIZE = 200;
//const int ORDER = 4;
const int ORDER = 5;
const int SLEEP_U_S = 1000;

GPoint drawFractalLine(GWindow & gw, GPoint pt,
                       double r, double theta, int order);

int main() {
    GWindow gw;
    double cx = gw.getWidth() / 2;
    double cy = gw.getHeight() / 2;

    GPoint pt(cx - SIZE / 2, cy - sqrt(3.0) * SIZE / 6);
    /*
    pt = drawFractalLine(gw, pt, SIZE, 0, ORDER);
    pt = drawFractalLine(gw, pt, SIZE, -120, ORDER);
    pt = drawFractalLine(gw, pt, SIZE, 120, ORDER);
    */
    pt = drawFractalLine(gw, pt, SIZE, 0, ORDER);
    pt = drawFractalLine(gw, pt, SIZE, -90, ORDER);
    pt = drawFractalLine(gw, pt, SIZE, -180, ORDER);
    pt = drawFractalLine(gw, pt, SIZE, 90, ORDER);

    return 0;
}

GPoint drawFractalLine(GWindow & gw, GPoint pt, double r, double theta, int order) {
    if (order <= 0) {
        usleep(SLEEP_U_S);
        return gw.drawPolarLine(pt, r, theta);
    } else {
        GPoint save = pt;
        pt = drawFractalLine(gw, pt, r / 3, theta, order - 1);
        pt = drawFractalLine(gw, pt, r / 3, theta - 60, order - 1);
        pt = drawFractalLine(gw, pt, r / 3, theta + 60, order - 1);
        pt = drawFractalLine(gw, pt, r / 3, theta, order - 1);
        /*
        save = gw.drawPolarLine(save, r / 3, theta);
        save = gw.drawPolarLine(save, r / 3, theta - 60);
        save = gw.drawPolarLine(save, r / 3, theta + 60);
        save = gw.drawPolarLine(save, r / 3, theta);
        */
        /*
        pt = drawFractalLine(gw, pt, r / 4, theta, order - 1);
        pt = drawFractalLine(gw, pt, r / 4, theta + 60, order - 1);
        pt = drawFractalLine(gw, pt, r / 4, theta, order - 1);
        pt = drawFractalLine(gw, pt, r / 4, theta - 60, order - 1);
        pt = drawFractalLine(gw, pt, r / 4, theta, order - 1);
        */
        /*
        pt = drawFractalLine(gw, pt, r / 3, theta + 60, order - 1);
        pt = drawFractalLine(gw, pt, r / 3, theta - 60, order - 1);
        pt = drawFractalLine(gw, pt, r / 3, theta, order - 1);
        pt = drawFractalLine(gw, pt, r / 3, theta + 60, order - 1);
        pt = drawFractalLine(gw, pt, r / 3, theta - 60, order - 1);
        */
        /*
        save = gw.drawPolarLine(save, r / 3, theta);
        save = gw.drawPolarLine(save, r / 3, theta + 60);
        save = gw.drawPolarLine(save, r / 3, theta - 60);
        save = gw.drawPolarLine(save, r / 3, theta);
        */
        return pt;
    }
}
