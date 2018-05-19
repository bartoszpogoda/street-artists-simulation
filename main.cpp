#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <mutex>
#include <ncurses.h>

#include "artist.h"
#include "cleaner.h"
#include "visualisation.h"
#include "fork.h"

const int width = 7;
const int height = 3;
const int numberOfArtists = 5;
const int numberOfCleaners = 1;

Wall* createWall() {
    return new Wall(width, height);
}

Artist** createArtists(Wall* wall) {
    Artist** artists = new Artist*[numberOfArtists];
    for(int i = 0 ; i < numberOfArtists ; i++) {
      artists[i] = new Artist(i, wall);
    }
    return artists;
}

Cleaner** createCleaners(Wall* wall) {
    Cleaner** cleaners = new Cleaner*[numberOfCleaners];
    for(int i = 0 ; i < numberOfCleaners ; i++) {
      cleaners[i] = new Cleaner(i, wall);
    }
    return cleaners;
}

int main(int argc, char *argv[])
{

    srand(time(NULL));

    Wall* wall = createWall();
    std::cout << "b";
    Artist** artists = createArtists(wall);
    Cleaner** cleaners = createCleaners(wall);

    std::cout << "c";

    // start artists
    std::thread* artistThreads = new std::thread[numberOfArtists];
    for(int i = 0 ; i < numberOfArtists ; i++) {
        artistThreads[i] = std::thread(&Artist::lifeCycle, artists[i]);
    }

    // start cleaners
    std::thread* cleanerThreads = new std::thread[numberOfCleaners];
    for(int i = 0 ; i < numberOfCleaners; i++) {
        cleanerThreads[i] = std::thread(&Cleaner::lifeCycle, cleaners[i]);
    }

    std::cout << "d";

    Visualisation visualisation = Visualisation();
    visualisation.start(wall, artists, cleaners);

    // after ESC was pressed
    for(int i = 0 ; i < numberOfArtists ; i++) {
        artists[i]->stop();
    }

    // stop join and clean up cleaners the same way TODO

    for(int i = 0 ; i < numberOfArtists; i++) {
        artistThreads[i].join();
    }


    // clean up
    for(int i = 0 ; i < numberOfArtists ; i++) {
        delete artists[i];
    }
    delete[] artists;

    delete[] artistThreads;

    return 0;
}
