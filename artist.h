#ifndef ARTIST_H
#define ARTIST_H

#include "wall.h"
#include "paintcan.h"
#include "paintsupply.h"

enum ArtistState {
    WaitingForWall, Painting, WaitingForRefill, Refilling
};

class Artist
{
private:
    int identifier;
    volatile bool isRunning;

    Wall* wall;

    WallSegment* standingBy;

    PaintSupply* paintSupply;

    PaintCan paintCan;

    std::atomic<ArtistState> state;

    int currentProgress; // out of 10

    int stepTime;

    int randomStepTime();
    void waitNSteps(int n, int stepTime);

    void refillPaint();

public:
    Artist(int identifier, Wall* wall, PaintSupply* paintSupply);

    ArtistState getState() { return this->state; }

    int getCurrentProgress() { return this->currentProgress; }

    WallSegment* getStandingBy() { return this->standingBy; }

    int getIdentifier() { return this->identifier; }

    PaintCan getPaintCan() { return this->paintCan; }

    void lifeCycle();

    void stop();

    static int randomnessRange;
    static int randomnessBase;
};

#endif ARTIST_H
