#ifndef GRAFOINT
#define GRAFOINT

#include <iostream>
#include <algorithm>
#include "vector"

using namespace std;

struct Intervalo 
{
    Intervalo(){a = 0; b = 0; idx = -1;};
    ~Intervalo();
    
    int a;
    int b; 
    int idx;

    Intervalo(int limiteInferior, int limiteSuperior, int idx)
    {
        a = limiteInferior;
        b = limiteSuperior;
        idx = idx; 
    }
    bool operator == (Intervalo i)
    {
        bool igual_a = this->a == i.a; 
        bool igual_b = this->b == i.b; 
        bool igual_idx = this->idx == i.idx; 

        return igual_a && igual_b && igual_idx; 
    }
};

struct Nodo 
{
    Nodo(){I = Intervalo(); type = string();};
    ~Nodo();

    Intervalo I; 
    string type; 

    Nodo(Intervalo I, string type)
    {
        I = I; 
        type = type; 
    }

    bool operator == (Nodo n)
    {
        bool igual_I = this->I == n.I;
        bool igual_type = this->type == n.type; 
        
        return igual_I && igual_type;
    }
};

struct Cabeza
{
    Cabeza(){n = Nodo(); w = 0;}
    ~Cabeza();
    
    Nodo n;
    int w;
    Cabeza(Nodo nodo, int peso)
    {
        n = nodo;
        w = peso;
    }
};

struct GrafoIntervalo
{
    GrafoIntervalo();
    ~GrafoIntervalo();
    
    int _n;
    vector<Intervalo> _intervalos;
    vector<Nodo> _N;
    vector<Intervalo> _intervaloAsociado;

    vector<vector<Cabeza>> _adylstIn; 
    vector<vector<Cabeza>> _adylstOut;
}; 

#endif