#ifndef PAINTSUPPLY_H
#define PAINTSUPPLY_H

#include <deque>
#include "paintcan.h"
#include <mutex>
#include <condition_variable>
#include <atomic>

class PaintSupply
{
    std::deque<PaintCan> supply;
    int supplySize;
    std::mutex _supplyQueueMutex;

    // Producer - consumer
    std::mutex _lock;
    std::condition_variable _cv;
    std::atomic<bool> supplyEmpty;
    std::atomic<bool> supplyFull;

    // There should be only one artist waiting for paint in the supply.
    std::mutex _lockWaitForPlace;
    std::condition_variable _cvWaitForPlace;
    std::atomic<bool> place;


public:
    PaintSupply(int supplySize);

    PaintCan aquirePaintCan();

    void supplyPaintCan(PaintCan paintCan);

    void enterPaintSupply();

    void leavePaintSupply();

    // for drawing purposes
    std::deque<PaintCan>* getDequeToDraw();
    bool isEmpty() { return this->supplyEmpty; }
    bool isFull() { return this->supplyFull; }

};

#endif // PAINTSUPPLY_H
