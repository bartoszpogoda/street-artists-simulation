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

    void drawConfiguration();

    void drawArtistsInfo(Artist** artists, int numberOfArtists);
    void drawCleanersInfo(Cleaner** cleaners, int numberOfCleaners);

    void drawArtistsNearWall(Artist** artists, int numberOfArtists);
    void drawArtistsWaiting(Artist** artists, int numberOfArtists);
    void drawArtistsWaitingForRefill(Artist** artists, int numberOfArtists);
    void drawArtistRefilling(Artist** artists, int numberOfArtists);

    void drawPaintSupply(PaintSupply* paintSupply);


    void drawCleanersNearWall(Cleaner** cleaners, int numberOfCleaners);

    void drawCleanersWaiting(Cleaner** cleaners, int numberOfCleaners);

    void drawCleanersWaitingForRoom(Cleaner** cleaners, int numberOfCleaners);
    void drawCleanersSleeping(Cleaner** cleaners, int numberOfCleaners);

    void setDrawingColor(PaintColor paintColor);
    void setDrawingColorWithLabel(PaintColor paintColor);

    void drawWall(Wall* wall);
    void drawHotel(Hotel* hotel);
    void drawRoom(int bottomRightX, int bottomRightY, bool isFree);

public:
    Visualisation();
    ~Visualisation();

    void start(Wall* wall, Artist** artists, int numberOfArtists, Cleaner** cleaners, int numberOfCleaners, PaintSupply* paintSupply, Hotel* hotel);

};

#endif // VISUALISATION_H
