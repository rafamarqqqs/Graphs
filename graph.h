#ifndef _graph_H_
#define _graph_H_

#include "list.h"
#include <stdarg.h>

typedef struct listgraph {

	List **vector;
	int size;
	int is_digraph;

} ListGraph;

typedef struct matrixgraph {
	
	int **matrix;
	int size;
	int is_digraph;

} MatrixGraph;

typedef struct graph {

	union{
		MatrixGraph *matrixGraph;
		ListGraph *listGraph;
	};
	
	char type;
	int size;

} Graph;

//usado para ordenação topológica
typedef struct index{
	int content;
	int position;
} TopOrdIdx;

//usado para condição na DFS
typedef unsigned char BYTE;

//usado para processar a dfs de diferentes formas
typedef int(*ProcessDFS)(int, int, int, int *, int *, int *, int *);

typedef struct set{
	int *vector;
	int size;
} Set;

int compareOrdTop(const void *, const void *);
int topologicalProcess(int, int, int, int *, int *, int *, int *);

Graph *createGraph(char, char, int, int);
void getAdj(Graph *, int);
void addVertex(Graph *);
void printGraph(Graph *);
void addEdge(Graph *, int, int, int);
void freeGraph(Graph **);
void removeEdge(Graph *, int, int);
void getLighterEdge(Graph *);
Graph *getTransposed(Graph *);
int buildPath(int *, int, int);
int breadthFirstSearch(Graph *, int, int);
int depthFirstSearch(Graph *, int, int);
int topologicalOrdenation(Graph *, int *);
void transformGraph(Graph *);
Graph *kruskalMST(Graph *);
Graph *primMST(Graph *);
int printSum(Graph *);
int dijkstraShortestPath(Graph *, int, int);

#endif
