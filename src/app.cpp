#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise
#include <iomanip>
#include "gwindow.h"
#include "vector.h"
#include "gtypes.h"
#include "error.h"
#include <sstream>
#include "random.h"

using namespace std;

void findCornerPoints(GWindow & gw, Vector<GPoint> & points, int n_across, int n_down) {
    int WINDOW_WIDTH = gw.getWidth();
    int WINDOW_HEIGHT = gw.getHeight();

    int left = 10, right = WINDOW_WIDTH - 10;
    int top = 10, bottom = WINDOW_HEIGHT - 10;

    int width = right - left;
    int height = bottom - top;

    int x, y;

#define GOING_DOWN 	0
#define GOING_UP 	1

    points.clear();

    for (int dir = GOING_DOWN; dir <= GOING_UP; dir++) {
        for (int i = 0; i <= n_down; i++) {
            int delta_y = int(double(i * height) / n_down);
            if (dir == GOING_DOWN) {
                x = right;
                y = top + delta_y;
            } else {
                x = left;
                y = bottom - delta_y;
            }
            points.add(GPoint(x, y));
        }

        for (int i = 1; i <= (n_across - 2); i++) {
            int delta_x = int(double(i * width) / (n_across - 1));
            if (dir == GOING_DOWN) {
                y = bottom;
                x = right - delta_x;
            } else {
                y = top;
                x = left + delta_x;
            }
            points.add(GPoint(x, y));
        }
    }
}

int main() {
    GWindow gw;
    Vector<GPoint> points;

    const int N_ACROSS = 50;
    //const int N_ACROSS = 57;
    const int N_DOWN = 30;
    const int DELTA = 67;
    //const int DELTA = 97;

    findCornerPoints(gw, points, N_ACROSS, N_DOWN);

    //cout << "Num pts " << points.size() << endl;

    GRectangle screen(0, 0, gw.getWidth(), gw.getHeight());
    for (int i = 0; i < points.size(); i++) {
        if (!screen.contains(points[i])) {
            ostringstream err_msg;
            err_msg << i << "  " << setprecision(2) << double(i)/points.size() << "% ";
            err_msg << "The point " + points[i].toString() + " isn't in the screen " + screen.toString();
            error(err_msg.str());
        }
    }

    int START_R = 74, 	END_R = 255;
    int START_G = 120, 	END_G = 200;
    int START_B = 230, 	END_B = 55;

    int start_pt = 0;
    for (int i = 0; ; i++) {
        double d = double(i) / points.size();
        if (d > 1) d = 1 / d;

        int red = 0xff & int(d * (END_R - START_R) + START_R);
        int green = 0xff & int(d * (END_G - START_G) + START_G);
        int blue = 0xff & int(d * (END_B - START_B) + START_B);

        int color = (red << 16 | green << 8 | blue);
        gw.setColor(color);
        /*
        cout << right << setw(3) << i;
        cout << "\t" << setw(3) << setprecision(3) << d;
        cout << "\tred " << setw(3) << red;
        cout << "\tgreen " << setw(3) << green;
        cout << "\tblue " << setw(3) << blue;
        cout << "\tcolor " << setw(7) << color << endl;
        */

        int end_pt = (start_pt + DELTA) % points.size();
        //int end_pt = randomInteger(0, points.size() - 1);

        gw.drawLine(points[start_pt], points[end_pt]);
        start_pt = end_pt;
        if (start_pt == 0) break;
    }

    return 0;
}
