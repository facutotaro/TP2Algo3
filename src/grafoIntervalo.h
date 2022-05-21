#include <iostream>
#include <algorithm>
#include "vector"
#include "map"

using namespace std;
typedef int peso;


struct Intervalo 
{
    Intervalo();
    int a;
    int b;
    Intervalo(int limiteInferior, int limiteSuperior){
        a = limiteInferior;
        b = limiteSuperior;
    }
};



struct Cabeza
{
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
    Intervalo _inicio; 
    Intervalo _fin;
    vector<pair<Intervalo, int>> _intervalos;
    vector<pair<Intervalo, int>> _N;

    vector<vector<Cabeza>> _adylstIn;
    vector<vector<Cabeza>> _adylstOut;
    vector<Cabeza> _adylstInicio; 
    
};