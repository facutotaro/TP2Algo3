#ifndef TP2_AHORA_SI_GRAFO_H
#define TP2_AHORA_SI_GRAFO_H

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct vertice {
    vertice(int numero);
    ~vertice();

    int _numero;
    string _color;
    int _distancia;
    int _padre;
    int _caminosMinimos;

};

struct grafo {
    grafo();
    ~grafo();
    void mostrar();
    bool bfs(int s, vector<vector<int>> * pred, vector<vector<int>> * caminosMin);

    // Partes

    // Nodos de la lista de adyacencia

    // Cantidad de aristas
    int _nAristas;

    // Cantidad de vertices
    int _nVertices;

    //Conjunto de Vertices
    vector<vertice> _vertices;

    // Lista de adyacencias
    vector<vector<int>> _adylst;
};

#endif //TP2_AHORA_SI_GRAFO_H
