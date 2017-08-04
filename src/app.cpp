#include <cmath>
#include "gwindow.h"
#include "point.h"
#include "grid.h"
#include "random.h"
#include "gobjects.h"
#include "console.h"
#include "vector.h"

using namespace std;

struct Graphics {
    GWindow *gw;
    GRectangle *rect;
    double cell_size;
    double margin;
};

enum GAME_STATE { LOST, WON, PLAYING };

struct Move {
    Point start, end;
};

const int N_CELLS = 7;
const int N_EDGE = 2;
const int ANIMATION_SPEED = 50;

const int PEG = 1;
const int HOLE = 2;
const int OUTSIDE = -1;

const int CENTER_X = 3, CENTER_Y = 3;

//This draws and initializes the board with the center being a hole and the rest pegs.
void drawInitialBoard(Graphics & gr, Grid<int> & board);
bool solvePegSolitaire(Graphics & gr, Grid<int> & board, int level);
void drawCell(Graphics & gr, Point pt, string color, bool is_filled);

int main() {
    GWindow gw(1000, 700);
    Grid<int> board(N_CELLS, N_CELLS);

    double width = gw.getWidth();
    double height = gw.getHeight();

    // we're using "floor" && "ceil" to prevent rounding error
    // b/c we will be repeatdly be drawing over cells.
    double x = floor(width * 0.3);
    double y = floor(height * 0.1);
    GRectangle rect = GRectangle(x, y,
                                 ceil(width-2.0*x),
                                 ceil(height-2.0*y));
    double size = std::min(rect.getWidth()/N_CELLS, rect.getHeight()/N_CELLS);

    Graphics gr;
    gr.gw = &gw;
    gr.rect = &rect;
    gr.cell_size = size;
    gr.margin = 0.1 * size;

    drawInitialBoard(gr, board);

    solvePegSolitaire(gr, board, 0);

    return 0;
}

void drawInitialBoard(Graphics & gr, Grid<int> & board) {
    double edge_size = gr.cell_size * N_EDGE;
    double non_edge = gr.cell_size * (N_CELLS - 2.0 * N_EDGE) + 2 * gr.margin;
    GPoint pt = gr.gw->drawPolarLine(gr.rect->getX() - gr.margin,
                                     (gr.rect->getY() + (N_EDGE * gr.cell_size)) - gr.margin,
                                     edge_size, 0);
    pt = gr.gw->drawPolarLine(pt, edge_size, 90);
    pt = gr.gw->drawPolarLine(pt, non_edge, 0);
    pt = gr.gw->drawPolarLine(pt, edge_size, -90);
    pt = gr.gw->drawPolarLine(pt, edge_size, 0);
    pt = gr.gw->drawPolarLine(pt, non_edge, -90);
    pt = gr.gw->drawPolarLine(pt, edge_size, 180);
    pt = gr.gw->drawPolarLine(pt, edge_size, -90);
    pt = gr.gw->drawPolarLine(pt, non_edge, 180);
    pt = gr.gw->drawPolarLine(pt, edge_size, 90);
    pt = gr.gw->drawPolarLine(pt, edge_size, 180);
    pt = gr.gw->drawPolarLine(pt, non_edge, 90);

    for (int r = 0; r < N_CELLS; r++) {
        for (int c = 0; c < N_CELLS; c++) {
            if (
                    (r < N_EDGE && c < N_EDGE) ||
                    (c >= (N_CELLS - N_EDGE) && r < N_EDGE) ||
                    (r >= (N_CELLS - N_EDGE) && c < N_EDGE) ||
                    (r >= (N_CELLS - N_EDGE) && c >= (N_CELLS - N_EDGE)))
                board[r][c] = OUTSIDE;
            else if (c == CENTER_X && r == CENTER_Y)
                board[r][c] = HOLE;
            else
                board[r][c] = PEG;

            if (board[r][c] != OUTSIDE) {
                int cell = board[r][c];
                if (cell == HOLE) {
                    drawCell(gr, Point(c, r), "white", false);
                } else {
                    drawCell(gr, Point(c, r), "black", true);
                }
            }
        }
    }
}

const string BLUE = "blue";

void animatePegMovement(Graphics & gr, Point start, Point mid, Point end, bool isReversing) {
    if (!isReversing) {
        drawCell(gr, start, "white", false);
        drawCell(gr, mid, "white", false);
        drawCell(gr, end, "blue", true);
    } else {
        drawCell(gr, start, "black", true);
        drawCell(gr, mid, "black", true);
        drawCell(gr, end, "white", false);
    }

    if (true)
        return;
    /*
    //attempt at trying to simulate movement, but it is fkn hard
    drawCell(gr, start, "white", false);
    pause(5);
    const int N_STEPS = 100;
    const int MID = N_STEPS/2;

    double x = gr.rect->getX() + gr.cell_size * start.getX();
    double y = gr.rect->getY() + gr.cell_size * start.getY();
    double dx = gr.cell_size * (end.getX() - start.getX());
    double dy = gr.cell_size * (end.getY() - start.getY());

    dx /= N_STEPS;
    dy /= N_STEPS;

    double circle_size = gr.cell_size - gr.margin;
    GOval *circle = new GOval(circle_size, circle_size);
    circle->setFilled(true);
    circle->setFillColor(BLUE);

    for (int i = 0; i < N_STEPS; i++) {
        if (i == MID) {
            if (isReversing) {

            } else {

            }
        }
        gr.gw->draw(circle, x, y);
        pause(2);
        gr.gw->setColor("white");		// overwrite the trail
        gr.gw->fillOval(x, y, circle_size, circle_size);
        x += dx; y += dy;
    }
    delete circle;
    drawCell(gr, end, "black", true);
    */
}

void applyMove(Graphics & gr, Grid<int> & board, Move move) {
    int mid_x = (move.start.getX() + move.end.getX())/2;
    int mid_y = (move.start.getY() + move.end.getY())/2;
    board[move.start.getY()][move.start.getX()] = HOLE;
    board[mid_y][mid_x] = HOLE;
    board[move.end.getY()][move.end.getX()] = PEG;
    animatePegMovement(gr, move.start, Point(mid_x, mid_y), move.end, false);
}

void reverseMove(Graphics & gr, Grid<int> & board, Move move) {
    int mid_x = (move.start.getX() + move.end.getX())/2;
    int mid_y = (move.start.getY() + move.end.getY())/2;
    board[move.start.getY()][move.start.getX()] = PEG;
    board[mid_y][mid_x] = PEG;
    board[move.end.getY()][move.end.getX()] = HOLE;
    animatePegMovement(gr, move.start, Point(mid_x, mid_y), move.end, true);
}

GAME_STATE findPossibleMoves(Grid<int> & board, Vector<Move> & moves) {
    moves.clear();

    Vector<Point> holes;
    int pegCount = 0;
    Point pegPoint;
    for (int row = 0; row < board.numRows(); row++) {
        for (int col = 0; col < board.numCols(); col++) {
            switch (board[row][col]) {
            case HOLE:
                holes.add(Point(col, row));
                break;
            case PEG:
                if (pegCount++ == 0) {
                    pegPoint = Point(col, row);
                }
                break;
            }
        }
    }

    if (pegCount == 1)
        return (pegPoint.getX() == CENTER_X && pegPoint.getY() == CENTER_Y) ? WON : LOST;

    for (Point hole : holes) {
        int r = hole.getY(), c = hole.getX();
        if ((c - 2 >= 0) &&
                (board[r][c-2] == PEG) &&
                (board[r][c-1] == PEG))
                moves.add(Move{Point(c-2, r), Point(c, r)});		// left-to-right
        if ((c + 2 < board.numCols()) &&
                (board[r][c+2] == PEG) &&
                (board[r][c+1] == PEG))
                moves.add(Move{Point(c+2, r), Point(c, r)});		// right-to-left
        if ((r - 2 >= 0) &&
                (board[r-2][c] == PEG) &&
                (board[r-1][c] == PEG))
                moves.add(Move{Point(c, r-2), Point(c, r)});		// top-to-bottom
        if ((r + 2 < board.numRows()) &&
                (board[r+2][c] == PEG) &&
                (board[r+1][c] == PEG))
                moves.add(Move{Point(c, r+2), Point(c, r)});		// bottom-to-top
    }

    return moves.size() > 0 ? PLAYING : LOST;
}

void drawCell(Graphics & gr, Point pt, string color, bool is_filled) {
    GWindow *window = gr.gw;
    GRectangle *rect = gr.rect;
    double size = gr.cell_size - gr.margin;
    int row = pt.getY();
    int col = pt.getX();

    if (is_filled) {
        window->setColor(color);
        window->fillOval(rect->getX() + (col * gr.cell_size + gr.margin),
                         rect->getY() + (row * gr.cell_size + gr.margin),
                         size, size);
    } else {
        window->setColor(color);
        window->fillOval(rect->getX() + (col * gr.cell_size + gr.margin),
                         rect->getY() + (row * gr.cell_size + gr.margin),
                         size, size);
        // draw "ring" around it
        window->setColor("black");
        window->drawOval(rect->getX() + (col * gr.cell_size + gr.margin),
                         rect->getY() + (row * gr.cell_size + gr.margin),
                         size, size);
    }
}

bool solvePegSolitaire(Graphics & gr, Grid<int> & board, int level) {
    Vector<Move> moves;

    pause(ANIMATION_SPEED);

    switch (findPossibleMoves(board, moves)) {
    case WON: return true;
    case LOST: return false;
    default: break;
    }

    for (Move move : moves) {
        applyMove(gr, board, move);
        if (solvePegSolitaire(gr, board, level + 1))
            return true;
        reverseMove(gr, board, move);
    }
    return false;
}
