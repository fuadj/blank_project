#include <string>
#include "gwindow.h"
#include <cmath>
#include "gtypes.h"
#include "random.h"

using namespace std;

const int LEVEL_LIMIT = 8;

GPoint drawCoastLine(GWindow & gw, GPoint pt, double length, double theta, int level = 0);

int main() {
    GWindow gw;
    int start_x = int(double(gw.getWidth()) * 0.1);
    int end_x = int(double(gw.getWidth()) * 0.9);
    int y = gw.getHeight()/2;

    drawCoastLine(gw, GPoint(start_x, y), end_x - start_x, 0);

    return 0;
}

GPoint drawCoastLine(GWindow & gw, GPoint pt, double length, double theta, int level) {
    if (level == LEVEL_LIMIT) {
        return gw.drawPolarLine(pt, length, theta);
    }

    pt = drawCoastLine(gw, pt, length/3, theta, level+1);
    if (randomChance(0.5)) {
        pt = drawCoastLine(gw, pt, length/3, theta+60, level+1);
        pt = drawCoastLine(gw, pt, length/3, theta-60, level+1);
    } else {
        pt = drawCoastLine(gw, pt, length/3, theta-60, level+1);
        pt = drawCoastLine(gw, pt, length/3, theta+60, level+1);
    }

    return drawCoastLine(gw, pt, length/3, theta, level+1);
}
