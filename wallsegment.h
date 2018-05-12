#ifndef WALLSEGMENT
#define WALLSEGMENT

#include <mutex>
#include <atomic>
#include <condition_variable>
#include "wall.h"

class Wall;

class WallSegment
{
private:
    Wall* wall;

    std::atomic<bool> occupied;
    int position;
    int height;

    int paintCoverage;

    std::mutex _lock;
    std::condition_variable _cvOccupied;
public:
    WallSegment(Wall* wall, int position, int height) : wall(wall), position(position), height(height), occupied(false), paintCoverage(0) {}

    void occupy();
    void release();

    bool isOccupied();

    bool isClean() { return this->paintCoverage == 0; }
    bool isFullyPainted() { return this->paintCoverage == height; }

    void setPaintCoverage(int paintCoverage) { this->paintCoverage = paintCoverage; }

    int getPosition();
    int getPaintCoverage() { return this->paintCoverage; }

};

#endif // WALLSEGMENT

