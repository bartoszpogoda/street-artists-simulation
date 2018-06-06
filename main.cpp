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
#include "paintsupply.h"
#include "supplier.h"
#include "colors.h"
#include "hotel.h"

const int width = 7;
const int height = 10;
const int numberOfArtists = 5;
const int numberOfCleaners = 6;
const int numberOfSuppliers = 2;
const int supplySize = 13;
const int hotelSize = 3;


Wall* createWall() {
    return new Wall(width, height);
}

PaintSupply* createPaintSupply() {
    return new PaintSupply(supplySize);
}

Hotel* createHotel() {
    return new Hotel(hotelSize);
}


Supplier** createSuppliers(PaintSupply* paintSupply) {
    Supplier** suppliers = new Supplier*[numberOfSuppliers];

    suppliers[0] = new Supplier(paintSupply, new PaintColor[4] {RED, RED, RED, CYAN}, 4, new int[2]{4,8}, 2);
    suppliers[1] = new Supplier(paintSupply, new PaintColor[1] {GREEN}, 1, new int[1]{4}, 1);

    return suppliers;
}

Artist** createArtists(Wall* wall, PaintSupply* paintSupply) {
    Artist** artists = new Artist*[numberOfArtists];
    for(int i = 0 ; i < numberOfArtists ; i++) {
      artists[i] = new Artist(i, wall, paintSupply);
    }
    return artists;
}

Cleaner** createCleaners(Wall* wall, Hotel* hotel) {
    Cleaner** cleaners = new Cleaner*[numberOfCleaners];
    for(int i = 0 ; i < numberOfCleaners ; i++) {
      cleaners[i] = new Cleaner(i, wall, hotel);
    }
    return cleaners;
}

int main(int argc, char *argv[])
{

    srand(time(NULL));

    Wall* wall = createWall();
    Hotel* hotel = createHotel();
    PaintSupply* paintSupply = createPaintSupply();
    Artist** artists = createArtists(wall, paintSupply);
    Cleaner** cleaners = createCleaners(wall, hotel);
    Supplier** suppliers = createSuppliers(paintSupply);

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

    // start suppliers
    std::thread* supplierThreads = new std::thread[numberOfSuppliers];
    for(int i = 0 ; i < numberOfSuppliers; i++) {
        supplierThreads[i] = std::thread(&Supplier::lifeCycle, suppliers[i]);
    }

    Visualisation visualisation = Visualisation();
    visualisation.start(wall, artists, numberOfArtists, cleaners, numberOfCleaners, paintSupply, hotel);

    // after ESC was pressed
    for(int i = 0 ; i < numberOfCleaners ; i++) {
        cleaners[i]->stop();
    }
    for(int i = 0 ; i < numberOfArtists ; i++) {
        artists[i]->stop();
    }
    for(int i = 0 ; i < numberOfSuppliers ; i++) {
        suppliers[i]->stop();
    }


    for(int i = 0 ; i < numberOfSuppliers; i++) {
        supplierThreads[i].join();
    }

    for(int i = 0 ; i < numberOfCleaners; i++) {
        cleanerThreads[i].join();
    }

    for(int i = 0 ; i < numberOfArtists; i++) {
        artistThreads[i].join();
    }



    // clean up
    for(int i = 0 ; i < numberOfSuppliers ; i++) {
        delete suppliers[i];
    }
    for(int i = 0 ; i < numberOfCleaners ; i++) {
        delete cleaners[i];
    }
    for(int i = 0 ; i < numberOfArtists ; i++) {
        delete artists[i];
    }
    delete[] suppliers;
    delete[] cleaners;
    delete[] artists;

    delete[] supplierThreads;
    delete[] cleanerThreads;
    delete[] artistThreads;

    return 0;
}
