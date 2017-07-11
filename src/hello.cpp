#include <iostream>
#include <string>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;

int SIZE = 500;

int OUTER_DIAMETER = int(0.75 * double(SIZE));
int OUTER_RADIUS = int(OUTER_DIAMETER / 2);

int EDGE_OFFSET = (SIZE - OUTER_DIAMETER) / 2;

int INNER_RADIUS = int(0.166666667 * double(OUTER_RADIUS));

int main() {
    GWindow window(SIZE, SIZE);

    window.setWindowTitle("Yin-Yang");

    window.setColor("white");
    window.fillRect(0, 0, SIZE, SIZE);

    // draw the outer circle
    window.setColor("black");
    window.fillOval(EDGE_OFFSET, EDGE_OFFSET, OUTER_DIAMETER, OUTER_DIAMETER);

    // draw the left semi cirle with the inside white
    window.setColor("white");
    window.fillRect(EDGE_OFFSET, EDGE_OFFSET, OUTER_DIAMETER/2, OUTER_DIAMETER);
    window.setColor("black");	// draw the left edge of the left side semi-circle
    window.drawOval(EDGE_OFFSET, EDGE_OFFSET, OUTER_DIAMETER, OUTER_DIAMETER);

    int upper_x = int(SIZE/2 - (OUTER_DIAMETER / 4));
    int upper_y = EDGE_OFFSET + 1;
    int upper_size = int(OUTER_DIAMETER / 2) - 1;	// the -1 is so it just skimms the border(we don't want it to touch)

    int lower_x = upper_x;
    int lower_y = SIZE/2;
    int lower_size = upper_size;

    window.setColor("white");
    window.fillOval(upper_x, upper_y, upper_size, upper_size);
    window.setColor("black");
    window.fillOval(lower_x, lower_y, lower_size, lower_size);

    int inner_size = (OUTER_DIAMETER/6);
    int inner_x = SIZE/2 - (inner_size/2);
    int inner_upper_y = SIZE/2 - 2*(inner_size);
    int inner_lower_y = SIZE/2 + 1*(inner_size);

    window.setColor("black");
    window.fillOval(inner_x, inner_upper_y, inner_size, inner_size);
    window.setColor("white");
    window.fillOval(inner_x, inner_lower_y, inner_size, inner_size);

    window.setVisible(true);

    window.requestFocus();
    //pause(3000);

    getLine("Press [Enter] to close the window... ");
    window.requestFocus();
    window.close();
    exitGraphics();

    return 0;
}
