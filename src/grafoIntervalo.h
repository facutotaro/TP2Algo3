#ifndef GRAFOINT
#define GRAFOINT

#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <list>
#include <set>

using namespace std;
const int INFTY = std::numeric_limits<int>::max();

using Peso = int;  
 struct Intervalo{
    Intervalo(){a = 0; b = 0; idx = -1;}
    ~Intervalo()= default;;

    int a;
    int b; 
    int idx;

    Intervalo(int limiteInferior, int limiteSuperior, int i){
        a = limiteInferior;
        b = limiteSuperior;
        idx = i;
    }
    bool operator==(const Intervalo& i) const{
        bool igual_a = this->a == i.a; 
        bool igual_b = this->b == i.b; 
        bool igual_idx = this->idx == i.idx;

        return igual_a && igual_b && igual_idx; 
    }
    bool operator<(const Intervalo& i) const{
        return this->a < i.a;
    }
};
using Vecino = pair<Intervalo, Peso>;
struct Arista{
    Arista(){u = Intervalo(); v = Intervalo(); w = 0;}
    ~Arista()= default;;

    Intervalo u; 
    Intervalo v; 
    Peso w; 

    Arista(Intervalo cola, Intervalo cabeza, Peso peso){
        u = cola; 
        v = cabeza;
        w = peso; 
    }
};
using Grafo = vector<vector<Vecino>>;

void relax(Intervalo u, Intervalo v, int w);
void inicializarVisitados(Grafo& G);
void DFS(Grafo& G, Intervalo s);
void topologicalSort(Grafo& G);
void DAGShortestPath(Grafo& G, Intervalo s);
void armarCaminoMinimo(Intervalo& s, Intervalo& d, vector<Intervalo>& padre, vector<Intervalo>& path);
void grafoIntervalo();

#endif


