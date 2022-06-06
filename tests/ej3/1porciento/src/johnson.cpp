#include "johnson.h"
void johnson(Digrafo &g)
{
    g._adylst.push_back(vector<Cabeza>());
    for (int i = 0; i < g._nodos; i++)
    {
        g._adylst[g._nodos].push_back(Cabeza(i, 0));
    }
    g._aristas += g._nodos;
    g._nodos++;
    vector<dist> res = vector<int>(g._nodos, INF);
    cout << g._nodos << ";";
    if (bellmanFord(g, g._nodos - 1, res))
    {
        cout << 1 << endl;
        // for (int i = 0; i < g._adylst.size()-1; i++)
        // {
        //     for (int j = 0; j < g._adylst[i].size(); j++)
        //     {
        //         g._adylst[i][j].w = g._adylst[i][j].w + res[i]-res[g._adylst[i][j].t];
        //     }
            
        // }
        // g._adylst.pop_back();
        // g._aristas = g._aristas - g._nodos + 1;
        // g._nodos--;
        // for (int i = 0; i < g._nodos; i++)
        // {
        //     dijkstra(g,i,res);
        // }
        
    }
}