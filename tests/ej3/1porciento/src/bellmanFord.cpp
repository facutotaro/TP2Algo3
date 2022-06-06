#include "bellmanFord.h"
const int INF = std::numeric_limits<int>::max();

dist suma(int a, int b)
{
    if (a == INF || b == INF)
        return INF;
    else
        return a + b;
}

bool bellmanFord(Digrafo g, Nodo n, vector<dist> &res)
{
    vector<Nodo> parents = vector<int>(g._nodos, -1);
    res[n] = 0;
    parents[n] = n;
    for (int i = 0; i < g._adylst.size() - 1; i++)
    {
        for (int j = 0; j < g._adylst.size(); j++)
        {
            for (int k = 0; k < g._adylst[j].size(); k++)
            {
                dist aux = suma(res[j], g._adylst[j][k].w);
                if (res[g._adylst[j][k].t] > aux)
                {
                    res[g._adylst[j][k].t] = aux;
                    parents[g._adylst[j][k].t] = j;
                }
            }
        }
    }

    bool encontrado = false;
    Nodo primeroDelCiclo;
    for (int j = 0; j < g._adylst.size(); j++)
    {
        for (int k = 0; k < g._adylst[j].size(); k++)
        {
            dist aux = suma(res[j], g._adylst[j][k].w);
            if (res[g._adylst[j][k].t] > aux)
            {
                res[g._adylst[j][k].t] = aux;
                parents[g._adylst[j][k].t] = j;
                if (!encontrado)
                {
                    primeroDelCiclo = j;
                    encontrado = true;
                }
            }
        }
    }

    if (!encontrado) return true;
    else {
        cout << 0 << endl;
        // vector<Nodo> ciclo;
        // vector<int> visitados =vector<int>(g._nodos,-1);
        // ciclo.push_back(primeroDelCiclo);
        // visitados[primeroDelCiclo] = 0;
        // int actual = parents[primeroDelCiclo];
        // int counter = 1;
        // while (visitados[actual] == -1)
        // {
        //     visitados[actual] = counter;
        //     counter++;
        //     ciclo.push_back(actual);
        //     actual = parents[actual];
        // }
        // ciclo.push_back(actual);
        // for (int i = ciclo.size()-1; i >= visitados[actual]; i--)
        // {
        //     cout << ciclo[i] << " ";
        // }
        
        // cout << endl;
        return false;
    }
}