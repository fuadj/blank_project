#include <iostream>
#include <string>
#include "vector.h"
#include "gwindow.h"
#include <unistd.h>
#include "spike.h"

using namespace std;

struct Move {
    int src, dest;
    int plate;

    Move(){}
    Move(int s, int d, int p): src(s), dest(d), plate(p) {}
};

void towersOfHannoi(int n, int source, int dest, int temp, Vector<Move> & moves);
void sendPlateAcrossHighway(GWindow * gw, int source, int dest, int plateWidth);


const int TOWER_HEIGHT = 10;
const int WIDTH = 600;
const int HEIGHT = 500;

const int BASE_Y = int(double(HEIGHT) * 0.9);
const int POLE_HEIGHT = (Spike::PLATE_BUFFER + Spike::PLATE_HEIGHT) * (TOWER_HEIGHT + 1);
const int HIGHWAY = int(double(POLE_HEIGHT) * 1.3);

void initSpikes(Vector<Spike> & spikes, GWindow * gw) {
    spikes.clear();
    spikes.push_back(Spike());		// dummy place holder. We want 1-based indexing
    for (int i = 1; i <= 3; i++) {
        int base_x = int(i * double(gw->getWidth()) / 4);
        spikes.push_back(Spike(gw,
                          Vector<int>(), // it starts out empty, we push plates to it
                          base_x, BASE_Y, POLE_HEIGHT, HIGHWAY));
        spikes[i].drawSpike();
    }
}

int main() {
    int SOURCE = 1;
    int DEST = 2;
    int TEMP = 3;

    GWindow gw(WIDTH, HEIGHT);
    Vector<Move> moves;

    Vector<Spike> spikes;

    initSpikes(spikes, &gw);
    for (int i = TOWER_HEIGHT; i >= 1; i--) // "build-up" the first(source) tower
        spikes[SOURCE].pushPlate(i);

    towersOfHannoi(TOWER_HEIGHT, SOURCE, DEST, TEMP, moves);

    for (Move move : moves) {
        spikes[move.src].popPlate();
        sendPlateAcrossHighway(&gw, move.src, move.dest, move.plate);
        spikes[move.dest].pushPlate(move.plate);
    }

    return 0;
}

void towersOfHannoi(int n, int source, int dest, int temp, Vector<Move> & moves) {
    if (n != 0) {
        towersOfHannoi(n-1, source, temp, dest, moves);
        moves.push_back(Move{source, dest, n});
        towersOfHannoi(n-1, temp, dest, source, moves);
    }
}

void sendPlateAcrossHighway(GWindow * gw, int source, int dest, int plateWidth) {
    const int MOVE_X = int(double(Spike::PLATE_HEIGHT) * 0.75);		// this needs to be tied-in with the place height

    int dir = (dest > source) ? 1 : -1;
    int start_y = BASE_Y - HIGHWAY - (Spike::PLATE_HEIGHT + Spike::PLATE_BUFFER);

    int start_x = int(WIDTH * double(source) / 4);
    int end_x = int(WIDTH * double(dest) / 4);

    int num_moves = abs((end_x - start_x) / MOVE_X);

    int scaled_plate_width = Spike::PLATE_WIDTH * plateWidth;

    start_x -= dir * (scaled_plate_width / 2);
    end_x += dir * (scaled_plate_width / 2);

    string save_color = gw->getColor();
    for (int i = 0; i < num_moves; i++) {
        if (i != 0) {		// after first move, clear the previous trail
            gw->setColor("white");
            gw->fillRect(start_x + (dir * (i - 1) * MOVE_X), start_y, scaled_plate_width, Spike::PLATE_HEIGHT);
        }
        gw->setColor(Spike::PLATE_COLOR);
        gw->fillRect(start_x + dir * (i * MOVE_X), start_y, scaled_plate_width, Spike::PLATE_HEIGHT);
        usleep(Spike::ANIMATION_SPEED);
    }

    // clear-out the last trail
    gw->setColor("white");
    gw->fillRect(start_x + (dir * (num_moves - 1) * MOVE_X), start_y, scaled_plate_width, Spike::PLATE_HEIGHT);

    gw->setColor(save_color);
}
