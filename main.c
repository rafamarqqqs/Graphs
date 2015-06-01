#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "graphList.h"
#include "graphMatrix.h"

int main(int argc, char *argv[]){

	Graph *graph = NULL;
	int vertex, edges, end, start;

	scanf("%d %d", &vertex, &edges);

	graph = createGraph('L', 'D', vertex, edges);

	while((scanf("%d %d", &start, &end)) != EOF)
		dijkstraShortestPath(graph, start, end);

	freeGraph(&graph);

	return 0;
}

