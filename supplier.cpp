#include "supplier.h"
#include <iostream>
#include <thread>
#include <chrono>

Supplier::Supplier(PaintSupply* paintSupply) : paintSupply(paintSupply), isRunning(true)
{

}


int Supplier::randomStepTime() {
    return (2000 + rand() % 2000)/10;
}

/**
 * @brief Supplier::wait10Times sleeps for 10x specified time while incrementing current progress after each step
 * @param stepTime time of each step in miliseconds
 */
void Supplier::waitNSteps(int n, int stepTime) {
    for(currentProgress = 0; currentProgress < n && this->isRunning ; currentProgress++) {
        std::this_thread::sleep_for (std::chrono::milliseconds(stepTime));
    }
    currentProgress = 0;
}

void Supplier::lifeCycle() {

    int stepTime = randomStepTime();

    while(this->isRunning) {

        waitNSteps(10, stepTime);
        paintSupply->supplyPaintCan(PaintCan(RED,1));

    }

}

void Supplier::stop() {
    this->isRunning = false;
}
