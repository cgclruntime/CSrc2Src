#include "defs.h"

double getStartLists(graph* G, edge** maxIntWtListPtr, 
        INT_T* maxIntWtListSizePtr) {

    LONG_T i, n, m, maxWeight, count, tmpListSize;
    INT_T maxIntWtListSize;
    edge *tmpList, *tmpList2, *maxIntWtList;
    double time;

    time = get_seconds();

    n = G->n;
    m = G->m;

    maxWeight = -1;

    /* Find the max weight */
    for (i=0; i<m; i++) {
        if (G->weight[i] > maxWeight) {
            maxWeight = G->weight[i];
        }   
    }
   
    /* Allocate memory for partial edge list on each thread */
    tmpListSize = 10;
    tmpList = (edge *) malloc(tmpListSize*sizeof(edge));
    count = 0;
    for (i=0; i<m; i++) {
        if (G->weight[i] == maxWeight) {
            tmpList[count].endVertex = G->endV[i];
            tmpList[count].e = i;
            tmpList[count].w = maxWeight;
            count++;
            if (count == tmpListSize) {
                /* Allocate more memory */
                tmpList2 = (edge*) malloc(2*tmpListSize*sizeof(edge));
                memcpy(tmpList2, tmpList, tmpListSize*sizeof(edge));
                tmpListSize = tmpListSize * 2;
                free(tmpList);
                tmpList = tmpList2;
            }
        }
    }
  
    maxIntWtList = tmpList;
    maxIntWtListSize = count;
    for (i=0; i<maxIntWtListSize; i++) {    
        maxIntWtList[i].startVertex = 
            BinarySearchEdgeListL(G->numEdges, n, maxIntWtList[i].e);
    }

    free(*maxIntWtListPtr);
    *maxIntWtListPtr = maxIntWtList;
    *maxIntWtListSizePtr = maxIntWtListSize;
    time = get_seconds() - time;
    return time;    
    /*    
    maxIntWtList = *maxIntWtListPtr;
    for (i=0; i<*maxIntWtListSizePtr; i++) {
        fprintf(stderr, "[%ld %ld %ld %ld] ", maxIntWtList[i].startVertex, 
                maxIntWtList[i].endVertex, maxIntWtList[i].e, maxIntWtList[i].w);
    }
    */ 
}
