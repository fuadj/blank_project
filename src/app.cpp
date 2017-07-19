#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <string>
#include "vector.h"
#include "grid.h"
using namespace std;

void fillGrid(Grid<int> & grid, Vector<int> & values);
bool isMagicSquare(Grid<int> & matrix);

int main() {
    Grid<int> matrix(3, 3);
    Vector<int> values;
    values += 1, 2, 3;
    values += 4, 5, 6;
    values += 7, 8, 9;
    fillGrid(matrix, values);
    cout << "The matrix is " << (isMagicSquare(matrix) ? "Magic" : "Imagic") << endl;
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

bool isMagicSquare(Grid<int> & matrix) {
    if (matrix.isEmpty() || (matrix.numCols() != matrix.numRows()))
        return false;

    bool did_sum = false;
    int prev_sum = 0;
    for (int row = 0; row < matrix.numRows(); row++) {
        int col_sum = 0;
        int row_sum = 0;
        for (int col = 0; col < matrix.numCols(); col++) {
            col_sum += matrix[row][col];
            row_sum += matrix[col][row];
        }
        if (col_sum != row_sum || (did_sum && prev_sum != col_sum))
            return false;
        did_sum = true;
        prev_sum = col_sum;
    }

    int diagonal_sum = 0;
    int inverse_diagonal_sum = 0;
    for (int i = 0; i < matrix.numRows(); i++) {
        diagonal_sum += matrix[i][i];
        inverse_diagonal_sum += matrix[matrix.numRows() - (i+1)][i];
    }
    if (diagonal_sum != inverse_diagonal_sum || (diagonal_sum != prev_sum))
        return false;
    return true;
}
