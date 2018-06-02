#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "paintsupply.h"

class Supplier
{
    volatile bool isRunning;
    PaintSupply* paintSupply;

    PaintColor* colors;
    int colorsLength;

    int* sizes;
    int sizesLength;


    int currentProgress; // out of 10
    int randomStepTime();
    void waitNSteps(int n, int stepTime);
public:
    Supplier(PaintSupply* paintSupply, PaintColor* colors, int colorslength, int* sizes, int sizesLength);

    void lifeCycle();

    void stop();
};

#endif // SUPPLIER_H
