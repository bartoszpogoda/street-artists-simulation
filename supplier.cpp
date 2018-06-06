#include "supplier.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "randomness.h"

Supplier::Supplier(PaintSupply* paintSupply, PaintColor* colors, int colorsLength, int* sizes, int sizesLength) :
    paintSupply(paintSupply), isRunning(true),
    colors(colors), colorsLength(colorsLength),
    sizes(sizes), sizesLength(sizesLength)
{

}

void Supplier::lifeCycle() {

    while(this->isRunning) {

        Randomness::waitNRandomSteps(10);
        paintSupply->supplyPaintCan(PaintCan(colors[rand() % colorsLength],sizes[rand() % sizesLength]));

    }

}

void Supplier::stop() {
    this->isRunning = false;
}
