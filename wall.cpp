#include "wall.h"
#include <iostream>

Wall::Wall(int width, int height)  : width(width), height(height), freeSegments(width)
{
    this->wallSegments = new WallSegment*[width];

    for(int i = 0 ; i < width ; i++) {
      this->wallSegments[i] = new WallSegment(this, i, height);
    }

}

WallSegment* Wall::aquireWallSegment() {

    std::unique_lock<std::mutex> l(this->_lock);

    this->_cv.wait(l, [this](){return this->freeSegments > 0;}); // waits until some segment is released

    WallSegment* firstFreeSegment = nullptr;

    for(int i = 0 ; i < width ; i++) {
        if(this->wallSegments[i]->isOccupied() == false) {
            firstFreeSegment = this->wallSegments[i];
            break;
        }
    }

    // Assertion
    if(firstFreeSegment == nullptr) {
        std::cout << "ASSERTION FAILED: First free segment was nullptr";
    }

    firstFreeSegment->occupy();
    this->freeSegments -= 1;

    l.unlock();

    return firstFreeSegment;
}

WallSegment* Wall::aquireWallSegmentToClean() {
    std::unique_lock<std::mutex> l(this->_lock);

    this->_cv.wait(l, [this](){return this->freeSegments > 0;}); // waits until some segment is released

    WallSegment* segmentToClean = nullptr;

    for(int i = 0 ; i < width ; i++) {
        if(this->wallSegments[i]->isOccupied() == false && !this->wallSegments[i]->isClean()) {
            segmentToClean = this->wallSegments[i];
            break;
        }
    }

    // If there is nothing to clean
    if(segmentToClean == nullptr) {
        l.unlock();
        this->_cv.notify_one();

    } else {

        segmentToClean->occupy();
        this->freeSegments -= 1;
        l.unlock();
    }

    return segmentToClean;
}

WallSegment* Wall::aquireWallSegmentToPaint() {
    std::unique_lock<std::mutex> l(this->_lock);

    this->_cv.wait(l, [this](){return this->freeSegments > 0;}); // waits until some segment is released

    WallSegment* segmentToPaint = nullptr;

    for(int i = 0 ; i < width ; i++) {
        if(this->wallSegments[i]->isOccupied() == false && !this->wallSegments[i]->isFullyPainted()) {
            segmentToPaint = this->wallSegments[i];
            break;
        }
    }

    // If there is nothing to clean
    if(segmentToPaint == nullptr) {
        l.unlock();
        this->_cv.notify_one();

    } else {

        segmentToPaint->occupy();
        this->freeSegments -= 1;
        l.unlock();
    }

    return segmentToPaint;
}

void Wall::releaseSegment(WallSegment* wallSegment) {

    std::unique_lock<std::mutex> l(this->_lock);

    wallSegment->release();
    this->freeSegments += 1;

    l.unlock();
    this->_cv.notify_one();

}
