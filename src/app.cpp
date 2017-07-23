#include <iostream>
#include "console.h" // This NEEDS to be included, it WON'T compile otherwise

using namespace std;

int cannonBall(int height);

int main() {
    for (int i = 1; i <= 4; i++) {
        cout << "Cannon Height " << i << " total balls " << cannonBall(i) << endl;
    }
    return 0;
}

int cannonBallLevels(int height, int & ballCount) {
    if (height <= 1)  {
        ballCount++;
        return 1;
    }

    int upperLevel = cannonBallLevels(height - 1, ballCount);

    int currentLevel = upperLevel + (2 * height - 1);
    ballCount += currentLevel;

    return currentLevel;
}

int cannonBall(int height) {
    int ballCount = 0;

    cannonBallLevels(height, ballCount);

    return ballCount;
}
