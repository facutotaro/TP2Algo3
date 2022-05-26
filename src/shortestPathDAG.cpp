
#include "shortestPathDAG.h"

void relax(NodoInt u, NodoInt v, int w)
{
    if (v.distancia > u.distancia + w) 
         v.distancia = u.distancia + w;
}

void inicializarVisitados(GrafoIntervalo &I)
{
    vector<bool> tipos(2); 
    for (int i = 0; i < I._n + 2; i++)
    {
        visitado.push_back(tipos);
    }
}

void DFS(GrafoIntervalo &I, NodoInt s)
{
    visitado[s.I.idx][s.tipo] = true; 
    for(CabezaInt cabeza : I._adylst[s.I.idx][s.tipo])
    {
        if(!visitado[cabeza.n.I.idx][cabeza.n.tipo])
            DFS(I, cabeza.n);
    }
    orden.push_front(s);    
}


void topologicalSort(GrafoIntervalo &I) 
{
   for(NodoInt nodo : I._N)
   {
       if(!visitado[nodo.I.idx][nodo.tipo])
            DFS(I, nodo);
   }
}

void DAGShortestPath(GrafoIntervalo& I, NodoInt s)
{
    topologicalSort(I);
    inicializarVisitados(I);
    s.distancia = 0; 
    for (NodoInt nodo : orden)
    {
       for (CabezaInt cabeza : I._adylst[nodo.I.idx][nodo.tipo])
            relax(nodo, cabeza.n, cabeza.w); 
    }
}


