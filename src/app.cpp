#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include "gwindow.h"
#include "random.h"
using namespace std;

const double MIN_AREA = 10000;
const double MIN_EDGE = 10;			/* Smallest edge length allowed */

void subDivideCanvas(GWindow & gw, double x, double y,
                     double width, double height);

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 700;
    const int EDGE = 50;
    GWindow gw(WIDTH, HEIGHT);

    subDivideCanvas(gw, EDGE, EDGE, WIDTH - 2 * EDGE, HEIGHT - 2 * EDGE);

    return 0;
}

void subDivideCanvas(GWindow & gw, double x, double y, double width, double height) {
    if (width * height >= MIN_AREA) {
        int bm_r = 0xff & randomInteger(128, 255);
        int bm_g = 0xff & randomInteger(28, 140);
        int bm_b = 0xff & randomInteger(28, 85);
        int bm_color = 0xffffffff & (bm_r << 16 | bm_g << 8 | bm_b);

        int am_r = randomInteger(0, 28);
        int am_g = randomInteger(10, 128);
        int am_b = randomInteger(70, 200);
        int am_color = 0xffffffff & (am_r << 16 | am_g << 8 | am_b);

        if (width > height) {
            double mid = randomReal(MIN_EDGE, width - MIN_EDGE);

            gw.setColor(bm_color);
            gw.fillRect(GRectangle(x, y, mid, height));
            gw.setColor(am_color);
            gw.fillRect(GRectangle(x + mid, y, width - mid, height));

            //gw.drawLine(x + mid, y, x + mid, y + height);

            subDivideCanvas(gw, x, y, mid, height);
            subDivideCanvas(gw, x + mid, y, width - mid, height);
        } else {
            double mid = randomReal(MIN_EDGE, height - MIN_EDGE);

            gw.setColor(bm_color);
            gw.fillRect(GRectangle(x, y, width, mid));
            gw.setColor(am_color);
            gw.fillRect(GRectangle(x, y + mid, width, height - mid));

            //gw.drawLine(x, y + mid, x + width, y + mid);

            subDivideCanvas(gw, x, y, width, mid);
            subDivideCanvas(gw, x, y + mid, width, height - mid);
        }
    }
}

