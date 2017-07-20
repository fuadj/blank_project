#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <string>
#include "vector.h"
#include "grid.h"
#include "math.h"
using namespace std;

void fillGrid(Grid<bool> & grid, Vector<bool> & values);

void fixCounts(Grid<bool> & locations, Grid<int> & counts);

#define T true
#define F false

int main() {
    Grid<int> counts;
    Grid<bool> mine(6, 6);
    Vector<bool> row_mines;

    row_mines += T, F, F, F, F, T;
    row_mines += F, F, F, F, F, T;
    row_mines += T, T, F, T, F, T;
    row_mines += T, F, F, F, F, F;
    row_mines += F, F, T, F, F, F;
    row_mines += F, F, F, F, F, F;

    fillGrid(mine, row_mines);
    fixCounts(mine, counts);

    cout << "The Mine: " << endl << mine.toString2D() << endl;
    cout << "Counted Mine: " << endl << counts.toString2D() << endl;

    return 0;
}

void fillGrid(Grid<bool> & grid, Vector<bool> & values) {
    int filled = 0;
    for (int row = 0; row < grid.numRows(); row++) {
        for (int col = 0; col < grid.numCols(); col++) {
            if (filled++ == values.size())
                return;

            grid[row][col] = values[row * grid.numRows() + col];
        }
    }
}

void fixCounts(Grid<bool> & locations, Grid<int> & counts) {
    counts.resize(locations.numRows(), locations.numCols());

    int NUM_ROWS = locations.numRows();
    int NUM_COLS = locations.numCols();

    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            int start_row = max(0, row - 1), end_row = min(NUM_ROWS - 1, row + 1);
            int start_col = max(0, col - 1), end_col = min(NUM_COLS - 1, col + 1);

            int cell_count = 0;
            for (int i = start_row; i <= end_row; i++) {
                for (int k = start_col; k <= end_col; k++) {
                    cell_count += (locations[i][k] ? 1 : 0);
                }
            }
            counts[row][col] = cell_count;
        }
    }
}
