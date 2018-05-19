#ifndef VISUALISATION_H
#define VISUALISATION_H

#include "artist.h"
#include "fork.h"
#include "cleaner.h"

class Visualisation
{
private:
    void initColors();

    void drawLegend();
//    void drawTimeRangePanel();

    void drawPhilosopher(int id, bool usingLeft, bool usingRight);
//    void drawPhilosopherDetails(int id, int progress, PhilosopherState state);
//    void drawFork(int id, bool inUse);

    void drawArtistsNearWall(Artist** artists);
    void drawCleanersNearWall(Cleaner** cleaners);

    void drawWall(Wall* wall);

public:
    Visualisation();
    ~Visualisation();

    void start(Wall* wall, Artist** artists, Cleaner** cleaners);

};

#endif // VISUALISATION_H
