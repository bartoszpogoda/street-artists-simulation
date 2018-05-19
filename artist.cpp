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

        this->standingBy = wall->aquireWallSegmentToPaint();
//        takeForks();

        while(this->standingBy == nullptr) {
            //
            std::this_thread::sleep_for (std::chrono::milliseconds(50));
            this->standingBy = wall->aquireWallSegmentToPaint();
        }

        // forks aquired, eataing
        this->state = Eating;



        int eatingStepTime = randomEatingStepTime();
        wait10Times(eatingStepTime);



        // test
        this->standingBy->setPaintCoverage(3);
        this->standingBy->setPaintColor(0, RED);
        this->standingBy->setPaintColor(1, RED);
        this->standingBy->setPaintColor(2, RED);


        eatingStepTime = randomEatingStepTime();
        wait10Times(eatingStepTime);

//        releaseForks();
        wall->releaseSegment(this->standingBy);
        this->standingBy = nullptr;


        this->state = Thinking;

    }

}

void Artist::stop() {
    this->isRunning = false;
}
