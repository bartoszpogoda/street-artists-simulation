#include "wallsegment.h"
#include <thread>
#include <ncurses.h>

void WallSegment::occupy() {
//    std::unique_lock<std::mutex> l(this->_lock);

//    this->_cvOccupied.wait(l, [this](){return this->occupied == false;});

    this->occupied = true;

//    l.unlock();
}

void WallSegment::release() {
//    std::unique_lock<std::mutex> l(this->_lock);

    this->occupied = false;

//    l.unlock();
//    this->_cvOccupied.notify_one();
}


bool WallSegment::isOccupied() {
    return occupied;
}

int WallSegment::getPosition() {
    return this->position;
}
