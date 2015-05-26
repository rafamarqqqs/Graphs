#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "graphList.h"
#include "graphMatrix.h"

int main(int argc, char *argv[]){

	Graph *graph = NULL;
	Graph *newGraph = NULL;
	int vertex, edges;

	scanf("%d %d", &vertex, &edges);

	graph = createGraph('M', 'G', vertex, edges);

	printGraph(graph);

	newGraph = primMST(graph);

	printf("%d %d\n", printSum(graph), printSum(newGraph));

	freeGraph(&graph);
	freeGraph(&newGraph);

	return 0;
}

