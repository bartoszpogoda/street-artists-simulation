#include "artist.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "randomness.h"

Artist::Artist(int identifier, Wall* wall, PaintSupply* paintSupply) : identifier(identifier),
    wall(wall), isRunning(true), paintCan(GREEN, 2),
    paintSupply(paintSupply)
{

}


void Artist::lifeCycle() {

    while(this->isRunning) {

        this->state = WaitingForWall;
        Randomness::waitNRandomSteps(1);

        if(paintCan.getCurrentCapacity() != 0) {
            // paint can not empty

            this->standingBy = wall->aquireWallSegmentToPaint();

            // aquire loop
            while(this->standingBy == nullptr) {
                Randomness::waitNRandomSteps(1);
                this->standingBy = wall->aquireWallSegmentToPaint();
            }

            this->state = Painting;

            // paint logic
            int initialCoverage = this->standingBy->getPaintCoverage();
            int totalHeight = this->standingBy->getHeight();

            Randomness::waitNRandomSteps(1);

            // while anything to paint and paint can not empty
            for(int i = initialCoverage; i < totalHeight && paintCan.getCurrentCapacity() > 0 ; i++) {
                this->standingBy->setPaintCoverage(i + 1);
                this->standingBy->setPaintColor(i, paintCan.getColor());
                this->paintCan.decrementCurrentCapacity();

                Randomness::waitNRandomSteps(3);
            }

            wall->releaseSegment(this->standingBy);
            this->standingBy = nullptr;

        }

        if(paintCan.getCurrentCapacity() == 0){
            this->refillPaint();
        }

    }

}

void Artist::refillPaint() {

    this->state = WaitingForRefill;

    paintSupply->enterPaintSupply();

    this->state = Refilling;

    Randomness::waitNRandomSteps(5);

    this->paintCan = paintSupply->aquirePaintCan();

    paintSupply->leavePaintSupply();

}

void Artist::stop() {
    this->isRunning = false;
}
