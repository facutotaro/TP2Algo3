#ifndef BELLFORD
#define BELLFORD
#include <iostream>
#include "digrafo.h"
using namespace std;
#include "vector"
using namespace std;
#include <limits>
typedef int Nodo;
typedef int dist;
//const int INF = std::numeric_limits<int>::max();
bool bellmanFord(Digrafo &g, Nodo &n, vector<dist> &res);

#endif