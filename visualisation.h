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

    void drawArtistsTable(Artist** artists, int numberOfArtists);

    void drawArtistsNearWall(Artist** artists, int numberOfArtists);
    void drawArtistsWaiting(Artist** artists, int numberOfArtists);
    void drawArtistsWaitingForRefill(Artist** artists, int numberOfArtists);
    void drawArtistRefilling(Artist** artists, int numberOfArtists);

    void drawPaintSupply(PaintSupply* paintSupply);


    void drawCleanersNearWall(Cleaner** cleaners, int numberOfCleaners);


    void drawCleanersWaiting(Cleaner** cleaners, int numberOfCleaners);

    void setDrawingColor(PaintColor paintColor);
    void setDrawingColorWithLabel(PaintColor paintColor);

    void drawWall(Wall* wall);

public:
    Visualisation();
    ~Visualisation();

    void start(Wall* wall, Artist** artists, int numberOfArtists, Cleaner** cleaners, int numberOfCleaners, PaintSupply* paintSupply);

};

#endif // VISUALISATION_H
