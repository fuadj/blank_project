#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "maze.h"
#include "point.h"

using namespace std;

bool solveMaze(Maze & maze, Point start, int level);
Point adjacentPoint(Point start, Direction dir);

const int ANIMATION_TIME = 5;
int main() {
    GWindow gw(1000, 700);
    Maze maze("maze.txt");
    double margin = std::max(0.10*gw.getWidth(), 0.10*gw.getHeight());
    maze.setWindow(&gw, margin, margin,
                   gw.getWidth() - 2.0*margin, gw.getHeight() - 2.0*margin);
    maze.draw();
    solveMaze(maze, maze.getStartPosition(), 0);
    return 0;
}

const double COLOR_DEGRADING_FACTOR = 0.65;
int levelColor(Maze & maze, int level) {
    int possible_levels = maze.numCols() * maze.numRows();
    int red = 0xff & int(255 - 255.0*(pow(double(level) / possible_levels, COLOR_DEGRADING_FACTOR)));
    return red << 16;
}

bool solveMaze(Maze & maze, Point start, int level) {
    pause(ANIMATION_TIME);
    if (maze.isOutside(start))
        return true;
    if (maze.isMarked(start))
        return false;
    maze.markSquare(start);
    maze.drawMark(start, levelColor(maze, level));
    for (Direction dir = NORTH; dir <= WEST; dir++) {
        if (!maze.wallExists(start, dir)) {
            Point neighbour = adjacentPoint(start, dir);
            if (solveMaze(maze, neighbour, level + 1)) {
                return true;
            }
        }
    }
    /*
    */
    maze.unmarkSquare(start);
    maze.eraseMark(start);
    return false;
}

Point adjacentPoint(Point start, Direction dir) {
    switch (dir) {
    case NORTH: return Point(start.getX(), start.getY() + 1);
    case EAST: 	return Point(start.getX() + 1, start.getY());
    case SOUTH: return Point(start.getX(), start.getY() - 1);
    case WEST: 	return Point(start.getX() - 1, start.getY());
    default: 	return start;
    }
}
