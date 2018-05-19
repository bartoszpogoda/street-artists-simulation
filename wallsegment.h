#ifndef WALLSEGMENT
#define WALLSEGMENT

#include <mutex>
#include <atomic>
#include <condition_variable>
#include "wall.h"
#include "colors.h"

class Wall;

class WallSegment
{
private:
    Wall* wall;

    std::atomic<bool> occupied;
    int position;
    int height;

    int paintCoverage;
    PaintColor* paints;

    std::mutex _lock;
    std::condition_variable _cvOccupied;
public:
    WallSegment(Wall* wall, int position, int height) : wall(wall), position(position), height(height), occupied(false), paintCoverage(0), paints(new PaintColor[height]) {}

    void occupy();
    void release();

    bool isOccupied();

    bool isClean() { return this->paintCoverage == 0; }
    bool isFullyPainted() { return this->paintCoverage == height; }

    void setPaintCoverage(int paintCoverage) { this->paintCoverage = paintCoverage; }
    void setPaintColor(int height, PaintColor paintColor) { this->paints[height] = paintColor; }

    int getPosition();
    int getPaintCoverage() { return this->paintCoverage; }
    PaintColor getPaintColor(int height) { return this->paints[height]; }
    int getHeight() { return this->height; }

};

#endif // WALLSEGMENT

