#ifndef shortestPathDAG
#define shortestPathDAG

#include "grafoIntervalo.h"

void DFS(GrafoIntervalo &I, Nodo s); 
void topologicalSort(GrafoIntervalo &I); 
void shortestPathDAG(GrafoIntervalo &I, Nodo s);


#endif 