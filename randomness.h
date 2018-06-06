#ifndef RANDOMNESS
#define RANDOMNESS

#include "thread"

class Randomness {

public:
    static int randomnessBase;
    static int randomnessRange;

    static void waitNRandomSteps(int n);

};

#endif // RANDOMNESS

