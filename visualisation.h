#ifndef VISUALISATION_H
#define VISUALISATION_H

#include "artist.h"
#include "cleaner.h"

class Visualisation
{
private:

    char** map;

    void loadMap();
    void drawMap();

    int mapX;
    int mapY;

    void initColors();

    void drawLegend();

    void drawArtistsNearWall(Artist** artists, int numberOfArtists);
    void drawCleanersNearWall(Cleaner** cleaners, int numberOfCleaners);

    void drawWall(Wall* wall);

public:
    Visualisation();
    ~Visualisation();

    void start(Wall* wall, Artist** artists, int numberOfArtists, Cleaner** cleaners, int numberOfCleaners);

};

#endif // VISUALISATION_H
