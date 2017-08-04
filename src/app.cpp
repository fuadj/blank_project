#include <cmath>
#include "gwindow.h"
#include "point.h"
#include "grid.h"
#include "random.h"
#include "gobjects.h"
#include "console.h"

using namespace std;

void drawChessBackground(GWindow & gw, GRectangle & rect);
double cellSizeForRect(GRectangle & rect);

bool placeQueens(GWindow &gw, GRectangle &rect, Grid<bool> & queens, int col);

const int ANIMATION_SPEED = 50;
const int N_CELLS = 8;

int main() {
    GWindow gw(1000, 700);
    Grid<bool> queens(N_CELLS, N_CELLS, false);

    double width = gw.getWidth();
    double height = gw.getHeight();
    double x = width * 0.3;
    double y = width * 0.1;
    GRectangle rect = GRectangle(x, y, width-2.0*x, height-2.0*y);

    drawChessBackground(gw, rect);

    placeQueens(gw, rect, queens, 0);

    return 0;
}

string colorForCell(int row, int col) {
    return ((row + col) % 2 == 0) ? "white" : "#bbbbbb";
}

void drawChessBackground(GWindow & gw, GRectangle & rect) {
    double cell_size = cellSizeForRect(rect);

    for (int i = 0; i < N_CELLS; i++) {
        for (int j = 0; j < N_CELLS; j++) {
            double x = ceil(rect.getX() + double(i) * cell_size);
            double y = ceil(rect.getY() + double(j) * cell_size);

            GRect *cell = new GRect(cell_size, cell_size);
            cell->setFilled(true);
            cell->setColor(colorForCell(i, j));
            gw.draw(cell, x, y);
            gw.remove(cell);
            delete cell;
        }
    }
    gw.setColor("black");
    // draw outer "enclosure"
    gw.drawRect(rect.getX(), rect.getY(), ceil(cell_size * N_CELLS), ceil(cell_size * N_CELLS));
}

double cellSizeForRect(GRectangle & rect) {
    return std::min(rect.getWidth()/N_CELLS, rect.getHeight()/N_CELLS);
}

void drawQueen(GWindow &gw, GRectangle &rect, int row, int col, bool place) {
    double cell_size = cellSizeForRect(rect);
    double margin = 0.15 * cell_size;

    double x = ceil(rect.getX() + double(col) * cell_size);
    double y = ceil(rect.getY() + double(row) * cell_size);

    if (place) {
        gw.setColor("blue");
        gw.fillOval(x+margin, y+margin, cell_size-2*margin, cell_size-2*margin);
    } else {
        gw.setColor(colorForCell(row, col));
        gw.fillRect(x+margin, y+margin, cell_size-2*margin, cell_size-2*margin);
    }
}

bool canPlaceQueen(Grid<bool> & queens, int row, int col) {
    if (queens[row][col]) return false;

    for (int i = 0; i < N_CELLS; i++) {
        if (queens[i][col]) return false;		// vertical
        if (queens[row][i]) return false;		// horizontal
    }

    int r = row, c = col;
    while (r > 0 && c > 0) { // top-left diagonal
        r--; c--;
    }
    while (r < N_CELLS && c < N_CELLS)
        if (queens[r++][c++]) return false;

    r = row; c = col;
    while (r < (N_CELLS-1) && c > 0) { 		// top-right diagonal
        r++; c --;
    }

    while (r > 0 && c < N_CELLS)
        if (queens[r--][c++]) return false;

    return true;
}

bool placeQueens(GWindow &gw, GRectangle &rect, Grid<bool> & queens, int col) {
    if (col >= queens.numCols()) return true;		// we've finished

    for (int row = 0; row < N_CELLS; row++) {
        if (canPlaceQueen(queens, row, col)) {
            queens[row][col] = true;
            drawQueen(gw, rect, row, col, true);
            pause(ANIMATION_SPEED);
            if (placeQueens(gw, rect, queens, col + 1))
                return true;
            queens[row][col] = false;
            drawQueen(gw, rect, row, col, false);
        }
    }

    return false;
}
