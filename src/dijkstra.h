#ifndef DIJKSTRA
#define DIJKSTRA
#include <iostream>
#include "digrafo.h"
using namespace std;
#include "vector"
using namespace std;
typedef int Nodo;

void dijkstra(Digrafo &g, Nodo n, vector<int> &pesos);
#endif