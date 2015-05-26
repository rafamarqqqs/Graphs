#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "graphList.h"
#include "graphMatrix.h"

#define DECIDER(switcher, listFunction, matrixFunction) {										\
													\
	switch(switcher){										\
													\
		case'M': matrixFunction;								\
			 break;										\
		case'L': listFunction;									\
			 break;										\
	}												\
}\

#define checkDigraph(graph, option1, option2) (graph -> is_digraph == 1 ? option1 : option2)

Graph *createGraph(char type, char isDigraph, int vertex, int edges){
	Graph *newGraph = (Graph *) malloc(sizeof(Graph));

	int isDigraphAux = isDigraph == 'D' ? 1 : 0;

	switch(type){
		
		case'M': newGraph -> matrixGraph = createMatrixGraph(isDigraphAux, vertex, edges);
			 break;
		case'L': newGraph -> listGraph = createListGraph(isDigraphAux, vertex, edges);	
			 break;
	}
	
	newGraph -> type = type;
	newGraph -> size = vertex;

	return newGraph;
}

void addVertex(Graph *graph){
	if(!graph)
		return;
	DECIDER(graph -> type, addVertexListGraph(graph -> listGraph), addVertexMatrixGraph(graph -> matrixGraph));
}

void getAdj(Graph *graph, int id){
	if(!graph)
		return;
	DECIDER(graph -> type, printAdjListGraph(graph -> listGraph, id), printAdjMatrixGraph(graph -> matrixGraph, id));
}

void printGraph(Graph *graph){
	if(!graph)
		return;
	DECIDER(graph -> type, printListGraph(graph -> listGraph), printMatrixGraph(graph -> matrixGraph));
}

void addEdge(Graph *graph, int src, int dest, int weight){
	if(!graph)
		return;
	DECIDER(graph -> type, addEdgeListGraph(graph -> listGraph, src, dest, weight), addEdgeMatrixGraph(graph -> matrixGraph, src, dest, weight));
}

void removeEdge(Graph *graph, int src, int dest){
	if(!graph)
		return;
	DECIDER(graph -> type, removeEdgeListGraph(graph -> listGraph, src, dest), removeEdgeMatrixGraph(graph -> matrixGraph, src, dest));
}

Graph *getTransposed(Graph *graph){
	if(!graph)
		return NULL;

	Graph *newGraph = createGraph(graph -> type == 'M' ? 'M' : 'L', 'D', graph -> size, 0);
	
	DECIDER(newGraph -> type, 
	checkDigraph(graph -> listGraph, newGraph -> listGraph = getTransposedListGraph(graph -> listGraph), free(newGraph)), 
	checkDigraph(graph -> matrixGraph, newGraph -> matrixGraph = getTransposedMatrixGraph(graph -> matrixGraph), free(newGraph)));

	if(newGraph)
		return newGraph;

	return NULL;
}

void getLighterEdge(Graph *graph){
	if(!graph)
		return;
	DECIDER(graph -> type, getLighterEdgeListGraph(graph -> listGraph), getLighterEdgeMatrixGraph(graph -> matrixGraph));
}

void freeGraph(Graph **graph){
	if(!graph || !*graph)
		return;
	DECIDER((*graph) -> type, freeListGraph(&((*graph) -> listGraph)), freeMatrixGraph(&((*graph) -> matrixGraph)));

	free(*graph);
	*graph = NULL;
}

int breadthFirstSearch(Graph *graph, int src, int dest){
	if(!graph)
		return -1;
	DECIDER(graph -> type, breadthFirstSearchListGraph(graph -> listGraph, src, dest),
						   breadthFirstSearchMatrixGraph(graph -> matrixGraph, src, dest));

	return 1;
}

int searchVertexProcess(int size, int u, int searchedVertex, int *p, int *d, int *f, int *vector){
	return !(u - searchedVertex);
}

int depthFirstSearch(Graph *graph, int src, int dest){
	if(!graph)
		return -1;
	DECIDER(graph -> type, depthFirstSearchListGraph(graph -> listGraph, src, dest, 1, searchVertexProcess, NULL),
						   depthFirstSearchMatrixGraph(graph -> matrixGraph, src, dest, 1, searchVertexProcess, NULL));

	return 1;
}

int topologicalOrdenation(Graph *graph, int *vector){
	if(!graph)
		return -1;
	
	DECIDER(graph -> type, topologicalOrdenationListGraph(graph -> listGraph, vector), topologicalOrdenationMatrixGraph(graph -> matrixGraph, vector));

	return 1;
}

void transformGraph(Graph *graph){
	if(!graph)
		return;

	DECIDER(graph -> type, (graph -> matrixGraph = toMatrix(graph -> listGraph)), (graph -> listGraph = toList(graph -> matrixGraph)));

	graph -> type == 'L' ? (graph -> type = 'M') : (graph -> type = 'L');
}

int _buildPath(int *pVector, int pos, int start){
	if(pos == start){
		printf("%d ", pos);
		return 1;
	}
	else{
		if(pos >= 0){
			if(_buildPath(pVector, pVector[pos], start)){
				printf("%d ", pos);
				return 1;
			}
		}
		return 0;
	}
}

int buildPath(int *pVector, int pos, int start){
	int value = _buildPath(pVector, pos, start);
	printf("\n");
	return value;
}

//função de comparação para a ordenação topológica
int compareOrdTop(const void *a, const void *b){
	return ((TopOrdIdx *) b) -> content - ((TopOrdIdx *) a) -> content;
}

//função para processar a dfs como em uma ordenação topológica
int topologicalProcess(int size, int u, int searchedVertex, int *p, int *d, int *f, int *vector){
	int i;
	for(i = 0; i < size; i++)
		vector[i] = f[i];

	return 0;
}


Graph *kruskalMST(Graph *graph){
	if(!graph)
		return NULL;

	Graph *newGraph = createGraph('N', graph -> listGraph -> is_digraph, graph -> size, 0);

	DECIDER(graph -> type, newGraph -> listGraph = kruskalMSTListGraph(graph -> listGraph), 
						  newGraph -> matrixGraph = kruskalMSTMatrixGraph(graph -> matrixGraph));

	newGraph -> type = graph -> type;

	return newGraph;
}

Graph *primMST(Graph *graph){
	if(!graph)
		return NULL;

	Graph *newGraph = createGraph('N', graph -> listGraph -> is_digraph, graph -> size, 0);

	DECIDER(graph -> type, newGraph -> listGraph = primMSTListGraph(graph -> listGraph), 
						  newGraph -> matrixGraph = primMSTMatrixGraph(graph -> matrixGraph));

	newGraph -> type = graph -> type;

	return newGraph;
}


int printSum(Graph *graph){
	if(!graph)
		return -1;

	DECIDER(graph -> type, return printSumListGraph(graph -> listGraph), return printSumMatrixGraph(graph -> matrixGraph));

	return -1;
}