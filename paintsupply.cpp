#include "paintsupply.h"

PaintSupply::PaintSupply(int supplySize) : supplyEmpty(true), supplyFull(false), place(true), supplySize(supplySize)
{

}

PaintCan PaintSupply::aquirePaintCan() {

    std::unique_lock<std::mutex> l(this->_lock);

    this->_cv.wait(l, [this](){return this->supplyEmpty == false;}); // waits until there is some paint to take

    _supplyQueueMutex.lock();
    PaintCan paintCan = supply.front();
    supply.pop_front();

    this->supplyFull = false;
    if(supply.empty()) {
        this->supplyEmpty = true;
    }

    _supplyQueueMutex.unlock();

    l.unlock();
    _cv.notify_one();

    return paintCan;

}


void PaintSupply::supplyPaintCan(PaintCan paintCan2) {


    // Temp:
    int a = rand() % 4;
    PaintColor color = a == 0 ? RED : a == 1 ? GREEN : a == 2 ? MAGENTA : CYAN;
    int size = rand() % 2 ? 4 : 8;

    PaintCan paintCan = PaintCan(color, size);


    std::unique_lock<std::mutex> l(this->_lock);

    this->_cv.wait(l, [this](){return this->supplyFull == false;}); // waits until there is some place for paint

    _supplyQueueMutex.lock();
    supply.push_back(paintCan);

    this->supplyEmpty = false;
    if(supply.size() >= supplySize) {
        this->supplyFull = true;
    }

    _supplyQueueMutex.unlock();

    l.unlock();
    _cv.notify_one();



//    _supplyQueueMutex.lock();


//    std::unique_lock<std::mutex> l(this->_lock);

//    supplyEmpty = false;

//    l.unlock();
//    _cv.notify_one();

//    _supplyQueueMutex.unlock();


}

void PaintSupply::enterPaintSupply() {

    std::unique_lock<std::mutex> l(this->_lockWaitForPlace);

    this->_cvWaitForPlace.wait(l, [this](){return this->place == true;}); // waits until there is place for artist in supply

    this->place = false;

    l.unlock();

}

void PaintSupply::leavePaintSupply() {

    std::unique_lock<std::mutex> l(this->_lockWaitForPlace);

    this->place = true;

    l.unlock();
    this->_cvWaitForPlace.notify_one(); // notifies artist waiting for place in supply

}


std::deque<PaintCan>* PaintSupply::getDequeToDraw() {
    return &supply;
}
