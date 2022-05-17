# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date
 
tp2: tp2.o dijkstra.o bellmanFord.o digrafo.o
	$(CC) $(CFLAGS) tp2.o dijkstra.o bellmanFord.o digrafo.o -o tp2

# The main.o target can be written more simply
 
tp2.o: tp2.cpp dijkstra.h bellmanFord.h digrafo.h
	$(CC) $(CFLAGS) -c tp2.cpp
 
dijkstra.o: dijkstra.h
 
bellmanFord.o: bellmanFord.h

digrafo.o: digrafo.h

.PHONY: clean
clean:
	rm -f *.o
	rm -f tp2
