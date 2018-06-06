
#include "randomness.h"

int Randomness::randomnessBase = 2000;
int Randomness::randomnessRange = 2000;

void Randomness::waitNRandomSteps(int n) {

    int randomStep = (randomnessBase + rand() % randomnessRange)/10;

    for(int currentProgress = 0; currentProgress < n ; currentProgress++) {
        std::this_thread::sleep_for (std::chrono::milliseconds(randomStep));
    }
}
