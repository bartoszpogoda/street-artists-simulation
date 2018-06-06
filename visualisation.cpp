#include "visualisation.h"
#include "ncurses.h"
#include "randomness.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Visualisation::Visualisation()
{
    initscr();
    noecho();
    curs_set(0);

    initColors();
}

void Visualisation::initColors() {
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);

    init_pair(4, COLOR_BLUE, COLOR_BLUE);
    init_pair(5, COLOR_YELLOW, COLOR_YELLOW);

    init_pair(6, COLOR_CYAN, COLOR_BLACK);

    init_pair(7, COLOR_WHITE, COLOR_WHITE);

    init_pair(8, COLOR_WHITE, COLOR_RED);

    init_pair(9, COLOR_RED, COLOR_RED);

    init_pair(10, COLOR_GREEN, COLOR_GREEN);

    init_pair(11, COLOR_WHITE, COLOR_BLUE);

    init_pair(12, COLOR_BLACK, COLOR_BLACK);

    init_pair(13, COLOR_CYAN, COLOR_CYAN);

    init_pair(14, COLOR_MAGENTA, COLOR_MAGENTA);

    init_pair(15, COLOR_WHITE, COLOR_MAGENTA);


    init_pair(16, COLOR_WHITE, COLOR_RED);

    init_pair(17, COLOR_WHITE, COLOR_GREEN);

    init_pair(18, COLOR_WHITE, COLOR_CYAN);

    init_pair(19, COLOR_WHITE, COLOR_MAGENTA);



    bkgd(COLOR_PAIR(1));
}

void Visualisation::drawConfiguration() {


    const int legendTopLeftX = 81;
    const int legendTopLeftY = 17;

    // if screen is not extended then do not draw anything
    int x,y;
    getmaxyx(stdscr, y, x) ;

    if(x < legendTopLeftX + 15) {
        return;
    }

    attron(COLOR_PAIR(1));
    move(legendTopLeftY + 2, legendTopLeftX);
    printw("Single operation time range: ");
    move(legendTopLeftY + 3, legendTopLeftX);
    printw("[");
    printw(std::to_string(Randomness::randomnessBase).c_str());
    printw(", ");
    printw(std::to_string(Randomness::randomnessRange + Randomness::randomnessBase).c_str());
    printw(") ms");
    move(legendTopLeftY + 4, legendTopLeftX);
    printw("'z', 'x', 'c', 'v'");


}

void Visualisation::drawWall(Wall *wall) {

    const int wallBottomX = 20;
    const int wallBottomY = 10;

    WallSegment** wallSegments = wall->getWallSegments();

    for(int i = 0 ; i < wall->getWidth() * 3 ; i++) {
        WallSegment* segmentToDraw = wallSegments[i/3];
        // painted
        int j = 0;
        for(; j < segmentToDraw->getPaintCoverage() ; j++) {

            PaintColor paintColor = segmentToDraw->getPaintColor(j);
            move(wallBottomY - j, wallBottomX + i);
            setDrawingColor(paintColor);
            addch('x');

        }

        // clean
        for(; j < segmentToDraw->getHeight() ; j++) {


            move(wallBottomY - j, wallBottomX + i);
            attron(COLOR_PAIR(7));
            addch('x');
        }
    }

}

void Visualisation::drawRoom(int bottomRightX, int bottomRightY, bool isFree) {
    // bed white
    for(int i = bottomRightX - 1 ; i >= bottomRightX - 2 ; i--) {
        move(bottomRightY, i);
        attron(COLOR_PAIR(7));
        addch('x');
    }
    // bed red
    for(int i = bottomRightX - 3 ; i >= bottomRightX - 6 ; i--) {
        move(bottomRightY, i);
        attron(COLOR_PAIR(9));
        addch('x');
    }

    // ceiling
    for(int i = bottomRightX ; i >= bottomRightX - 10 ; i--) {
        move(bottomRightY - 3, i);
        attron(COLOR_PAIR(14));
        addch('x');
    }

    // wall
    move(bottomRightY - 2, bottomRightX - 10);
    attron(COLOR_PAIR(14));
    addch('x');

    // door
    if(!isFree) {
        for(int i = bottomRightY ; i >= bottomRightY -1 ; i--) {
            move(i, bottomRightX - 10);
            attron(COLOR_PAIR(9));
            addch('x');
        }
    }
}

void Visualisation::drawHotel(Hotel *hotel) {
    const int basementRightX = 79;
    const int basementRightY = 23;

    int numberOfRooms = hotel->getNumberOfRooms();

    for(int i = 0; i < numberOfRooms * 4 ; i++) {
        move(basementRightY - i, basementRightX - 10);
        attron(COLOR_PAIR(10));
        printw("           ");
    }

    for(int i = 0; i < numberOfRooms ; i++) {
        drawRoom(basementRightX, basementRightY - i * 4, hotel->getRoom(i)->isFree()); // not sure 3 or 4
    }
}

void Visualisation::drawArtistsNearWall(Artist** artists, int numberOfArtists) {

    const int wallBottomX = 20;
    const int wallBottomY = 10;

    for(int i = 0 ; i < numberOfArtists ; i++) {
        if(artists[i]->getStandingBy() != nullptr) {
            int position = artists[i]->getStandingBy()->getPosition();

            move(wallBottomY + 2, wallBottomX + position*3 + 1);
            attron(COLOR_PAIR(5));
            addch('x');

            move(wallBottomY + 3, wallBottomX + position*3 + 1);
            attron(COLOR_PAIR(8));
            addch('0' + artists[i]->getIdentifier());

        }
    }

}

void Visualisation::drawArtistsInfo(Artist** artists, int numberOfArtists) {

    const int tableTopLeftX = 81;
    const int tableTopLeftY = 3;

    // if screen is not extended then do not draw anything
    int x,y;
    getmaxyx(stdscr, y, x) ;

    if(x < tableTopLeftX + 15) {
        return;
    }

    move(tableTopLeftY - 2, tableTopLeftX);
    attron(COLOR_PAIR(1));
    printw("Artists paint");

    for(int i = 0 ; i < numberOfArtists ; i++) {
        move(tableTopLeftY + i*2, tableTopLeftX);
        attron(COLOR_PAIR(1));
        addch('0' + artists[i]->getIdentifier());
        addch(' ');

        PaintCan paintCan = artists[i]->getPaintCan();

        int j = 0;
        for(;j < paintCan.getCurrentCapacity() ; j++) {
            setDrawingColor(paintCan.getColor());
            addch('x');
        }
        for(;j < paintCan.getTotalCapacity(); j++) {
            attron(COLOR_PAIR(7));
            addch('x');
        }

    }
}

void Visualisation::drawCleanersInfo(Cleaner** cleaners, int numberOfCleaners) {
    const int tableTopLeftX = 96;
    const int tableTopLeftY = 3;

    // if screen is not extended then do not draw anything
    int x,y;
    getmaxyx(stdscr, y, x) ;

    if(x < tableTopLeftX + 15) {
        return;
    }

    move(tableTopLeftY - 2, tableTopLeftX);
    attron(COLOR_PAIR(1));
    printw("Cleaners energy");

    for(int i = 0 ; i < numberOfCleaners ; i++) {
        move(tableTopLeftY + i*2, tableTopLeftX);
        attron(COLOR_PAIR(1));
        addch('0' + cleaners[i]->getIdentifier());
        addch(' ');

        int energyLevel= cleaners[i]->getEnergy();
        int maxEnergyLevel= cleaners[i]->getMaxEnergy();

        int j = 0;
        for(;j < energyLevel ; j++) {
            attron(COLOR_PAIR(9));
            addch('x');
        }
        for(;j < maxEnergyLevel; j++) {
            attron(COLOR_PAIR(7));
            addch('x');
        }

    }
}

void Visualisation::drawArtistsWaiting(Artist** artists, int numberOfArtists) {

    const int waitingBottomX = 5;
    const int waitingBottomY = 10;

    int index = 0;
    for(int i = 0 ; i < numberOfArtists ; i++) {
        if(artists[i]->getState() == WaitingForWall) {

            move(waitingBottomY + 2, waitingBottomX + index * 2);
            attron(COLOR_PAIR(5));
            addch('x');

            move(waitingBottomY + 3, waitingBottomX + index * 2);
            attron(COLOR_PAIR(8));
            addch('0' + artists[i]->getIdentifier());

            index++;
        }
    }
}


void Visualisation::drawArtistsWaitingForRefill(Artist** artists, int numberOfArtists) {

    const int waitingForRefillBottomX = 28;
    const int waitingForRefillBottomY = 20;

    int index = 0;
    for(int i = 0 ; i < numberOfArtists ; i++) {
        if(artists[i]->getState() == WaitingForRefill) {

            move(waitingForRefillBottomY + 2, waitingForRefillBottomX + index * 2);
            attron(COLOR_PAIR(5));
            addch('x');

            move(waitingForRefillBottomY + 3, waitingForRefillBottomX + index * 2);
            attron(COLOR_PAIR(8));
            addch('0' + artists[i]->getIdentifier());

            index++;
        }
    }

}

void Visualisation::drawArtistRefilling(Artist** artists, int numberOfArtists) {

    const int refillBottomX = 25;
    const int refillBottomY = 20;

    int index = 0;
    for(int i = 0 ; i < numberOfArtists ; i++) {
        if(artists[i]->getState() == Refilling) {

            move(refillBottomY + 2, refillBottomX);
            attron(COLOR_PAIR(5));
            addch('x');

            move(refillBottomY + 3, refillBottomX);
            attron(COLOR_PAIR(8));
            addch('0' + artists[i]->getIdentifier());

            index++;

            return;
        }
    }

}


void Visualisation::drawCleanersWaiting(Cleaner** cleaners, int numberOfCleaners) {

    const int waitingBottomX = 50;
    const int waitingBottomY = 10;

    int index = 0;
    for(int i = 0 ; i < numberOfCleaners ; i++) {
        if(cleaners[i]->getState() == CWaitingForWall) {

            move(waitingBottomY + 2, waitingBottomX + index * 2);
            attron(COLOR_PAIR(5));
            addch('x');

            move(waitingBottomY + 3, waitingBottomX + index * 2);
            attron(COLOR_PAIR(11));
            addch('0' + cleaners[i]->getIdentifier());

            index++;
        }
    }
}


void Visualisation::drawCleanersNearWall(Cleaner** cleaners, int numberOfCleaners) {

    const int wallBottomX = 20;
    const int wallBottomY = 10;

    for(int i = 0 ; i < numberOfCleaners ; i++) {
        if(cleaners[i]->getStandingBy() != nullptr) {
            int position = cleaners[i]->getStandingBy()->getPosition();

            move(wallBottomY + 2, wallBottomX + position*3 + 1);
            attron(COLOR_PAIR(5));
            addch('x');

            move(wallBottomY + 3, wallBottomX + position*3 + 1);
            attron(COLOR_PAIR(11));
            addch('0' + cleaners[i]->getIdentifier());

        }
    }

}


void Visualisation::drawCleanersWaitingForRoom(Cleaner** cleaners, int numberOfCleaners) {

    const int waitingForRoomBottomX = 65;
    const int waitingForRoomBottomY = 20;

    int index = 0;
    for(int i = 0 ; i < numberOfCleaners ; i++) {
        if(cleaners[i]->getState() == WaitingForRoom) {

            move(waitingForRoomBottomY + 2, waitingForRoomBottomX - index * 2);
            attron(COLOR_PAIR(5));
            addch('x');

            move(waitingForRoomBottomY + 3, waitingForRoomBottomX - index * 2);
            attron(COLOR_PAIR(11));
            addch('0' + cleaners[i]->getIdentifier());

            index++;

        }
    }
}

void Visualisation::drawCleanersSleeping(Cleaner** cleaners, int numberOfCleaners) {
    const int basementRightX = 79;
    const int basementRightY = 23;

        for(int i = 0 ; i < numberOfCleaners ; i++) {
            if(cleaners[i]->getState() == Sleeping) {

                int roomId = cleaners[i]->getOccupiedHotelRoom()->getId();

                // face
                move(basementRightY - roomId * 4 - 1, basementRightX - 2);
                attron(COLOR_PAIR(5));
                addch('x');

                // shirt
                move(basementRightY - roomId * 4, basementRightX - 8);
                attron(COLOR_PAIR(11));
                addch('0' + cleaners[i]->getIdentifier());

            }
        }

}

void Visualisation::drawPaintSupply(PaintSupply* paintSupply) {

    const int suplyRightX = 17;
    const int supplyRightY = 22;


    move(20,5);
    if(paintSupply->isEmpty() || paintSupply->isFull()) {
        attron(COLOR_PAIR(8));
    } else {
        attron(COLOR_PAIR(15));
    }
    printw("Paint Supply");

    std::deque<PaintCan>* deque = paintSupply->getDequeToDraw();

    for(int i = 0 ; i < deque->size() ; i++) {
        PaintCan toDraw = deque->at(i);

        move(supplyRightY,suplyRightX - i);
        setDrawingColorWithLabel(toDraw.getColor());

        addch('0' + toDraw.getTotalCapacity());
    }

}


Visualisation::~Visualisation(){
    endwin();
}

void Visualisation::loadMap() {

    string line;
    ifstream mapfile;

    mapfile.open("map.txt", ios::in);

    if(mapfile.is_open()) {

        mapfile >> mapX;
        mapfile >> mapY;

        map = new char*[mapY];
        for(int i = 0; i < mapY ; i++) {
            map[i] = new char[mapX];

            for(int j = 0 ; j < mapX ; j++) {
                mapfile >> map[i][j];
            }
        }

        mapfile.close();
    }
}

void Visualisation::drawMap() {

    for(int i = 0 ; i < mapY ; i++) {
        for(int j = 0 ; j < mapX ; j++) {

            move(i,j);
            if(map[i][j] == 'B') {
                attron(COLOR_PAIR(4));
            } else if(map[i][j] == 'Y') {
                attron(COLOR_PAIR(5));
            } else if(map[i][j] == 'L') {
                attron(COLOR_PAIR(12));
            } else if(map[i][j] == 'G') {
                attron(COLOR_PAIR(10));
            } else if(map[i][j] == 'P') {
                attron(COLOR_PAIR(14));
            } else {
                attron(COLOR_PAIR(2));
            }
            addch(map[i][j]);

        }
    }

}


void Visualisation::setDrawingColor(PaintColor paintColor) {
    switch(paintColor) {
        case RED:
            attron(COLOR_PAIR(9));
            break;
        case GREEN:
            attron(COLOR_PAIR(10));
            break;
        case CYAN:
            attron(COLOR_PAIR(13));
            break;
        case MAGENTA:
            attron(COLOR_PAIR(14));
            break;
        }
}

void Visualisation::setDrawingColorWithLabel(PaintColor paintColor) {
    switch(paintColor) {
        case RED:
            attron(COLOR_PAIR(16));
            break;
        case GREEN:
            attron(COLOR_PAIR(17));
            break;
        case CYAN:
            attron(COLOR_PAIR(18));
            break;
        case MAGENTA:
            attron(COLOR_PAIR(19));
            break;
        }
}

void Visualisation::start(Wall* wall, Artist** artists, int numberOfArtists, Cleaner** cleaners, int numberOfCleaners, PaintSupply* paintSupply, Hotel* hotel) {

    loadMap();

    // main loop
    int ch;
    nodelay(stdscr, TRUE);
    for (;;) {
        if ((ch = getch()) != 27) {

            // handle configuration keys
            if(ch == 'z' && Randomness::randomnessBase >= 310) {
                Randomness::randomnessBase -= 10;
            } else if(ch == 'x') {
                Randomness::randomnessBase += 10;
            } else if(ch == 'c' && Randomness::randomnessRange >= 710) {
                Randomness::randomnessRange -= 10;
            } else if (ch == 'v') {
                Randomness::randomnessRange += 10;
            }

            clear();
            drawMap();
            drawConfiguration();

            drawArtistsInfo(artists, numberOfArtists);
            drawCleanersInfo(cleaners, numberOfCleaners);

            drawWall(wall);

            drawHotel(hotel);

            drawArtistsNearWall(artists, numberOfArtists);
            drawArtistsWaiting(artists, numberOfArtists);
            drawArtistsWaitingForRefill(artists, numberOfArtists);
            drawArtistRefilling(artists, numberOfArtists);

            drawCleanersNearWall(cleaners, numberOfCleaners);
            drawCleanersWaiting(cleaners, numberOfCleaners);
            drawCleanersWaitingForRoom(cleaners, numberOfCleaners);
            drawCleanersSleeping(cleaners, numberOfCleaners);
            drawPaintSupply(paintSupply);

            timeout(125);
        }
        else {
            return;
        }

    }
}
