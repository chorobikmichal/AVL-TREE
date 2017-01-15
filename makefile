all: file run

file: avltree.c
	gcc -std=c99 avltree.c -o run.

run:
	./run
