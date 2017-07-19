#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <string>
#include "vector.h"
#include "grid.h"
using namespace std;

void fillGrid(Grid<int> & grid, Vector<int> & values);

int main() {
    Grid<int> matrix(3, 3);
    Vector<int> values;
    values += 1, 2, 3;
    values += 4, 5, 6;
    values += 7, 8, 9;
    fillGrid(matrix, values);
    cout << "The Grid: " << matrix.toString() << endl;
    return 0;
}

void fillGrid(Grid<int> & grid, Vector<int> & values) {
    int filled = 0;
    for (int row = 0; row < grid.numRows(); row++) {
        for (int col = 0; col < grid.numCols(); col++) {
            if (filled++ == values.size())
                return;

            grid[row][col] = values[row * grid.numRows() + col];
        }
    }
}
