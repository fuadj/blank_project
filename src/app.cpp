#include <string>
#include "gwindow.h"
#include <cmath>
#include "gtypes.h"
#include "random.h"

using namespace std;

const double BRANCH_DEGREE = 90;
const double BRANCH_SCALE = 0.61;

void drawFractalTree(GWindow & gw, double x, double y, double r, double theta, int order);

int main() {
    GWindow gw;
    double x = gw.getWidth() / 2;
    double y = gw.getHeight() * 0.80;
    drawFractalTree(gw, x, y, 100, 90, 7);
    return 0;
}

void drawFractalTree(GWindow & gw, double x, double y, double r, double theta, int order) {
    if (order < 0)
        return;

    GPoint pt = gw.drawPolarLine(x, y, r, theta);
    drawFractalTree(gw, pt.getX(), pt.getY(), r * BRANCH_SCALE, theta+BRANCH_DEGREE/2, order-1);
    drawFractalTree(gw, pt.getX(), pt.getY(), r * BRANCH_SCALE, theta-BRANCH_DEGREE/2, order-1);
}
