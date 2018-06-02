#include "hotel.h"

Hotel::Hotel(int numberOfRooms) : numberOfRooms(numberOfRooms), numberOfFreeRooms(numberOfRooms)
{
    this->rooms = new HotelRoom*[numberOfRooms];

    for(int i = 0 ; i < numberOfRooms ; i++) {
      this->rooms[i] = new HotelRoom(i);
    }
}

HotelRoom* Hotel::aquireFreeRoom() {
    std::unique_lock<std::mutex> l(this->_lock);

    this->_cv.wait(l, [this](){return this->numberOfFreeRooms > 0;});

    HotelRoom* freeRoom = nullptr;

    for(int i = 0 ; i < numberOfRooms ; i++) {
        if(this->rooms[i]->isFree()) {
            freeRoom = this->rooms[i];
            break;
        }
    }

    freeRoom->setFree(false);
    this->numberOfFreeRooms -= 1;
    l.unlock();

    return freeRoom;
}

void Hotel::releaseRoom(HotelRoom* roomToRelease) {
    std::unique_lock<std::mutex> l(this->_lock);

    roomToRelease->setFree(true);
    this->numberOfFreeRooms += 1;

    l.unlock();
    this->_cv.notify_one();
}
