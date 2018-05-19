#include "cleaner.h"
#include <iostream>
#include <thread>
#include <chrono>

int Cleaner::randomnessRange = 2000;
int Cleaner::randomnessBase = 2000;

Cleaner::Cleaner(int identifier, Wall* wall) : identifier(identifier),
    wall(wall), isRunning(true), currentProgress(0)
{
}

int Cleaner::randomThinkingStepTime() {
    return (randomnessBase + rand() % randomnessRange)/10;
}


int Cleaner::randomEatingStepTime() {
    return (randomnessBase + rand() % randomnessRange)/10;
}


/**
 * @brief Philosopher::wait10Times sleeps for 10x specified time while incrementing current progress after each step
 * @param stepTime time of each step in miliseconds
 */
void Cleaner::wait10Times(int stepTime) {
    for(currentProgress = 0; currentProgress < 10 && this->isRunning ; currentProgress++) {
        std::this_thread::sleep_for (std::chrono::milliseconds(stepTime));
    }
    currentProgress = 0;
}


void Cleaner::lifeCycle() {

    while(this->isRunning) {

        // thinking
        int thinkingStepTime = randomThinkingStepTime();
        wait10Times(thinkingStepTime);

        // finished thinking - will wait for forks
        this->state = CWaiting;

        this->standingBy= wall->aquireWallSegmentToClean();
//        takeForks();

        while(this->standingBy == nullptr) {
            //
            std::this_thread::sleep_for (std::chrono::milliseconds(50));
            this->standingBy = wall->aquireWallSegmentToClean();
        }

        // forks aquired, eataing
        this->state = CEating;

        int eatingStepTime = randomEatingStepTime();
        wait10Times(eatingStepTime);

        // test
        this->standingBy->setPaintCoverage(0);

//        releaseForks();
        wall->releaseSegment(this->standingBy);


        this->state = CThinking;

    }

}

void Cleaner::stop() {
    this->isRunning = false;
}
