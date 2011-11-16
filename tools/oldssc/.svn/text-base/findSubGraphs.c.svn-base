#include "defs.h"

double findSubGraphs(graph* G, V** extractedSubGraphs, 
        edge* maxIntWtList, int maxIntWtListSize) {

    LONG_T i, j, k, n, verticesVisited, currIndex;
    char* visited;
    INT_T depth;
    V *VList;
    double time;

    time = get_seconds();
    n = G->n;

    visited = (char *) malloc(n*sizeof(char));

    for(i=0; i<maxIntWtListSize; i++) {

        VList = extractedSubGraphs[i]; 

        for (k=0; k<n; k++)
            visited[k] = (char) 0;
    
        VList[0].num = maxIntWtList[i].startVertex;
        VList[0].depth = -1;

        VList[1].num = maxIntWtList[i].endVertex;
        VList[1].depth = 1;
            
        visited[(VList[0]).num] = (char) 1;
        visited[(VList[1]).num] = (char) 1;

        depth = 1;
        verticesVisited = 2;
        currIndex = 1;

        while ((depth < SubGraphPathLength) || (verticesVisited == n)) {
            depth = VList[currIndex].depth+1;
            for (j=G->numEdges[VList[currIndex].num];
                j<G->numEdges[VList[currIndex].num+1]; j++) {
                if (visited[G->endV[j]] == (char) 0) {
                    visited[G->endV[j]] = (char) 1;
                    VList[verticesVisited].num = G->endV[j];
                    VList[verticesVisited].depth = depth;
                    verticesVisited = verticesVisited + 1;
                }
            }
            if ((currIndex < verticesVisited - 1) && (verticesVisited < n))  {
                currIndex++;
                depth = VList[currIndex].depth;
            } else 
                break;
        }
        extractedSubGraphs[i] = VList;
    }

    free(visited);
    time = get_seconds() - time;
    return time;
    /*
    for (i=0; i<maxIntWtListSize; i++) {

        for (j=0; j<n; j++) {
            fprintf(stderr, "[%ld %ld] ", extractedSubGraphs[i][j].num, extractedSubGraphs[i][j].depth);
        }
        fprintf(stderr, "\n");

    }
    */
}
