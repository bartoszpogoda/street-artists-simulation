#ifndef CLEANER_H
#define CLEANER_H

#include <atomic>
#include "wall.h"
#include "wallsegment.h"
#include "hotel.h"

class Wall;

enum CleanerState {
    CWaitingForWall, Cleaning, WaitingForRoom, Sleeping
};

class Cleaner
{
private:
    int identifier;
    volatile bool isRunning;

    Hotel* hotel;

    Wall* wall;

    WallSegment* standingBy;

    HotelRoom* occupiedRoom;

    std::atomic<CleanerState> state;

    int currentProgress; // out of 10

    int stepTime;
    int randomStepTime();
    void waitNSteps(int n, int stepTime);

    void haveARest();

public:
    Cleaner(int identifier, Wall* wall, Hotel* hotel);

    CleanerState getState() { return this->state; }

    int getCurrentProgress() { return this->currentProgress; }

    WallSegment* getStandingBy() { return this->standingBy; }

    HotelRoom* getOccupiedHotelRoom() { return this->occupiedRoom; }

    int getIdentifier() { return this->identifier; }

    void lifeCycle();

    void stop();

    static int randomnessRange;
    static int randomnessBase;
};

#endif // CLEANER_H
