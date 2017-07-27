#include <string>
#include "gwindow.h"
#include <cmath>
//#include <unistd.h>
#include "gtypes.h"
#include "random.h"

using namespace std;

void drawSierpinskiTriangleOverlapping(GWindow & gw, GPoint left, double size, int order);
void drawSierpinskiTriangleNonOverlapping(GWindow & gw, GPoint left, double size, int order);

int ORDER_LIMIT = 8;
double BUFFER = 0.1;
int SIDE = 700;
//int ANIMATION_SPEED = 100000;

int main() {
    GWindow gw(SIDE, SIDE);
    double x = gw.getWidth() * BUFFER;
    double y = gw.getHeight() * (1 - BUFFER);

    //drawSierpinskiTriangleOverlapping(gw, GPoint(x, y), SIZE, ORDER_LIMIT);
    drawSierpinskiTriangleOverlapping(gw, GPoint(x, y), (gw.getWidth() * (1 - BUFFER * 2)), ORDER_LIMIT);
    //drawSierpinskiTriangleNonOverlapping(gw, GPoint(x, y), (gw.getWidth() * (1 - BUFFER * 2)), ORDER_LIMIT);
    return 0;
}

/**
 * This implementation overdraws too many overlapping lines b/c each triangle draws
 * its side overlapping its "parent" triangle.
 */
void drawSierpinskiTriangleOverlapping(GWindow & gw, GPoint leftBottom, double size, int order) {
    //usleep(ANIMATION_SPEED);
    if (order < 0) return;

    GPoint top = gw.drawPolarLine(leftBottom, size, 60);
    GPoint right = gw.drawPolarLine(leftBottom, size, 0);
    gw.drawLine(top, right);

    GPoint topTriangleLeftBottom = GPoint(
                (top.getX() + leftBottom.getX())/2,
                (top.getY() + leftBottom.getY())/2
                );
    GPoint rightTriangleLeftBottom = GPoint(
                (right.getX() + leftBottom.getX())/2,
                (right.getY() + leftBottom.getY())/2
                );
    drawSierpinskiTriangleOverlapping(gw, leftBottom, size / 2, order - 1);
    drawSierpinskiTriangleOverlapping(gw, topTriangleLeftBottom, size / 2, order - 1);
    drawSierpinskiTriangleOverlapping(gw, rightTriangleLeftBottom, size / 2, order - 1);
}

void drawSierpinskiRecursiveNonOverlapping(GWindow & gw, GPoint left, GPoint top, GPoint right, int order) {
    if (order < 0)
        return;
    GPoint top_left = GPoint(
                (left.getX() + top.getX())/2,
                (left.getY() + top.getY())/2
                );
    GPoint top_right = GPoint(
                (right.getX() + top.getX())/2,
                (right.getY() + top.getY())/2
                );
    GPoint bottom_mid = GPoint(
                (left.getX() + right.getX())/2,
                (left.getY() + right.getY())/2
                );
    gw.drawLine(top_left, top_right);
    gw.drawLine(top_left, bottom_mid);
    gw.drawLine(top_right, bottom_mid);

    drawSierpinskiRecursiveNonOverlapping(gw, top_left, top, top_right, order - 1);	// the top triangle
    drawSierpinskiRecursiveNonOverlapping(gw, left, top_left, bottom_mid, order - 1);	// the top triangle
    drawSierpinskiRecursiveNonOverlapping(gw, bottom_mid, top_right, right, order - 1);	// the top triangle
}

void drawSierpinskiTriangleNonOverlapping(GWindow & gw, GPoint left, double size, int order) {
    GPoint top = gw.drawPolarLine(left, size, 60);
    GPoint right = gw.drawPolarLine(left, size, 0);
    gw.drawLine(top, right);
    drawSierpinskiRecursiveNonOverlapping(gw, left, top, right, order - 1);
}
