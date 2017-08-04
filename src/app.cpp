#include <cmath>
#include "gwindow.h"
#include "point.h"
#include "grid.h"
#include "random.h"
#include "gobjects.h"
#include "console.h"
#include "vector.h"

using namespace std;

void drawChessBackground(GWindow & gw, GRectangle & rect);
double cellSizeForRect(GRectangle & rect);

bool findKnightTour(GWindow &gw, GRectangle &rect, Grid<int> & board, int row, int col, int level);

const int ANIMATION_SPEED = 5;
const int N_CELLS = 8;
const int N_TOTAL = N_CELLS * N_CELLS;
const int EMPTY_CELL = -1;

Vector<Point> KNIGHT_MOVES;

int main() {
    GWindow gw(1000, 700);
    Grid<int> board(N_CELLS, N_CELLS, EMPTY_CELL);

    KNIGHT_MOVES += Point(1,-2), Point(2,-1), Point(2,1), Point(1,2), Point(-1, 2), Point(-2,1), Point(-2,-1), Point(-1,-2);

    double width = gw.getWidth();
    double height = gw.getHeight();
    double x = width * 0.3;
    double y = width * 0.1;
    GRectangle rect = GRectangle(x, y, width-2.0*x, height-2.0*y);

    drawChessBackground(gw, rect);

    findKnightTour(gw, rect, board, N_CELLS-1, 0, 0);
    //findKnightTour(gw, rect, board, randomInteger(0, N_CELLS-1), randomInteger(0, N_CELLS-1), 0);

    return 0;
}

string colorForCell(int row, int col) {
    return ((row + col) % 2 == 0) ? "white" : "#999999";
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

void drawKnight(GWindow &gw, GRectangle &rect, int knight, int row, int col, bool place) {
    double cell_size = cellSizeForRect(rect);
    double margin = 0.15 * cell_size;

    double x = ceil(rect.getX() + double(col) * cell_size);
    double y = ceil(rect.getY() + double(row) * cell_size);

    if (place) {
        gw.setColor("white");
        gw.fillOval(x+margin, y+margin, cell_size-2*margin, cell_size-2*margin);
        GLabel *label = new GLabel(integerToString(knight));
        label->setFont("Console-16");
        label->setColor("black");
        gw.draw(label,
                x + (cell_size/2 - label->getWidth()/2),
                y + (cell_size/2 + label->getFontAscent()/2));
        delete label;
    } else {
        gw.setColor(colorForCell(row, col));
        gw.fillRect(x+margin, y+margin, cell_size-2*margin, cell_size-2*margin);
    }
}

bool findKnightTour(GWindow &gw, GRectangle &rect, Grid<int> & board, int row, int col, int level) {
    if (level == N_TOTAL) return true;
    if ((row < 0 || col < 0) ||
            (row >= board.numRows() || col >= board.numCols()))
        return false;
    if (board[row][col] != EMPTY_CELL) return false;
    board[row][col] = level + 1;
    drawKnight(gw, rect, board[row][col], row, col, true);
    pause(ANIMATION_SPEED);

    //int move = randomInteger(0, KNIGHT_MOVES.size()-1);
    for (int i = 0; i < KNIGHT_MOVES.size(); i++) {
        if (findKnightTour(gw, rect, board,
                           row + KNIGHT_MOVES[i].getY(),
                           col + KNIGHT_MOVES[i].getX(),
                           level + 1))
            return true;
        //move = (move + 1) % (KNIGHT_MOVES.size());
    }
    board[row][col] = EMPTY_CELL;
    drawKnight(gw, rect, board[row][col], row, col, false);
    return false;
}
