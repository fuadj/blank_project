/* 
 * File: maze.cpp
 * --------------
 * A maze is mostly a grid of walls. plus a little drawing code.
 */

#include "maze.h"
#include "error.h"
#include "gtypes.h"
#include <cmath>
#include "filelib.h"
#include <stdio.h>

void Maze::initBoard(int numRows, int numCols, bool hasWalls) {
    startPosition = Point(0, 0);
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            for (int d = 0; d < NUM_DIRS; d++) {
                cells[r][c].walls[d] = hasWalls;
                cells[r][c].isMarked = false;
            }
        }
    }
}

Maze::Maze(int numRows, int numCols, bool hasWalls) : cells(numRows, numCols) {
    initBoard(numRows, numCols, hasWalls);
    windowConfigured = false;
}

bool isWallInDir(Vector<std::string> & lines, int i, int j, Direction dir) {
    switch(dir) {
    case NORTH:
        return lines[i - 1][j] != ' ';
    case EAST:
        return lines[i][j + 1] != ' ';
    case SOUTH:
        return lines[i + 1][j] != ' ';
    case WEST:
        return  lines[i][j - 1] != ' ';
    default:
        return true;
    }
}

bool isValidCell(Vector<std::string> & lines, int i, int j) {
    if (lines[i][j] != ' ')
        return false;

    if (lines[i][j-1] == '+' ||
            lines[i][j+1] == '+') // vertical passage
        return false;
    if (lines[i - 1][j] == '+' ||
            lines[i + 1][j] == '+') // horizontal passage
        return false;

    return true;
}

Maze::Maze(std::string filename) {
    windowConfigured = false;

    std::ifstream file;
    if (!openFile(file, filename)) {
        error("Error opening maze file: " + filename);
    }
    Vector<std::string> lines;
    readEntireFile(file, lines);
    file.close();

    if (lines.isEmpty())
        error("Maze file empty: " + filename);

    int numRows = 0, numCols = 0;
    for (int i = 0; i < lines.size(); i++) if (lines[i][0] != '+') numRows++;
    for (int i = 0; i < lines[0].length(); i++) {
        char ch = lines[0][i];
        if (ch != '\r' && ch != '+')
            numCols++;
    }

    cells.resize(numRows, numCols);

    initBoard(numRows, numCols, false);

    for (int i = lines.size() - 1, y = 0; i >= 0; i--) {
        if (lines[i][0] == '+') continue;

        for (int j = 0, x = 0; j < lines[i].length(); j++) {
            if (isValidCell(lines, i, j) || (toupper(lines[i][j]) == 'S')) {
                for (int dir = 0; dir < NUM_DIRS; dir++)
                    cells[y][x].walls[dir] = isWallInDir(lines, i, j, Direction(dir));

                if (lines[i][j] == 'S') {  //starting position
                    startPosition = Point(x, y);
                }
                x++;
            }
        }
        y++;
    }
}

void Maze::setWindow(GWindow *gw, double x, double y, double width, double height) {
    this->gw = gw;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    cellSize = std::min(width/numCols(), height/numRows());
    bottomX = x + (width - numCols()*cellSize)/2;
    bottomY = y + height - (height - numRows()*cellSize)/2;
    windowConfigured = true;
}

int Maze::numRows() {
    return cells.numRows();
}

int Maze::numCols() {
    return cells.numCols();
}

bool Maze::pointInBounds(Point p) {
    return (p.getX() >= 0 && p.getX() < numCols() && p.getY() >=0 && p.getY() < numCols());
}

void Maze::clearWindow() {
    checkWindowConfigured();

    std::string save_color = gw->getColor();
    gw->setColor("white");
    gw->fillRect(x, y, width, height);
    gw->setColor(save_color);
}

bool Maze::isWall(Point p1, Point p2) {
    if (!pointInBounds(p1) || !pointInBounds(p2))
        error("PointT is not in bounds for maze");
    return cells[p1.getY()][p1.getX()].walls[neighborDir(p1, p2)];
}

void Maze::setWall(Point p1, Point p2, bool state) {
    if (!pointInBounds(p1) || !pointInBounds(p2))
        error("PointT is not in bounds for maze");
    cells[p1.getY()][p1.getX()].walls[neighborDir(p1, p2)] = state;
    cells[p2.getY()][p2.getX()].walls[neighborDir(p2, p1)] = state;
}

void Maze::draw() {
    clearWindow();
    for (int r = 0; r < cells.numRows(); r++) {
        for (int c = 0; c < cells.numCols(); c++) {
            drawWallsForCell(Point(c, r));
        }
    }
}

const double SQRT_OF_2 = pow(2, 0.5);

void Maze::drawMark(Point p, std::string color) {
    checkWindowConfigured();
    if (!pointInBounds(p))
        error("PointT is not in bounds for maze");

    double margin = cellSize*.2;
    double length = cellSize - 2*margin;
    gw->setColor(color);
    gw->drawPolarLine(bottomX + p.getX()*cellSize + margin,
                      bottomY - (p.getY()*cellSize + margin),
                      SQRT_OF_2 * length, 45);
    gw->drawPolarLine(bottomX + p.getX()*cellSize + margin,
                      bottomY - (p.getY()*cellSize + cellSize - margin),
                      SQRT_OF_2 * length, -45);
}

Direction Maze::neighborDir(Point p1, Point p2) {
    if ((abs(p1.getY()-p2.getY()) + abs(p1.getX()-p2.getX())) != 1)
        error("Points are not neighbors");
    if (p1.getY() != p2.getY())
        return (p1.getY() < p2.getY() ? NORTH : SOUTH);
    else
        return (p1.getX() < p2.getX() ? EAST : WEST);
}

void Maze::drawWallsForCell(Point p) {
    checkWindowConfigured();

    gw->setColor(cells[p.getY()][p.getX()].walls[SOUTH] ? "Black" : "White");
    GPoint pt = gw->drawPolarLine(bottomX + p.getX()*cellSize,
                                 bottomY - p.getY()*cellSize,
                                 cellSize, 0);
    gw->setColor(cells[p.getY()][p.getX()].walls[EAST] ? "Black" : "White");
    pt = gw->drawPolarLine(pt, cellSize, 90);
    gw->setColor(cells[p.getY()][p.getX()].walls[NORTH] ? "Black" : "White");
    pt = gw->drawPolarLine(pt, cellSize, 180);
    gw->setColor(cells[p.getY()][p.getX()].walls[WEST] ? "Black" : "White");
    pt = gw->drawPolarLine(pt, cellSize, -90);
}

Point Maze::getStartPosition() {
    return startPosition;
}

bool Maze::isOutside(Point pt) {
    return !pointInBounds(pt);
}

bool Maze::wallExists(Point pt, Direction dir) {
    return cells[pt.getY()][pt.getX()].walls[dir];
}

void Maze::markSquare(Point pt) {
    cells[pt.getY()][pt.getX()].isMarked = true;
}

void Maze::unmarkSquare(Point pt) {
    cells[pt.getY()][pt.getX()].isMarked = false;
}

bool Maze::isMarked(Point pt) {
    return cells[pt.getY()][pt.getX()].isMarked;
}

void Maze::checkWindowConfigured() {
    if (!windowConfigured)
        error("Maze::setWindow() not called");
}
