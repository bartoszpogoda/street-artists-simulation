#ifndef PAINTCAN_H
#define PAINTCAN_H

#include "colors.h"


class PaintCan
{
    PaintColor color;

    // in wall segment blocks
    int totalCapacity;
    int currentCapacity;


public:
    PaintCan(PaintColor color, int totalCapacity) : color(color), totalCapacity(totalCapacity), currentCapacity(totalCapacity) {}

    PaintColor getColor() { return this->color; }

    int getTotalCapacity() { return this->totalCapacity; }
    int getCurrentCapacity() { return this->currentCapacity; }

    void decrementCurrentCapacity() { this->currentCapacity = this->currentCapacity - 1; }

    void setCurrentCapacity(int currentCapacity) { this->currentCapacity = currentCapacity; }

};

#endif // PAINTCAN_H
