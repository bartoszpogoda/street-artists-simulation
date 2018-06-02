#ifndef HOTEL_H
#define HOTEL_H

#include <mutex>
#include <condition_variable>
#include "hotelroom.h"

class HotelRoom;

class Hotel
{
    int numberOfRooms;
    int numberOfFreeRooms;

    std::mutex _lock;
    std::condition_variable _cv;

    HotelRoom** rooms;

public:
    Hotel(int numberOfRooms);

    /** Wait and then aquire a free room. */
    HotelRoom* aquireFreeRoom();

    void releaseRoom(HotelRoom* roomToRelease);

    int getNumberOfRooms() { return numberOfRooms; }

    HotelRoom* getRoom(int i) { return rooms[i]; }
};

#endif // HOTEL_H
