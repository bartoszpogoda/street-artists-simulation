#include "artist.h"
#include <iostream>
#include <thread>
#include <chrono>

int Artist::randomnessRange = 2000;//200;//0;
int Artist::randomnessBase = 2000;//200;//0;

Artist::Artist(int identifier, Wall* wall) : identifier(identifier),
    wall(wall), isRunning(true), currentProgress(0), paintCan(GREEN, 2)
{

}

int Artist::randomStepTime() {
    return (randomnessBase + rand() % randomnessRange)/10;
}

/**
 * @brief Artist::wait10Times sleeps for 10x specified time while incrementing current progress after each step
 * @param stepTime time of each step in miliseconds
 */
void Artist::waitNSteps(int n, int stepTime) {
    for(currentProgress = 0; currentProgress < n && this->isRunning ; currentProgress++) {
        std::this_thread::sleep_for (std::chrono::milliseconds(stepTime));
    }
    currentProgress = 0;
}


void Artist::lifeCycle() {

    int stepTime = randomStepTime();

    while(this->isRunning) {

        this->state = WaitingForWall;
        waitNSteps(10, stepTime);

        this->state = WaitingForWall;

        if(paintCan.getCurrentCapacity() != 0) {
            // paint can not empty

            this->standingBy = wall->aquireWallSegmentToPaint();

            // aquire loop
            while(this->standingBy == nullptr) {
                std::this_thread::sleep_for (std::chrono::milliseconds(50));
                this->standingBy = wall->aquireWallSegmentToPaint();
            }

            this->state = Painting;

            // paint logic
            int initialCoverage = this->standingBy->getPaintCoverage();
            int totalHeight = this->standingBy->getHeight();

            waitNSteps(1, stepTime);

            // while anything to paint and paint can not empty
            for(int i = initialCoverage; i < totalHeight && paintCan.getCurrentCapacity() > 0 ; i++) {
                this->standingBy->setPaintCoverage(i + 1);
                this->standingBy->setPaintColor(i, paintCan.getColor());
                this->paintCan.decrementCurrentCapacity();

                waitNSteps(3, stepTime);
            }

            wall->releaseSegment(this->standingBy);
            this->standingBy = nullptr;

        }

        if(paintCan.getCurrentCapacity() == 0){
            this->state = WaitingForRefill;
            waitNSteps(10, stepTime);

            this->refillPaint();
        }

    }

}

void Artist::refillPaint() {

    int a = rand() % 4;
    PaintColor color = a == 0 ? RED : a == 1 ? GREEN : a == 2 ? MAGENTA : CYAN;
    int size = rand() % 2 ? 4 : 8;

    this->paintCan = PaintCan(color, size);
}

void Artist::stop() {
    this->isRunning = false;
}
