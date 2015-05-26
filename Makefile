all: list.o queue.o graphMatrix.o graphList.o graph.o set.o heap.o main.o
	@gcc -std=c99 -g graphList.o queue.o list.o graphMatrix.o set.o graph.o heap.o main.o -o main -Wall

main.o:
	@gcc -std=c99 -g -c main.c -o main.o -Wall

set.o:
	@gcc -std=c99 -g -c set.c -o set.o -Wall

graph.o:
	@gcc -std=c99 -g -c graph.c -o graph.o -Wall

graphMatrix.o:
	@gcc -std=c99 -g -c graphMatrix.c -o graphMatrix.o -Wall

graphList.o:
	@gcc -std=c99 -g -c graphList.c -o graphList.o -Wall

queue.o:
	@gcc -std=c99 -g -c queue.c -o queue.o -Wall

list.o:
	@gcc -std=c99 -g -c list.c -o list.o -Wall

heap.o:
	@gcc -std=c99 -g -c heap.c -o heap.o -Wall

clean:
	@rm *.o main

zip:
	@zip -r grafo.zip graph.c graph.h graphList.c graphList.h graphMatrix.c graphMatrix.h queue.c queue.h set.c set.h heap.c heap.h list.c list.h Makefile main.c readme

run:
	@./main
