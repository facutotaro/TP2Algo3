#ifndef JOHNSON
#define JOHNSON
#include "dijkstra.h"
#include "bellmanFord.h"
#include "digrafo.h"
#include <iostream>
#include <limits>
#include <vector>
const int INF = std::numeric_limits<int>::max();
void johnson(Digrafo &g);

#endif