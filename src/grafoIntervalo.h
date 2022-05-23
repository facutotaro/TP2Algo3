#ifndef GRAFOINT
#define GRAFOINT

#include <iostream>
#include <algorithm>
#include "vector"

using namespace std;
typedef int peso;
typedef int indxOg;


struct Intervalo 
{
    Intervalo(){a = 0; b = 0;};
    ~Intervalo();
    int a;
    int b;
    Intervalo(int limiteInferior, int limiteSuperior)
    {
        a = limiteInferior;
        b = limiteSuperior;
    }
};

struct Cabeza
{
    Cabeza(){i = Intervalo(); w = 0;}
    ~Cabeza();
    Intervalo i;
    int w;
    Cabeza(Intervalo nodo, int peso)
    {
        i = nodo;
        w = peso;
    }
};

class GrafoIntervalo
{
    GrafoIntervalo();
    ~GrafoIntervalo();

    void mostrar();
    
    int _n;
    vector<pair<Intervalo, indxOg>> _intervalos;
    vector<pair<Intervalo, indxOg>> _N;
    vector<Intervalo> _intervaloAsociado;

    pair<Intervalo, Intervalo> _inicio;
    pair<Intervalo, Intervalo> _fin;

    vector<Cabeza> _adylstInicio;
    vector<vector<Cabeza>> _adylstIn;
    vector<vector<Cabeza>> _adylstOut; 
}; 

#endif