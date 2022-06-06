#include "digrafo.h"

#include <iostream>
using namespace std;

Digrafo::Digrafo()
{
    cin >> _nodos;
    cin >> _aristas;
    _adylst = vector<vector<Cabeza>>(_nodos,vector<Cabeza>());
    int actual,siguiente,peso;
    //Itero sobre el input para crear el digrafo
    for (int i = 0; i < _aristas; i++)
    {
        cin >> actual;
        cin >> siguiente;
        cin >> peso;
        _adylst[actual].push_back(Cabeza(siguiente,peso));
    }    
}

Digrafo::~Digrafo()
{
}

void Digrafo::mostrar()
{
    cout << _nodos << " " << _aristas << endl;
    for (int i = 0; i < _adylst.size(); i++)
    {
        for (int j = 0; j < _adylst[i].size(); j++)
        {
            cout << i << " " << _adylst[i][j].t << " " << _adylst[i][j].w << endl;
        }
    }
}