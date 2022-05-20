#include <iostream>
#include <algorithm>
#include "vector"

using namespace std;
typedef int peso;


struct Intervalo 
{
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
    vector<Intervalo> _intervalos;
    vector<Intervalo> _N;

    int _m;
    vector<vector<Cabeza>> _adylstIn;
    vector<vector<Cabeza>> _adylstOut;
    vector<Cabeza> _adylstInicio; 
    
};