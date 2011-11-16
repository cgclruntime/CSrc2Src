#include "defs.h"

void initRand(LONG_T seed) {
    srand48(seed);
}

void getRandVals(DOUBLE_T* rv, LONG_T numRandVals) {
    LONG_T i;
    for (i=0; i<numRandVals; i++) {
        rv[i] = drand48();
    }
}
