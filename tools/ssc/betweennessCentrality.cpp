#include "defs.h"
#include<iostream>
#include "ParaHeader.h"
long int S[20][131072];
long int sig[20][131072];
long int d[20][131072];
double del[20][131072];
double SBC[20][131072];


void bc(graph* G, DOUBLE_T* BC, LONG_T n,LONG_T* permV,LONG_T pbegin,LONG_T pend,int id) {
    //VERT_T* S;
    dynArray* P; /* predecessors of a vertex v on shortest paths from s */
    //LONG_T* sig; /* No. of shortest paths */
    //LONG_T* d; /* Length of shortest path between every pair */
    //DOUBLE_T* del; /* dependency of vertices */
    LONG_T i, v, w, start, end;

    if (pbegin>pend) return;

    //S = (VERT_T *) malloc(n * sizeof (VERT_T));
    P = (dynArray *) calloc(n, sizeof (dynArray));
    //sig = (LONG_T *) malloc(n * sizeof (LONG_T));
    //d = (LONG_T *) malloc(n * sizeof (LONG_T));
    //del = (DOUBLE_T *) malloc(n * sizeof (DOUBLE_T));
    std::cout<<id<<"in\n";
    for (int i=0;i<n;i++) initDynArray(&P[i]);
for (int now=pbegin;now<=pend;now++) {
    
    
    i = permV[now];
    sig[id][i] = 1;
    d[id][i] = 0;

    start = 0;
    S[id][0] = i;
    end = 1;
    LONG_T j, k;

    while (end - start > 0) {

        v = S[id][start];

        for (j = G->numEdges[v]; j < G->numEdges[v + 1]; j++) {


            if ((G->weight[j] & 7) != 0) {
                w = G->endV[j];

                if (v != w) {


                    if (d[id][w] < 0) {
                        S[id][end++] = w;
                        d[id][w] = d[id][v] + 1;
                        sig[id][w] = 0;
                    }

                    if (d[id][w] == d[id][v] + 1) {
                        sig[id][w] = sig[id][w] + sig[id][v];

                        dynArrayInsert(&P[w], v);
                    }

                }
            }
        }

        start++;

    }
    for (j = end - 1; j > 0; j--) {
        w = S[id][j];
        for (k = 0; k < P[w].count; k++) {
            v = P[w].vals[k];
            del[id][v] = del[id][v] + sig[id][v]*(1 + del[id][w]) / sig[id][w];
        }
        SBC[id][w] += del[id][w];
    }

    for (j = end - 1; j >= 0; j--) {
        w = S[id][j];
        d[id][w] = -1;
        del[id][w] = 0;
        P[w].count = 0;
    }
}
    for (int j = 0; j < n; j++)
        freeDynArray(&P[j]);
    free(P);
    std::cout<<id<<"finish\n";
}

void _fake_bc_2(graph* G, DOUBLE_T* BC, LONG_T n, LONG_T* permV,LONG_T pbegin,LONG_T pend,int id, FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP2, pCtxt->m_uiEBP2);	
	pCtxt->m_iArgsLen = pCtxt->m_uiEBP1-pCtxt->m_uiEBP2-8;
	memcpy(pCtxt->m_acArgs, (void *)(pCtxt->m_uiEBP2+8), pCtxt->m_iArgsLen);
}

void _fake_bc_1(graph* G, DOUBLE_T* BC, LONG_T n,LONG_T* permV,LONG_T pbegin,LONG_T pend,int id, FuncContext *pCtxt)
{
	get_stack_info(pCtxt->m_uiESP1, pCtxt->m_uiEBP1);
	_fake_bc_2(G,BC,n,permV,pbegin,pend,id, pCtxt);
}


double betweennessCentrality(graph* G, DOUBLE_T* BC,int iPoolSize) {

    LONG_T i, j, k, p, n;

    LONG_T* permV;
    LONG_T v, w;
    LONG_T numV;
    double time;
    double sum;

    /* numV: no. of vertices to run BFS from = 2^K4Approx */
    numV = 1 << K4Approx;
    n = G->n;
    permV = (LONG_T *) malloc(n * sizeof (LONG_T));
    /* generate a list of numV permuted vertices */
    for (i = 0; i < n; i++) {
        permV[i] = i;
    }
    srand48(SCALE * 387543);
    for (i = 0; i < n; i++) {
        j = lrand48() % n;
        /* Swap permV[i] and permV[j] */
        k = permV[i];
        permV[i] = permV[j];
        permV[j] = k;
    }

    time = get_seconds();

    ActionScope s0(1);
    /*for (p = 0; p < numV; p++) {
        bc(G, BC, n, permV[p]);
        FuncContext *pCtxt = new FuncContext(s0, (void *)bc, "aaa");	
        _fake_bc_1(G, BC, n, permV[p], pCtxt);
        parallelFunc(pCtxt);
    }*/
    int pb,pe;
    iPoolSize--;
    for (i = 0; i < n; i++) {
        for (int j=0;j<iPoolSize;j++) d[j][i] = -1;
        //del[id][i] = 0;
    }
    for (p=0;p<iPoolSize;p++) {
        pb=numV/iPoolSize*p;
        pe=numV/iPoolSize*(p+1)-1;
        if (p==iPoolSize-1) pe=numV-1;
        //bc(G,BC,n,permV,pb,pe);
        FuncContext *pCtxt = new FuncContext(s0, (void *)bc, "aaa");	
        _fake_bc_1(G, BC, n, permV,pb,pe,p, pCtxt);
        parallelFunc(pCtxt);
    }
    
    s0.exitScope();
    time = get_seconds() - time;

    free(permV);

    /* Verification */
    sum = 0;
    for (int p=0;p<iPoolSize;p++) {
        for (i = 0; i < n; i++) {
            sum += SBC[p][i];
        }
    }
    printf("BC sum: %lf\n", (sum * n) / numV);
    
    return time;
}
