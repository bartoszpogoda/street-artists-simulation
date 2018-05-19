#ifndef CLEANER_H
#define CLEANER_H

#include <atomic>
#include "wall.h"
#include "wallsegment.h"

class Wall;

enum CleanerState {
    CThinking, CEating, CWaiting, CLeftForkAquired, CRightForkAquired
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

    // actual time divided by 10
    int randomThinkingStepTime();

    // actual time divided by 10
    int randomEatingStepTime();

    void wait10Times(int stepTime);

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
