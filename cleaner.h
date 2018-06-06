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

    int energy;

    int maxEnergy;

    std::atomic<CleanerState> state;

    void haveARest();

public:
    Cleaner(int identifier, Wall* wall, Hotel* hotel) : isRunning(true), identifier(identifier), wall(wall), hotel(hotel), maxEnergy(10), energy(10) {}

    CleanerState getState() { return this->state; }

    WallSegment* getStandingBy() { return this->standingBy; }

    HotelRoom* getOccupiedHotelRoom() { return this->occupiedRoom; }

    int getIdentifier() { return this->identifier; }

    int getEnergy() { return this->energy; }

    int getMaxEnergy() { return this->maxEnergy; }

    void lifeCycle();

    void stop();

};

#endif // CLEANER_H
