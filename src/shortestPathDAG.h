
#include "grafoIntervalo.h"

#include<list>

list<NodoInt> orden; 
vector<vector<bool>> visitado; 

void inicializarVisitados(GrafoIntervalo &I);
void relax(NodoInt u, NodoInt v, int w); 
void DFS(GrafoIntervalo &I, NodoInt s); 
void topologicalSort(GrafoIntervalo &I); 
void shortestPathDAG(GrafoIntervalo &I, NodoInt s);



