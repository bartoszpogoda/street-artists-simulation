#include "wallsegment.h"
#include <thread>
#include <ncurses.h>

void WallSegment::occupy() {
    this->occupied = true;
}

void WallSegment::release() {
    this->occupied = false;
}


bool WallSegment::isOccupied() {
    return occupied;
}

int WallSegment::getPosition() {
    return this->position;
}
