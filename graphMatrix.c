#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "set.h"
#include "heap.h"
#include "graph.h"
#include "graphList.h"
#include "queue.h"

#define bigger(a, b) (a > b ? a : b)
#define smaller(a, b) (a < b ? a : b)

#define WHITE 0
#define GRAY -2
#define BLACK -3

int addVertexMatrixGraph(MatrixGraph *graph){
	if(!graph)
		return -1;
	
	int i, j;

	graph -> matrix = realloc(graph -> matrix, sizeof(int *) * (graph -> size + 1));
	
	for(i = 0; i < graph -> size; i++){ //realocar os espaços necessários
		graph -> matrix[i] = realloc(graph -> matrix[i], sizeof(int) * (graph -> size + 1));
		for(j = graph -> size; j < (graph -> size + 1); j++)
			graph -> matrix[i][j] = -1;
	}

	for(i = graph -> size; i < (graph -> size + 1); i++){
		graph -> matrix[i] = (int *) malloc(sizeof(int) * (graph -> size + 1));
		for(j = 0; j < (graph -> size + 1); j++)
			graph -> matrix[i][j] = -1;
	}

	graph -> size++;

	return 1;
}

int removeEdgeMatrixGraph(MatrixGraph* graph, int src, int dest){
	if(!graph || bigger(src, dest) > graph -> size)
		return -1;

	graph -> matrix[src][dest] = -1;

	if(!(graph -> is_digraph))
		graph -> matrix[dest][src] = -1;

	return 1;
}

int addEdgeMatrixGraph(MatrixGraph *graph, int src, int dest, int weight){
	if(!graph || bigger(src, dest) >= graph -> size)
		return -1;

	graph -> matrix[src][dest] = weight;
	
	if(!(graph -> is_digraph))
		graph -> matrix[dest][src] = weight;

	return 1;
}

MatrixGraph* createMatrixGraph(int is_digraph, int vertex, int edges){
	if(vertex <= 0 || edges < 0)
		return NULL;

	int i, j, weight, vertexA, vertexB;

	MatrixGraph *newGraph = (MatrixGraph *) malloc(sizeof(MatrixGraph));

	newGraph -> matrix = (int **) malloc(sizeof(int *) * vertex);

	for(i = 0; i < vertex; i++){
		newGraph -> matrix[i] = (int *) malloc(sizeof(int) * vertex);
		for(j = 0; j < vertex; j++)
			newGraph -> matrix[i][j] = -1;
	}
	
	newGraph -> is_digraph = is_digraph;	
	newGraph -> size = vertex;

	while(edges){ //adiciona todos os vértices
		scanf("%d %d %d", &vertexA, &vertexB, &weight);
		//scanf("%d %d", &vertexA, &vertexB);
		addEdgeMatrixGraph(newGraph, vertexA, vertexB, weight);
		edges--;
	}

	return newGraph;
}


int printMatrixGraph(MatrixGraph *graph){
	if(!graph)
		return -1;
	
	int i, j;

	for(i = 0; i < graph -> size; i++){
		for(j = 0; j < graph -> size; j++){
			if(graph -> matrix[i][j] < 0)
				printf(". ");
			else
				printf("%d ", graph -> matrix[i][j]);
		}

		printf("\n");
	}

	return 1;
}

int printAdjMatrixGraph(MatrixGraph *graph, int vertex){
	if(!graph || vertex >= graph -> size)
		return -1;

	int i;

	for(i = 0; i < graph -> size; i++){
		if(graph -> matrix[vertex][i] != -1){
			printf("%d ", i);
		}
	}

	printf("\n");

	return 1;
}

void freeMatrixGraph(MatrixGraph **graph){
	if(!graph || !*graph)
		return;

	int i;

	for(i = 0; i < (*graph) -> size; i++)
		free((*graph) -> matrix[i]);

	free((*graph) -> matrix);
	free(*graph);
	*graph = NULL;
}

int getLighterEdgeMatrixGraph(MatrixGraph *graph){
	if(!graph)
		return -1;

	int i, j, smaller = INT_MAX, smallerEdge;

	for(i = 0; i < graph -> size; i++){
		for(j = 0; j < graph -> size; j++){
			if(graph -> matrix[i][j] < smaller && graph -> matrix[i][j] != -1){
				smaller = graph -> matrix[i][j];
				smallerEdge = smaller(i, j);
			}
		}
	}
	
	if(smaller != INT_MAX)
		printf("%d\n", smallerEdge);
	else		
		printf("This graph has no edges.\n");

	return 1;
}

MatrixGraph *getTransposedMatrixGraph(MatrixGraph *graph){
	if(!graph || !(graph -> is_digraph))
		return NULL;

	int i, j;
	MatrixGraph *newGraph = createMatrixGraph(graph -> is_digraph, graph -> size, 0);

	for(i = 0; i < graph -> size; i++){
		for(j = 0; j < graph -> size; j++){
				newGraph -> matrix[i][j] = graph -> matrix[j][i];
		}
	}

	printMatrixGraph(newGraph);

	return newGraph;
}


int breadthFirstSearchMatrixGraph(MatrixGraph *graph, int start, int searchedVertex){
	if(!graph || bigger(start, searchedVertex) >= graph -> size)
		return -1;

	int *color = (int *) malloc(sizeof(int) * graph -> size);
	int u, v, i;
	int *d = (int *) malloc(sizeof(int) * graph -> size);
	int *p = (int *) malloc(sizeof(int) * graph -> size);

	for(i = 0; i < graph -> size; i++){
		p[i] = -1;
		color[i] = WHITE;
		d[i] = 0;
	}

	Queue *queue = createQueue();
	u = start;
	color[u] = BLACK;
	enqueue(queue, u);

	while(!isEmpty(queue)){
		u = dequeue(queue);

		for(i = 0; i < graph -> size; i++){
			
			if(graph -> matrix[u][i] != -1){												//se existe aresta
				v = i;

				if(color[v] == WHITE){														//se ela é branca
					color[v] = BLACK;
					d[v] = d[u] + 1;
					p[v] = u;
					enqueue(queue, v);
				}
			}
		}
	}																						

	buildPath(p, searchedVertex, start);

	free(color);
	free(d);
	free(p);

	return 1;
}

int _depthFirstSearchVisitMatrixGraph(MatrixGraph *graph, int u, int searchedVertex, int *p, int *color, 
										int *d, int *f, int *visitTime, BYTE condition, ProcessDFS callback, int *vector){

	int i, v;
	color[u] = GRAY;

	if(condition && callback(graph -> size, u, searchedVertex, p, d, f, vector))
		return 1;

	d[u] = ++(*visitTime);

	for(i = 0; i < graph -> size; i++){
		if(graph -> matrix[u][i] != -1){
			v = i;
			if(color[v] == WHITE){
				p[v] = u;
				if(_depthFirstSearchVisitMatrixGraph(graph, v, searchedVertex, p, color, d, f, visitTime, condition, callback, vector))
					return 1;
			}
		}
	}

	color[u] = BLACK;
	f[u] = ++(*visitTime);

	return 0;
}

int depthFirstSearchMatrixGraph(MatrixGraph *graph, int start, int searchedVertex, BYTE condition, ProcessDFS callback, int *vector){
	if(!graph || bigger(start, searchedVertex) >= graph -> size)
		return -1;

	int *color = (int *) malloc(sizeof(int) * graph -> size);
	int u, i, visitTime = 0;
	int *p = (int *) malloc(sizeof(int) * graph -> size);
	int *f = (int *) malloc(sizeof(int) * graph -> size);
	int *d = (int *) malloc(sizeof(int) * graph -> size);

	for(i = 0; i < graph -> size; i++){
		p[i] = -1;
		color[i] = WHITE;
		d[i] = f[i] = 0;
	}

	for(u = start; u < graph -> size; u++){
		if(color[u] == WHITE){
			p[u] = -2;
			if(_depthFirstSearchVisitMatrixGraph(graph, u, searchedVertex, p, color, d, f, &visitTime, condition, callback, vector) && i == start)
				break;
		}
	}

	if(u == graph -> size){
		for(u = 0; u < start; u++){
			if(color[u] == WHITE){
				p[u] = -2;
				_depthFirstSearchVisitMatrixGraph(graph, u, searchedVertex, p, color, d, f, &visitTime, condition, callback, vector);
			}
		}
	}

	if(condition)
		buildPath(p, searchedVertex, start);
	else
		callback(graph -> size, 0, 0, p, d, f, vector);

	free(color);
	free(p);
	free(d);
	free(f);

	return 1;
}

ListGraph* toList(MatrixGraph *graph){
	if(!graph)
		return NULL;

	int i, j;
	ListGraph *newGraph = createListGraph(graph -> is_digraph, graph -> size, 0);

	for(i= 0; i < graph -> size; i++){
		for(j = 0; j < graph -> size; j++){
			if(graph -> matrix[i][j] != -1){
				addEdgeListGraph(newGraph, i, j, graph -> matrix[i][j]);
			}
		}
	}

	freeMatrixGraph(&graph);

	return newGraph;
}

int topologicalOrdenationMatrixGraph(MatrixGraph *graph, int *pVector){
	if(!graph)
		return -1;
	else if(!graph -> is_digraph)
		return 0;
	
	int i;

	TopOrdIdx *auxVector = (TopOrdIdx *) malloc(sizeof(TopOrdIdx) * graph -> size);

	depthFirstSearchMatrixGraph(graph, 0, graph -> size - 1, 0, topologicalProcess, pVector);

	for(i = 0; i < graph -> size; i++){
		auxVector[i].content = pVector[i];
		auxVector[i].position = i;
	}

	qsort(auxVector, graph -> size, sizeof(TopOrdIdx), compareOrdTop);

	for(i = 0; i < graph -> size; i++)
		pVector[i] = auxVector[i].position;

	free(auxVector);

	return 1;
}

//Algoritmo de MST de Kruskal feito em um grafo representado por matrix
MatrixGraph *kruskalMSTMatrixGraph(MatrixGraph *graph){
	if(!graph)
		return NULL;

	int i, j, u, v;
	MatrixGraph *newGraph = NULL;
	SetNode **vertexSet = NULL;
	List *edges = NULL;
	ListNode *current = NULL;

	newGraph = createMatrixGraph(graph -> is_digraph, graph -> size, 0);					//inicializa um novo grafo
	edges = createList();																	//lista de arestas
	vertexSet = (SetNode **) malloc(sizeof(SetNode *) * graph -> size);						//sets para cada vértice

	//inicializa os sets para cada vértice
	for(i = 0; i < graph -> size; i++){
		vertexSet[i] = createSetNode(i);
		makeSet(vertexSet[i]);
	}
	
	for(i = 0; i < graph -> size; i++){														//coloca as arestas em uma lista ordenada
		for(j = 0; j < graph -> size; j++){
			if(graph -> matrix[i][j] != -1)
				addListNode(edges, i, j, graph -> matrix[i][j], compareMST);
		}
	}

	current = edges -> head -> next;

	//passa por todas as arestas presentes no vetor de arestas
	while(current){
		
		u = current -> src;
		v = current -> dest;

		//se dois vértices não pertencerem ao mesmo set, adicionamos a aresta entre eles ao novo grafo e unimos os seus sets
		if(findSet(vertexSet[u]) != findSet(vertexSet[v])){									//se u e v não pertencem à mesma árvore
			addEdgeMatrixGraph(newGraph, u, v, current -> weight);							//adiciona a aresta no novo grafo
			unite(vertexSet[u], vertexSet[v]);												//une dois sets
		}
		
		current = current -> next;
	}

	freeList(&edges);

	for(i = 0; i < graph -> size; i++)
		free(vertexSet[i]);

	free(vertexSet);

	return newGraph;								//retorna o grafo cujas arestas formam uma MST
}

MatrixGraph *primMSTMatrixGraph(MatrixGraph *graph){
	if(!graph)
		return NULL;

	int i, j;
	int *p, *k;
	MatrixGraph *newGraph = createMatrixGraph(graph -> is_digraph, graph -> size, 0);
	
	SetNode **setVector = (SetNode **) malloc(sizeof(SetNode *) * graph -> size);
	SetNode *mainSet;

	Heap *heap = createHeap();

	k = (int *) malloc(sizeof(int) * graph -> size);
	p = (int *) malloc(sizeof(int) * graph -> size);

	for(i = 0; i < graph -> size; i++){
		k[i] = INT_MAX;
		p[i] = -1;
	}

	//faz o set para ser o "corte"
	mainSet = createSetNode(-1);
	makeSet(mainSet);

	//um set para cada um dos elementos, colocar todos na heap
	for(i = 0; i < graph -> size; i++){
		setVector[i] = createSetNode(i);
		makeSet(setVector[i]);
		heapInsert(heap, i, INT_MAX);
	}
	
	k[0] = 0;
	setKey(heap, 0, 0);	//root começa com key = 0


	while(heap -> size > 0){
		HeapNode *node = extractMin(heap);

		if(p[node -> id] != -1){
			unite(mainSet, setVector[node -> id]);
			addEdgeMatrixGraph(newGraph, node -> id, p[node -> id], k[node -> id]);
		}


		i = node -> id;
		for(j = 0; j < graph -> size; j++){
			if(graph -> matrix[i][j] != -1 && findSet(setVector[j]) != findSet(mainSet) && graph -> matrix[i][j] < k[j]){
				p[j] = i;
				k[j] = graph -> matrix[i][j];
				setKey(heap, j, graph -> matrix[i][j]);
			}
		}
	}

	for(i = 0; i < graph -> size; i++)
		free(setVector[i]);

	freeHeap(&heap);
	free(mainSet);
	free(setVector);
	free(k);
	free(p);

	return newGraph;
}

int printSumMatrixGraph(MatrixGraph *graph){
	if(!graph)
		return -1;

	int i, j, weight = 0;
	List **auxVector = (List **) malloc(sizeof(List *) * graph -> size);

	for(i = 0; i < graph -> size; i++)
		auxVector[i] = createList();

	for(i = 0; i < graph -> size; i++){
		for(j = 0; j < graph -> size; j++){
			//utilizado para não somar duas vezes o peso de uma mesma aresta
			if(graph -> matrix[i][j] != -1 && searchNode(auxVector[j], i) == -2){
				addListNode(auxVector[i], i, j, graph -> matrix[i][j], compareMST);
				weight += graph -> matrix[i][j];
			}			
		}
	}

	for(i = 0; i < graph -> size; i++)
		freeList(&auxVector[i]);

	free(auxVector);
	
	return weight;
}