#ifndef GRAFO
#define GRAFO
#include "vector"
using namespace std;

struct Digrafo
{
    Digrafo();
    ~Digrafo();
    void mostrar();

    // Partes

    // Nodos de la lista de adyacencia
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

    // Cantidad de aristas
    int _aristas;
    // Cantidad de nodos
    int _nodos;
    // Lista de adyacencias
    vector<vector<Cabeza>> _adylst;
};

#endif