#include "defs.h"

double computeGraph(graph* G, graphSDG* SDGdata) {

    VERT_T* endV;
    LONG_T u, *degree, *numEdges, *pos;
    WEIGHT_T* w;
    LONG_T i, j, n, m;
    double time;

    n = N;
    m = M;

    time = get_seconds(); 
    
    endV   = (VERT_T *) malloc(m* sizeof(VERT_T));
    assert(endV != NULL);
    degree = (LONG_T *) calloc(n, sizeof(LONG_T));
    assert(degree != NULL);
    numEdges = (LONG_T *) malloc((n+1)*sizeof(LONG_T));
    assert(numEdges != NULL);
    pos = (LONG_T *) malloc(m*sizeof(LONG_T));
    assert(pos != NULL);
    w = (WEIGHT_T *) malloc(m*sizeof(WEIGHT_T));
    assert(w != NULL);
   
    /* Get the degree of each vertex */ 
    for (i=0; i<m; i++) {
        u = SDGdata->startVertex[i];
        pos[i] = degree[u]++;
    } 

    /* prefix sums over the degree */
    numEdges[0] = 0; 
    for (i=1; i<n+1; i++) {
        numEdges[i] = numEdges[i-1] + degree[i-1];
    }
 
    for (i=0; i<m; i++) {
        u = SDGdata->startVertex[i];
        j = numEdges[u] + pos[i];
        endV[j] = SDGdata->endVertex[i];
        w[j] = SDGdata->weight[i]; 
    }
 
    free(degree);
    free(pos);
 
    G->n = n;
    G->m = m;
    G->numEdges = numEdges;
    G->endV = endV;
    G->weight = w;

    /* Verification */
    /*
    fprintf(stderr, "SDG data:\n");
    for (i=0; i<SDGdata->m; i++) {
        fprintf(stderr, "[%ld %ld %ld] ", SDGdata->startVertex[i], 
                SDGdata->endVertex[i], SDGdata->weight[i]);
    }
 

    for (i=0; i<G->n + 1; i++) {
        fprintf(stderr, "[%ld] ", G->numEdges[i]);
    }
    
    fprintf(stderr, "\nGraph:\n");
    for (i=0; i<G->n; i++) {
        for (j=G->numEdges[i]; j<G->numEdges[i+1]; j++) {
            fprintf(stderr, "[%ld %ld %ld] ", i, G->endV[j], G->weight[j]);
        }
    }
    */ 

    free(SDGdata->startVertex);
    free(SDGdata->endVertex);
    free(SDGdata->weight);
    time = get_seconds() - time;
    return time;
}
