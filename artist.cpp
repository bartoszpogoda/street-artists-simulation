#include "artist.h"
#include <iostream>
#include <thread>
#include <chrono>

int Artist::randomnessRange = 2000;
int Artist::randomnessBase = 2000;

Artist::Artist(int identifier, Wall* wall) : identifier(identifier),
    wall(wall), isRunning(true), currentProgress(0)
{
}

int Artist::randomThinkingStepTime() {
    return (randomnessBase + rand() % randomnessRange)/10;
}


int Artist::randomEatingStepTime() {
    return (randomnessBase + rand() % randomnessRange)/10;
}


/**
 * @brief Philosopher::wait10Times sleeps for 10x specified time while incrementing current progress after each step
 * @param stepTime time of each step in miliseconds
 */
void Artist::wait10Times(int stepTime) {
    for(currentProgress = 0; currentProgress < 10 && this->isRunning ; currentProgress++) {
        std::this_thread::sleep_for (std::chrono::milliseconds(stepTime));
    }
    currentProgress = 0;
}


void Artist::lifeCycle() {

    while(this->isRunning) {

        // thinking
        int thinkingStepTime = randomThinkingStepTime();
        wait10Times(thinkingStepTime);

        // finished thinking - will wait for forks
        this->state = Waiting;

        WallSegment* usedWallSegment = wall->aquireWallSegmentToPaint();
//        takeForks();

        while(usedWallSegment == nullptr) {
            //
            std::this_thread::sleep_for (std::chrono::milliseconds(50));
            usedWallSegment = wall->aquireWallSegmentToPaint();
        }

        // forks aquired, eataing
        this->state = Eating;

        int eatingStepTime = randomEatingStepTime();
        wait10Times(eatingStepTime);

        // test
        usedWallSegment->setPaintCoverage(3);

//        releaseForks();
        wall->releaseSegment(usedWallSegment);


        this->state = Thinking;

    }

}

void Artist::stop() {
    this->isRunning = false;
}
