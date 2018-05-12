#ifndef ARTIST_H
#define ARTIST_H

#include "fork.h"
#include "wall.h"

enum ArtistState {
    Thinking, Eating, Waiting, LeftForkAquired, RightForkAquired
};

class Artist
{
private:
    int identifier;
    volatile bool isRunning;

    Wall* wall;

    std::atomic<ArtistState> state;

    int currentProgress; // out of 10

    // actual time divided by 10
    int randomThinkingStepTime();

    // actual time divided by 10
    int randomEatingStepTime();

    void wait10Times(int stepTime);

    void takeForks();

    void releaseForks();

public:
    Artist(int identifier, Wall* wall);

    ArtistState getState() { return this->state; }

    int getCurrentProgress() { return this->currentProgress; }

    void lifeCycle();

    void stop();

    static int randomnessRange;
    static int randomnessBase;
};

#endif ARTIST_H
