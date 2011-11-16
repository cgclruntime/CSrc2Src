#ifndef _DEFS_H
#define _DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#define INT_T int
#define DOUBLE_T double

/* long must be 64-bit */
#define LONG_T long int

/* Edge Weights are 64-bit */
#define WEIGHT_T LONG_T

/* Vertex IDs must be 64-bit */
#define VERT_T LONG_T

/* Data structure for representing tuples
 * in the Scalable Data Generator */
typedef struct 
{

    /* Edge lists */
    VERT_T* startVertex;
    VERT_T* endVertex;
    WEIGHT_T* weight;
    
    /* No. of directed edges */     
    LONG_T m;

    /* No. of vertices */
    LONG_T n;

} graphSDG;

/* The graph data structure*/
typedef struct
{ 
    LONG_T n;
    LONG_T m;

    /* Directed edges out of vertex vi (say, k edges -- v1, v2, ... vk) 
     * are stored in the contiguous block endV[numEdges[i] .. numEdges[i+1]]
     * So, numEdges[i+1] - numEdges[i] = k in this case */
    VERT_T* endV;
    LONG_T* numEdges;
    WEIGHT_T* weight;

} graph;

/* Edge data structure for Kernel 2 */
typedef struct
{
    VERT_T startVertex;
    VERT_T endVertex;
    WEIGHT_T w;
    LONG_T e;
} edge;

/* Kernel 3 outputs a list of visited vertices in a Breadth-First 
 * Search upto a depth subGraphPathLength */
typedef struct
{
    VERT_T num;
    INT_T depth;
} V;

typedef struct {
    LONG_T* vals;
    LONG_T count;
	LONG_T max_size;
} dynArray;

/* Global variables */
extern INT_T SCALE;
extern LONG_T N;
extern LONG_T M;

/* R-MAT parameters */
extern DOUBLE_T A;
extern DOUBLE_T B;
extern DOUBLE_T C;
extern DOUBLE_T D;

extern WEIGHT_T MaxIntWeight;
extern INT_T SubGraphPathLength;
extern INT_T K4Approx;

/* Function declarations */

void init(int);

/* utils.c */
DOUBLE_T get_seconds(void);
LONG_T BinarySearchEdgeListL(LONG_T *, LONG_T, LONG_T);

#define ARRAY_INIT_SIZE 8
LONG_T dynArraySortedInsertPos(dynArray*, LONG_T);
void dynArraySortedInsert(dynArray*, LONG_T, LONG_T);
void dynArrayInsert(dynArray*, LONG_T);
void initDynArray(dynArray*);
void clearDynArray(dynArray*);
void freeDynArray(dynArray*);

double genScalData(graphSDG*);
void choosePartition(DOUBLE_T, LONG_T *, LONG_T *, LONG_T, 
    DOUBLE_T, DOUBLE_T, DOUBLE_T, DOUBLE_T);
inline void varyParams(DOUBLE_T *, INT_T, DOUBLE_T *, DOUBLE_T *,
    DOUBLE_T *, DOUBLE_T *);

double computeGraph(graph*, graphSDG*);
double getStartLists(graph*, edge**, INT_T*);
double findSubGraphs(graph*, V**, edge*, INT_T);
double betweennessCentrality(graph*, DOUBLE_T *);
#endif
