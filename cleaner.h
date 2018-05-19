#ifndef CLEANER_H
#define CLEANER_H

#include <atomic>
#include "wall.h"
#include "wallsegment.h"

class Wall;

enum CleanerState {
    CWaitingForWall, Cleaning
};

class Cleaner
{
private:
    int identifier;
    volatile bool isRunning;

    Wall* wall;

    WallSegment* standingBy;

    std::atomic<CleanerState> state;

    int currentProgress; // out of 10

    int randomStepTime();
    void waitNSteps(int n, int stepTime);

public:
    Cleaner(int identifier, Wall* wall);

    CleanerState getState() { return this->state; }

    int getCurrentProgress() { return this->currentProgress; }

    WallSegment* getStandingBy() { return this->standingBy; }

    int getIdentifier() { return this->identifier; }

    void lifeCycle();

    void stop();

    static int randomnessRange;
    static int randomnessBase;
};

#endif // CLEANER_H
