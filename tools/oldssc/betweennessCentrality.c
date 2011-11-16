#include "defs.h"

double betweennessCentrality(graph* G, DOUBLE_T* BC) {

    LONG_T i, j, k, p, n;
    VERT_T* S;          /* stack of vertices in the order of non-decreasing 
                           distance from s. Also used for implicitly representing 
                           the BFS queue */
    dynArray* P;        /* predecessors of a vertex v on shortest paths from s */
    LONG_T* sig;        /* No. of shortest paths */
    LONG_T* d;          /* Length of shortest path between every pair */
    DOUBLE_T* del;      /* dependency of vertices */
    LONG_T* permV; 
    LONG_T start, end;
    LONG_T v, w;
    LONG_T numV;
    double time;
    double sum;

    /* numV: no. of vertices to run BFS from = 2^K4Approx */
    numV = 1<<K4Approx;
    n = G->n;
    permV = (LONG_T *) malloc(n*sizeof(LONG_T)); 
    /* generate a list of numV permuted vertices */
    for (i=0; i<n; i++) {
        permV[i] = i;
    }
    srand48(SCALE*387543);
    for (i=0; i<n; i++) {
        j = lrand48() % n;
        /* Swap permV[i] and permV[j] */
        k = permV[i];
        permV[i] = permV[j];
        permV[j] = k;
    } 
    
    time = get_seconds();

    S   = (VERT_T *) malloc(n*sizeof(VERT_T));
    P   = (dynArray *) calloc(n, sizeof(dynArray));
    sig = (LONG_T *) malloc(n*sizeof(LONG_T));
    d   = (LONG_T *) malloc(n*sizeof(LONG_T));
    del = (DOUBLE_T *) malloc(n*sizeof(DOUBLE_T));
    
    for (i=0; i<n; i++) {
        initDynArray(&P[i]);    
        d[i] = -1;    
        del[i] = 0;
    }

    for (p=0; p<numV; p++) {

        i = permV[p];
        
        sig[i] = 1;
        d[i] = 0;

        start = 0;
        S[0] = i;
        end = 1;

        while (end - start > 0) {

            v = S[start];

            for (j=G->numEdges[v]; j<G->numEdges[v+1]; j++) {

                /* Filter edges with weights divisible by 8 */
                if ((G->weight[j] & 7) != 0) {
                    w = G->endV[j];

                    if (v != w) {

                        /* w found for the first time? */ 
                        if (d[w] < 0) {
                            S[end++] = w;
                            d[w] = d[v] + 1;
                            sig[w] = 0;
                        }

                        if (d[w] == d[v] + 1) {
                            sig[w] = sig[w] + sig[v];
                            dynArrayInsert(&P[w], v);
                        }

                    }
                }
            }

            start++;
                
        }

        for (j=end-1; j>0; j--) {
            w = S[j];
            for (k = 0; k<P[w].count; k++) {
                v = P[w].vals[k];
                del[v] = del[v] + sig[v]*(1+del[w])/sig[w];
            }
            BC[w] += del[w];
        } 

        for (j=end-1; j>=0; j--) {
            w = S[j];
            d[w] = -1;
            del[w] = 0;
            P[w].count = 0;
        }
    }

    free(S);
    for (j=0; j<n; j++)
        freeDynArray(&P[j]);
    free(P);
    free(sig);
    free(d);
    free(del);
    
    time = get_seconds() - time;

    free(permV);

    /* Verification */
    sum = 0;
    for (i=0; i<n; i++) {
        sum += BC[i];
    }
    printf("BC sum: %lf\n", (sum*n)/numV); 
    
    return time;
}
