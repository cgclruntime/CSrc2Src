#include "defs.h"

double get_seconds() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return (double) (tp.tv_sec + ((1e-6)*tp.tv_usec));
}

LONG_T BinarySearchEdgeListL(LONG_T* array, LONG_T m, LONG_T i) {

    LONG_T h, l, md;

    if (i==0)
        return 0;

    h = m;
    l = 0;
    md = m/2;

    while (h-l > 0) {

        md = (h+l)/2;

        if ((array[md] <= i) && (array[md+1] > i)) {
            return md;
        }

        if (array[md] > i) {
            h = md;
        }

        if ((array[md] <= i) && (array[md+1] <= i)) {
            l = md+1;
        }
    }

    return (md-1);
}

void dynArraySortedInsert(dynArray* l, LONG_T elem, LONG_T pos) {

    LONG_T i;
    LONG_T* newArray;

    if (l->count == ARRAY_INIT_SIZE) {
        
        /* double the size */
        newArray = (long *) malloc(2*ARRAY_INIT_SIZE*sizeof(long));
        l->max_size = 2*ARRAY_INIT_SIZE;
        for (i=0; i<l->count; i++) {
            newArray[i] = (l->vals)[i];
        }
        l->vals = newArray;
        
    } else if (l->count == l->max_size) {

        /* double the size */
        newArray = (long *) malloc(2*(l->max_size)*sizeof(long));
        l->max_size = 2 * (l->max_size);
        for (i=0; i<l->count; i++) {
            newArray[i] = (l->vals)[i];
        }
        free(l->vals);
        l->vals = newArray;

    }
    
    /* shift all the values to the right */
    for (i=l->count-1; i>=pos; i--) {
        (l->vals)[i+1] = (l->vals)[i];    
    }

    /* insert in correct position */
    (l->vals)[pos] = elem;
    l->count = l->count + 1;

}

LONG_T dynArraySortedInsertPos(dynArray* l, LONG_T elem) {

    LONG_T i;

    if (l->count==0) {
        return 0;
    }
    
    for (i=0; i<l->count; i++) {
        if ((l->vals)[i] == elem)
            return -1;
        if ((l->vals)[i] > elem)
            return i;
    }
    
    return l->count;
}


void initDynArray(dynArray* l) {
    
    l->vals = NULL;
    l->count = 0;
    l->max_size = 0;

}

void clearDynArray(dynArray* l) {

    l->count = 0;

}

void freeDynArray(dynArray* l) {
    if (l->vals != NULL)
        free(l->vals);
}


void dynArrayInsert(dynArray* l, LONG_T elem) {

    LONG_T* newVals;
    LONG_T i;

    if (l->max_size == 0) {
        /* Create a new list */
        l->vals = (long *) malloc(ARRAY_INIT_SIZE*sizeof(long));
        l->max_size = ARRAY_INIT_SIZE;
        l->vals[0] = elem;
        l->count = 1;
        return;
    }

    if (l->max_size != l->count) {
        l->vals[l->count] = elem;
        l->count = l->count + 1;
        return;

    } else {

        /* Increase array capacity by ARRAY_INIT_SIZE */
        l->max_size = l->max_size + ARRAY_INIT_SIZE;
        newVals = (LONG_T *) malloc(l->max_size*sizeof(LONG_T));
        for (i=0; i<l->count; i++) {
            newVals[i] = l->vals[i];
        }
        free(l->vals);
        l->vals = newVals;
        l->vals[l->count] = elem;
        l->count = l->count + 1;
        return;
    }
}
