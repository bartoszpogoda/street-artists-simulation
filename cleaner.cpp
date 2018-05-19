#include "cleaner.h"
#include <iostream>
#include <thread>
#include <chrono>

int Cleaner::randomnessRange = 200;//0;
int Cleaner::randomnessBase = 200;//0;

Cleaner::Cleaner(int identifier, Wall* wall) : identifier(identifier),
    wall(wall), isRunning(true), currentProgress(0)
{
}

int Cleaner::randomStepTime() {
    return (randomnessBase + rand() % randomnessRange)/10;
}


/**
 * @brief Cleaner::wait10Times sleeps for 10x specified time while incrementing current progress after each step
 * @param stepTime time of each step in miliseconds
 */
void Cleaner::waitNSteps(int n, int stepTime) {
    for(currentProgress = 0; currentProgress < n && this->isRunning ; currentProgress++) {
        std::this_thread::sleep_for (std::chrono::milliseconds(stepTime));
    }
    currentProgress = 0;
}


void Cleaner::lifeCycle() {

    int stepTime = randomStepTime();

    while(this->isRunning) {

        this->state = CWaitingForWall;

        this->standingBy= wall->aquireWallSegmentToClean();

        while(this->standingBy == nullptr) {
            std::this_thread::sleep_for (std::chrono::milliseconds(50));
            this->standingBy = wall->aquireWallSegmentToClean();
        }

        this->state = Cleaning;

        // paint logic
        int initialCoverage = this->standingBy->getPaintCoverage();

        waitNSteps(1, stepTime);

        // while anything to paint and not tired(todo)
        for(int i = initialCoverage; i > 0; i--) {
            this->standingBy->setPaintCoverage(i - 1);

            waitNSteps(3, stepTime);
        }

        wall->releaseSegment(this->standingBy);
        this->standingBy = nullptr;

        this->state = CWaitingForWall;

    }

}

void Cleaner::stop() {
    this->isRunning = false;
}
