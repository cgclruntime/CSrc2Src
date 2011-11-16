#include "defs.h"

/* Global variables */
INT_T SCALE;
LONG_T N;
LONG_T M;

/* R-MAT parameters */
DOUBLE_T A;
DOUBLE_T B;
DOUBLE_T C;
DOUBLE_T D;

WEIGHT_T MaxIntWeight;
INT_T SubGraphPathLength;
INT_T K4Approx;

void init(int SCALE) {

	/* Binary Scaling Heuristic */
	/* SCALE */

    N = 1<<SCALE;
    M = 8*N;

    /* R-MAT parameters */
    A = 0.6;
    B = (1-A)/3.0;
    C = B;
    D = B;

    MaxIntWeight = (1<<SCALE);
    SubGraphPathLength = 3;

    if (SCALE < 10)
        K4Approx = SCALE;
    else 
        K4Approx = 10;
}
