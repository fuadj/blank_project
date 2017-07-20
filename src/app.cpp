#include "console.h" // "console.h" needs to be included to work with StanfordLib, it otherwise WON'T compile
#include <iostream>
#include <iomanip>
#include "vector.h"
#include "queue.h"
#include "random.h"
#include "simpio.h"
#include "grid.h"
using namespace std;

const int GRID_SIZE = 25;

const int MIN_AIR_TIME = 1;
const int MAX_AIR_TIME = 4;
const int NUM_BALLS_SPRUNG = 2;

void runMouseTrapSimulation(Grid<bool> & grid, int & nTimePassed, int & maxBallsInAir);
void printMouseTrapReport(Grid<bool> & grid, int nTimePassed, int maxBallsInAir);

int main() {
    Grid<bool> grid(GRID_SIZE, GRID_SIZE, true);
    int nTimePassed;
    int maxBallsInAir;

    runMouseTrapSimulation(grid, nTimePassed, maxBallsInAir);
    printMouseTrapReport(grid, nTimePassed, maxBallsInAir);

    return 0;
}

void runMouseTrapSimulation(Grid<bool> & grid, int & nTimePassed, int & maxBallsInAir) {
    Vector<int> ballsInAir;

    nTimePassed = 0;
    maxBallsInAir = 0;
    ballsInAir.add(0);		// add a single ball to start the reaction

    while (!ballsInAir.isEmpty()) {
        for (int i = 0; i < ballsInAir.size(); ) {
            nTimePassed++;

            if (ballsInAir[i] == 0) {
                ballsInAir.remove(i);		// the ball has landed

                int col = randomInteger(0, grid.numCols() - 1);
                int row = randomInteger(0, grid.numRows() - 1);
                if (grid[row][col]) {
                    grid[row][col] = false;

                    for (int k = 0; k < NUM_BALLS_SPRUNG; k++)
                        ballsInAir.add(randomInteger(MIN_AIR_TIME, MAX_AIR_TIME));

                    maxBallsInAir = max(maxBallsInAir, ballsInAir.size());
                }
            } else {
                ballsInAir[i]--;
                i++;
            }
        }
    }

}

void printMouseTrapReport(Grid<bool> & grid, int nTimePassed, int maxBallsInAir) {
    cout << "Simulation results for grid of size [" << grid.numRows() << ", " << grid.numCols() << "]" << endl;
    int grid_size = grid.numCols() * grid.numRows();
    int num_exploded = 0;
    for (bool cell : grid) {
        if (!cell) num_exploded++;
    }

    cout << endl << grid.toString2D() << endl;
    cout << "Num exploded " << num_exploded << endl;
    cout << "Percentage survived " << double(grid_size - num_exploded)/grid_size << endl;
    cout << "Time taken to stabilize " << nTimePassed << endl;
    cout << "Max # of balls in the air " << maxBallsInAir << endl;
}
