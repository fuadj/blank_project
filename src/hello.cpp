#include <iostream>
#include <string>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;

int WIDTH = 500;
int HEIGHT = 300;

int X_BUFFER = 40;

int X_START = -1 * X_BUFFER;

int OVAL_HEIGHT = int(1.2 * double(HEIGHT));
int OVAL_WIDTH = WIDTH + 2 * X_BUFFER;

int BAND_HEIGHT = 20;


int main() {
    GWindow window(WIDTH, HEIGHT);

    window.setWindowTitle("Sample Project");

    window.setColor("cyan");
    window.fillRect(0, 0, WIDTH, HEIGHT);

    Vector<string> colors;
    colors.add("red");
    colors.add("orange");
    colors.add("yellow");
    colors.add("green");
    colors.add("blue");
    colors.add("magenta");
    colors.add("magenta");

    int Y_OFFSET = HEIGHT - (int(OVAL_HEIGHT/3) + colors.size() * BAND_HEIGHT);

    for (int i = 0; i < colors.size(); i++) {
        window.setColor(colors.get(i));
        window.fillOval(X_START, Y_OFFSET + i * BAND_HEIGHT, OVAL_WIDTH, OVAL_HEIGHT);
    }
    window.setColor("cyan");
    window.fillOval(X_START, Y_OFFSET + (colors.size() - 1) * BAND_HEIGHT, OVAL_WIDTH, OVAL_HEIGHT);

    window.setVisible(true);

    window.requestFocus();
    //pause(3000);

    getLine("Press [Enter] to close the window... ");
    window.requestFocus();
    window.close();
    exitGraphics();

    return 0;
}
