#ifndef _hanoi_spike_h
#define _hanoi_spike_h

#include "gwindow.h"
#include "vector.h"
#include "error.h"
#include <string>

class Spike {
public:
    const static int BASE_COLOR = 0xff000000;	// black
    const static int POLE_COLOR = 0xff888888;	// grey
    const static int PLATE_COLOR = 0xffdd0000;	// redish

    const static int PLATE_WIDTH = 11;
    const static int PLATE_HEIGHT = 8;
    const static int PLATE_BUFFER = 3;

    const static int BASE_WIDTH = 120;
    const static int BASE_HEIGHT = 8;
    const static int POLE_WIDTH = 3;

    const static int ANIMATION_SPEED = 100000;		// in micro-seconds

    Spike() {
    }

    Spike(GWindow * gw, const Vector<int> & initialPlates, int x, int y, int height, int highway) {
        initSpike(gw, initialPlates, x, y, height, highway);
    }

    void drawSpike() {
        drawBase();
        drawPlates(plates.size());
        drawPole();
    }

    void popPlate() {
        if (plates.isEmpty())
            error("Trying to pop an empty spike");
        animatePlate(true, plates.size() - 1, plates[plates.size() - 1]);
        plates.remove(plates.size() - 1);
    }

    void pushPlate(int plate_width) {
        animatePlate(false, plates.size(), plate_width);
        plates.push_back(plate_width);
    }

private:
    void initSpike(GWindow * gw, const Vector<int> & initialPlates, int x, int y, int height, int highway) {
        this->gw = gw;
        plates = initialPlates;
        base_x = x; base_y = y;
        poleHeight = height;
        highwayHeight = highway;
    }

    void drawBase() {
        std::string save = gw->getColor();
        gw->setColor(BASE_COLOR);
        gw->fillRect(base_x - (BASE_WIDTH/2), base_y - BASE_HEIGHT, BASE_WIDTH, BASE_HEIGHT);
        gw->setColor(save);
    }

    void drawPole() {
        std::string save = gw->getColor();
        gw->setColor(POLE_COLOR);
        gw->fillRect(base_x - (POLE_WIDTH / 2), (base_y - BASE_HEIGHT) - poleHeight, POLE_WIDTH, poleHeight);
        gw->setColor(save);
    }

    // @param platesBelow		# of plates below the plate to draw
    void drawPlate(int platesBelow, int width) {
        width = PLATE_WIDTH * width;
        int plate_x = base_x - width/2;
        int plate_y = (base_y - BASE_HEIGHT) - (platesBelow + 1) * (PLATE_HEIGHT + PLATE_BUFFER);
        std::string save = gw->getColor();
        gw->setColor(PLATE_COLOR);
        gw->fillRect(plate_x, plate_y, width, PLATE_HEIGHT);
        gw->setColor(save);
    }

    void drawPlates(int numPlates) {
        for (int i = 0; i < numPlates; i++)
            drawPlate(i, plates[i]);
    }

    // Clears the space b/n the top plate and the "highway"
    void clearTopRegion(int platesBelow) {
        int width = BASE_WIDTH;
        int x = base_x - width / 2;
        int y = base_y - (BASE_HEIGHT + highwayHeight);
        int height = highwayHeight - (platesBelow * (PLATE_HEIGHT + PLATE_BUFFER));

        std::string save_color = gw->getColor();
        gw->setColor("white");
        gw->fillRect(x, y, width, height);
        gw->setColor(save_color);
    }

    void animatePlate(bool poping, int platesBelow, int plateWidth) {
        drawBase();
        drawPlates(platesBelow);
        drawPole();

        int frames = (highwayHeight / (PLATE_HEIGHT + PLATE_BUFFER)) - platesBelow;

        int start = 	(poping ? 0 			: 	frames - 1);
        int end = 		(poping ? frames 	 	: 	-1);
        int delta =		(poping ? 1 			: 	-1);

        for (int i = start; i != end; i += delta) {
            clearTopRegion(platesBelow);
            drawPlate(platesBelow + i, plateWidth);
            drawPole();		// re-draw the pole as it might have been drawn-over
            usleep(ANIMATION_SPEED);
        }
        clearTopRegion(platesBelow);

        if (!poping)		// if pushing(i.e: !poping), draw the plate after it "lands"
            drawPlate(platesBelow, plateWidth);

        drawPole();
    }

    Vector<int> plates;
    int base_x, base_y;
    int poleHeight;
    int highwayHeight;		// the height it rises from (base_x, base_y)

    GWindow *gw;
};

#endif
