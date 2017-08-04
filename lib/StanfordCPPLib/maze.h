/* 
 * File: maze.h
 * ------------
 * Defines the Maze class.
 * Last modified Tue Jan 22 20:19:35 PST 2008 jzelenski
 */

#ifndef _maze_h
#define _maze_h

#include <ostream>
#include <string>
#include "grid.h"
#include "gwindow.h"
#include "direction.h"
#include "point.h"

class Maze {
public:
    Maze(int numRows, int numCols, bool hasWalls);
    Maze(std::string filename);

    void setWindow(GWindow * gw, double x, double y, double width, double height);

    Point getStartPosition();

    bool isOutside(Point pt);

    bool wallExists(Point pt, Direction dir);

    void markSquare(Point pt);
    void unmarkSquare(Point pt);

    bool isMarked(Point pt);

    int numRows();
    int numCols();

    bool pointInBounds(Point p);

    /*
    * Member function: isWall
    * Usage: if (maze.isWall(a, b))...
    * ---------------------------------
    * This member function returns true if there is a wall between
    * the two cells at points p1 and p2. If the two points are
    * not neighbors or if either is out of bounds, an error is raised.
    */
    bool isWall(Point p1, Point p2);

    /*
    * Member function: setWall
    * Usage: maze.setWall(a, b, true);
    * --------------------------------
    * This member function sets the wall between cells at points
    * p1 and p2 to state. It can be used to either add or remove
    * walls. The graphical display is updated to match. If the two
    * points are not neighbors or either point is out of bounds,
    * an error is raised.
    */
    void setWall(Point p1, Point p2, bool state);

    void draw();

    /*
    * Member function: drawMark
    * Usage: maze.drawMark(p, "Red");
    * ------------------------------
    * This member function draws a mark on the cell at point p
    * in the specified color. To erase a previous mark, you
    * can redraw one in white or use the draw function to reset
    * all marks.
    */
    void drawMark(Point p, std::string color);
    void drawMark(Point p, int color);
    void fillMark(Point p, int color, bool filled);
    void eraseMark(Point p);

private:
    struct MCell {
        bool walls[NUM_DIRS];
        bool isMarked;

        friend std::ostream & operator<<(std::ostream & os, const MCell & cell) {
        os << (cell.isMarked ? 'X' : 'O');
        os << "{";
        for (int i = 0; i < NUM_DIRS; i++) {
        if (i != 0) os << ", ";
        os << (cell.walls[i] ? 't' : 'f');
        }
        return os << "}";
        }
    };

    Grid<MCell> cells;

    GWindow * gw;

    double x, y;
    double width, height;
    double bottomX, bottomY, cellSize;

    Point startPosition;

    void initBoard(int numRows, int numCols, bool hasWalls);
    Direction neighborDir(Point p1, Point p2);
    void drawWallsForCell(Point p);

    void clearWindow();

    void checkWindowConfigured();
    bool windowConfigured;
};

#endif
