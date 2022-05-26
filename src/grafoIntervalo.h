#ifndef GRAFOINT
#define GRAFOINT

#include <iostream>
#include <algorithm>
#include <limits>
#include "vector"
#include<list>


using namespace std;

struct Intervalo 
{
    Intervalo(){a = 0; b = 0; idx = -1;}
    ~Intervalo(){};
    
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


struct NodoInt
{
    NodoInt(){I = Intervalo(); tipo = -1; distancia = std::numeric_limits<int>::max();}
    ~NodoInt(){};

    Intervalo I; 
    int tipo; 
    // NodoInt padre; 
    int distancia; 

    NodoInt(Intervalo I, int tipo)
    {
        I = I; 
        tipo = tipo; 
    }

    bool operator == (NodoInt n)
    {
        bool igual_I = this->I == n.I;
        bool igual_type = this->tipo == n.tipo; 
        
        return igual_I && igual_type;
    }
};

struct CabezaInt
{
    CabezaInt(){n = NodoInt(); w = 0;}
    ~CabezaInt(){};
    
    NodoInt n; 
    int w;
    CabezaInt(NodoInt nodo, int peso)
    {
        n = n;
        w = peso;
    }
};

struct GrafoIntervalo
{
    GrafoIntervalo();
    ~GrafoIntervalo();

    void solver();

    int _n;
    vector<Intervalo> _intervalos;
    vector<NodoInt> _N; 
    // Vector con 0 <= i <= _n + 1 posiciones (I_0 a I_n ya que I_n+1 no tiene aristas de salida)
    // En la lista de adyacencia del intervalo i, _adylst[i], contendra dos vectores tq' 
    // _adylst[i][0] es la lista de adyancencia del nodo i_in y _adylst[i][1] la lista de adyacencia del nodo i_out. 
    // En caso de que _adylst[i] sea vacio quiere decir que ese intervalo no es nodo del grafo. 
    vector<vector<vector<CabezaInt>>> _adylst;
}; 

#endif


