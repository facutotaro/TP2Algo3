#ifndef GRAFO
#define GRAFO
#include "vector"
using namespace std;

struct Digrafo
{
    Digrafo();
    ~Digrafo();
    void mostrar();

    //Partes
    struct Cabeza
    {
        int t;
        int w;
        Cabeza(int nodo, int peso){
            t = nodo;
            w = peso;
        }
    };
    int _aristas;
    int _nodos;
    vector<vector<Cabeza>> _adylst;
};

#endif