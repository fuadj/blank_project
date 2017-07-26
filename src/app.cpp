#include <string>
#include "gwindow.h"
#include <cmath>

using namespace std;

const int INCH_WIDTH = 320;
const int INCH_HEIGHT = 80;

const int NUM_LEVELS = 4;

void drawMarker(GWindow & gw, int x, int y, int sideSpan, int level = 0);

int main() {
    GWindow gw;
    int center_x = gw.getWidth() / 2;
    int center_y = int(double(gw.getHeight()) * 0.8);
    gw.setColor("black");

    gw.drawLine(center_x - (INCH_WIDTH / 2), center_y, center_x + (INCH_WIDTH / 2), center_y);

    drawMarker(gw, center_x, center_y, INCH_WIDTH/2);
    return 0;
}

void drawMarker(GWindow & gw, int x, int y, int sideSpan, int level) {
    if (level < NUM_LEVELS) {
        double tick_height = INCH_HEIGHT / pow(2, level);
        gw.drawLine(x, y - tick_height, x, y);
        drawMarker(gw, x - sideSpan/2, y, sideSpan/2, level+1);
        drawMarker(gw, x + sideSpan/2, y, sideSpan/2, level+1);
    }
}
