#include <cmath>
#include "gwindow.h"
#include "maze.h"
#include "point.h"
#include "console.h"
#include "grid.h"
#include "random.h"

using namespace std;

void fillRegion(GWindow &gw, const GRectangle & rect, Grid<bool> &pixels, int row, int col);
void drawCell(GWindow &gw, const GRectangle & rect, Grid<bool> &grid, int row, int col);
void drawGrid(GWindow &gw, const GRectangle & rect, Grid<bool> &grid);

const int N_ROWS = 23;
const int N_COLS = 19;
const int ANIMATION_SPEED = 50;

void initGridPic(Grid<bool> & grid) {
    for (int row = 9; row < N_ROWS; row++) {
        grid[row][0] = true;			// left wall
        grid[row][N_COLS-1] = true;		// right wall
    }
    for (int col = 0; col < N_COLS; col++)
        grid[N_ROWS-1][col] = true;		// bottom floor
    for (int row = 9, col = 0; row >= 0; row--, col++) {
        grid[row][col] = true;		// left ceiling
    }
    for (int row = 0, col = 9; row <= 9; row++, col++) {
        grid[row][col] = true;		// right ceiling
    }

    // the windows
    for (int i = 0; i < 4; i++) {
        // verticals
        grid[10 + i][3] = true;
        grid[10 + i][6] = true;
        grid[10 + i][12] = true;
        grid[10 + i][15] = true;

        // horizontals
        grid[10][3+i] = true;
        grid[10][12+i] = true;
        grid[13][3+i] = true;
        grid[13][12+i] = true;
    }

    // door vertical
    for (int i = 0; i < 6; i++) {
        grid[16+i][7] = true;
        grid[16+i][11] = true;
    }
    for (int i = 0; i < 5; i++)
        grid[16][7+i] = true;
}

int main() {
    GWindow gw(1000, 700);
    Grid<bool> grid(23, 19, false);

    initGridPic(grid);
    double width = gw.getWidth();
    double height = gw.getHeight();
    double x = width * 0.4;
    double y = width * 0.1;
    GRectangle rect = GRectangle(x, y, width-2.0*x, height-2.0*y);
    drawGrid(gw, rect, grid);
    fillRegion(gw, rect, grid, randomInteger(0, N_ROWS-1), randomInteger(0, N_COLS-1));
    return 0;
}

void fillRegion(GWindow &gw, const GRectangle & rect, Grid<bool> &pixels, int row, int col) {
    if (row < 0 || row >= pixels.numRows()) return;
    if (col < 0 || col >= pixels.numCols()) return;
    if (pixels[row][col] == true) return;		// if it is black

    pixels[row][col] = true;
    pause(ANIMATION_SPEED);
    gw.setColor("blue");
    drawCell(gw, rect, pixels, row, col);
    fillRegion(gw, rect, pixels, row-1, col);
    fillRegion(gw, rect, pixels, row+1, col);
    fillRegion(gw, rect, pixels, row, col-1);
    fillRegion(gw, rect, pixels, row, col+1);
}

void drawCell(GWindow &gw, const GRectangle & rect, Grid<bool> &grid, int row, int col) {
    double size = std::min((rect.getWidth()/N_COLS), (rect.getHeight()/N_ROWS));
    double margin = 0.15 * size;
    double cell_x = rect.getX() + col * size + margin;
    double cell_y = rect.getY() + row * size + margin;

    if (grid[row][col]) {		// filled
        gw.fillOval(cell_x, cell_y, size - margin, size - margin);
    } else {
        gw.drawOval(cell_x, cell_y, size - margin, size - margin);
    }
}

void drawGrid(GWindow &gw, const GRectangle & rect, Grid<bool> &grid) {
    gw.setColor("white");
    gw.fillRect(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
    gw.setColor("black");
    for (int row = 0; row < grid.numRows(); row++) {
        for (int col = 0; col < grid.numCols(); col++) {
            drawCell(gw, rect, grid, row, col);
        }
    }
}
