#include "visualisation.h"
#include "ncurses.h"
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


    bkgd(COLOR_PAIR(1));
}

void Visualisation::drawLegend() {

    attron(COLOR_PAIR(6));
    move(0,1);
    printw("Legend: ");

    attron(COLOR_PAIR(4));
    move(2,3);
    addch(' ');
    attron(COLOR_PAIR(1));
    printw(" Thinking progress");

    attron(COLOR_PAIR(5));
    move(3,3);
    addch(' ');
    attron(COLOR_PAIR(1));
    printw(" Eating progress");

    attron(COLOR_PAIR(3));
    move(4,3);
    addch('Y');
    attron(COLOR_PAIR(1));
    printw(" Fork in use");

    attron(COLOR_PAIR(2));
    move(5,3);
    addch('Y');
    attron(COLOR_PAIR(1));
    printw(" Fork free");

    move(6,1);
    attron(COLOR_PAIR(1));
    printw("\\o/ Philo with hands");


    attron(COLOR_PAIR(6));
    move(0,30);
    printw("Visualisation: ");

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
            if(paintColor == RED) {
                attron(COLOR_PAIR(9));
            } else {
                attron(COLOR_PAIR(10));
            }
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
            } else {
                attron(COLOR_PAIR(2));
            }
            addch(map[i][j]);

        }
    }

}

void Visualisation::start(Wall* wall, Artist** artists, int numberOfArtists, Cleaner** cleaners, int numberOfCleaners) {

    loadMap();

    // main loop
    int ch;
    nodelay(stdscr, TRUE);
    for (;;) {
        if ((ch = getch()) != 27) {

            clear();
            drawMap();

            drawWall(wall);
            drawArtistsNearWall(artists, numberOfArtists);
            drawCleanersNearWall(cleaners, numberOfCleaners);

            // DBG number of free segments
            move(10,10);
            attron(COLOR_PAIR(1));
            printw(std::to_string(wall->getFreeSegmentsCount()).c_str());

            timeout(125);
        }
        else {
            return;
        }

    }
}
