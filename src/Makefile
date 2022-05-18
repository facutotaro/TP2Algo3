# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
 
tp2: tp2.o dijkstra.o bellmanFord.o digrafo.o johnson.o
	$(CC) $(CFLAGS) tp2.o dijkstra.o bellmanFord.o digrafo.o johnson.o -o tp2


tp2.o: tp2.cpp dijkstra.h bellmanFord.h digrafo.h johnson.h
	$(CC) $(CFLAGS) -c tp2.cpp
 
johnson.o: dijkstra.h bellmanFord.h digrafo.h 

dijkstra.o: dijkstra.h digrafo.h
 
bellmanFord.o: bellmanFord.h

digrafo.o: digrafo.h


.PHONY: clean
clean:
	rm -f *.o
	rm -f tp2
