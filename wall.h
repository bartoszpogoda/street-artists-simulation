#ifndef WALL_H
#define WALL_H

#include "wallsegment.h"

class WallSegment;

class Wall
{
private:
    /** Width and height are in meters. */
    int width;
    int height;

    std::mutex _lock;
    std::condition_variable _cv;

    std::atomic<int> freeSegments;

    WallSegment** wallSegments;

public:
    Wall(int width, int height);

    /** Wait and then aquire a segment which is not fully painted. */
    WallSegment* aquireWallSegmentToPaint();

    /** Wait and then aquire a segmnet which is not fully clean. */
    WallSegment* aquireWallSegmentToClean();

    void releaseSegment(WallSegment* wallSegment);

    int getFreeSegmentsCount() { return this->freeSegments; }
    WallSegment** getWallSegments() { return this->wallSegments; }
    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
};

#endif // WALL_H
