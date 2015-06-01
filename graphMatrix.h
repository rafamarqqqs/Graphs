#ifndef _graphMatrix_H_
#define _graphMatrix_H_

#include "graph.h"
#include "graphMatrix.h"

MatrixGraph* createMatrixGraph(int, int, int);
int addVertexMatrixGraph(MatrixGraph *);
int printMatrixGraph(MatrixGraph *);
int addEdgeMatrixGraph(MatrixGraph*, int, int, int);
int printAdjMatrixGraph(MatrixGraph*, int);
int removeEdgeMatrixGraph(MatrixGraph*, int, int);
void freeMatrixGraph(MatrixGraph**);
int getLighterEdgeMatrixGraph(MatrixGraph *);

MatrixGraph* getTransposedMatrixGraph(MatrixGraph *);
int breadthFirstSearchMatrixGraph(MatrixGraph *, int, int);
int depthFirstSearchMatrixGraph(MatrixGraph *, int, int, BYTE, ProcessDFS, int *);

ListGraph *toList(MatrixGraph *);

int topologicalOrdenationMatrixGraph(MatrixGraph *, int *);

MatrixGraph *kruskalMSTMatrixGraph(MatrixGraph *);
MatrixGraph *primMSTMatrixGraph(MatrixGraph *);
int printSumMatrixGraph(MatrixGraph *);
int dijkstraShortestPathMatrixGraph(MatrixGraph *, int, int);

#endif
