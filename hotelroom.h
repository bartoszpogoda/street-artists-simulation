#ifndef HOTELROOM_H
#define HOTELROOM_H


class HotelRoom
{
    bool free;
    int id;
public:
    HotelRoom(int id) : free(true), id(id) {}

    bool isFree() { return this->free; }
    void setFree(bool free) { this->free = free; }

    int getId() { return this->id; }
};

#endif // HOTELROOM_H
