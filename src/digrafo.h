#ifndef GRAFO
#define GRAFO
#include "vector"
using namespace std;

struct Cabeza
{
    int t;
    int w;
    Cabeza(int nodo, int peso)
    {
        t = nodo;
        w = peso;
    }
};

struct Digrafo
{
    Digrafo();
    ~Digrafo();
    void mostrar();
    // Cantidad de aristas
    int _aristas;
    // Cantidad de nodos
    int _nodos;
    // Lista de adyacencias
    vector<vector<Cabeza>> _adylst;
};

#endif