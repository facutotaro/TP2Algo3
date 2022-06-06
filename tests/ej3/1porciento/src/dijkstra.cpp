#include "dijkstra.h"
#include <iostream>
#include <limits>
#include <set>
using namespace std;
const int INF = std::numeric_limits<int>::max();
typedef int dist;
typedef pair<int,Nodo> Pendiente;

void dijkstra(Digrafo &g, Nodo n, vector<int> &pesos)
{
    vector<dist> res = vector<dist>(g._nodos,INF);
    res[n] = 0;
    set<Pendiente> cola;    
    for (int i = 0; i < g._nodos; i++)
    {
        cola.insert(Pendiente(res[i],i));
    }
    while (cola.size() > 0)
    {
        Pendiente p = *cola.begin();
        cola.erase(p);
        Nodo n = p.second;
        for (int i = 0; i < g._adylst[n].size(); i++)
        {
            int aux = INF;
            Nodo prox = g._adylst[n][i].t;
            if(res[n] != INF)
            {
                aux = res[n] + g._adylst[n][i].w;
            }
            if (res[prox] > aux)
            {
                cola.erase(Pendiente(res[prox],prox));
                res[prox] = aux;
                cola.insert(Pendiente(res[prox],prox));
            }
        }
    }
    // for (int i = 0; i < res.size(); i++)
    // {
    //     if (res[i] == INF)
    //     {
    //         cout << "INF ";
    //     }
    //     else cout << res[i] + pesos[i] - pesos[n]<< " ";
    // }
    //cout << endl;
}