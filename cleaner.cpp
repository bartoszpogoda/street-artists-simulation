#include "cleaner.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "randomness.h"



void Cleaner::lifeCycle() {

    while(this->isRunning) {

        this->state = CWaitingForWall;

        this->standingBy= wall->aquireWallSegmentToClean();

        while(this->standingBy == nullptr) {
            Randomness::waitNRandomSteps(1);
            this->standingBy = wall->aquireWallSegmentToClean();
        }

        this->state = Cleaning;

        // paint logic
        int initialCoverage = this->standingBy->getPaintCoverage();

        // while anything to paint and not tired(todo)
        for(int i = initialCoverage; i > 0 && this->energy > 0; i--) {

            Randomness::waitNRandomSteps(3);
            this->standingBy->setPaintCoverage(i - 1);
            this->energy -= 1;
        }

        wall->releaseSegment(this->standingBy);

        this->standingBy = nullptr;

        if(this->energy == 0) {
            haveARest();
        }

    }

}


void Cleaner::haveARest() {

    this->state = WaitingForRoom;

    occupiedRoom = this->hotel->aquireFreeRoom();

    this->state = Sleeping;

    while(this->energy < this->maxEnergy) {
        this->energy += 1;
        Randomness::waitNRandomSteps(3);
    }

    this->hotel->releaseRoom(occupiedRoom);

    occupiedRoom = nullptr;
    this->state = CWaitingForWall;


}

void Cleaner::stop() {
    this->isRunning = false;
}
