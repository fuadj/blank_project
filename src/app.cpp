#include <string>
#include "gwindow.h"
#include <cmath>
#include "gtypes.h"
#include "random.h"

using namespace std;

void drawHFractal(GWindow & gw, double x, double y, double size, int order);

int main() {
    GWindow gw;
    double xc = gw.getWidth() / 2;
    double yc = gw.getHeight() / 2;
    drawHFractal(gw, xc, yc, 100, 3);
    return 0;
}

void drawHFractal(GWindow & gw, double x, double y, double size, int order) {
    if (order < 0)
        return;

    double x_left = x-size/2, x_right = x+size/2;
    double y_top = y-size/2, y_bottom = y+size/2;
    gw.drawLine(x_left, y, x_right, y);
    gw.drawLine(x_left, y_top, x_left, y_bottom);
    gw.drawLine(x_right, y_top, x_right, y_bottom);
    drawHFractal(gw, x_left, y_top, size/2, order-1);
    drawHFractal(gw, x_right, y_top, size/2, order-1);
    drawHFractal(gw, x_left, y_bottom, size/2, order-1);
    drawHFractal(gw, x_right, y_bottom, size/2, order-1);
}
