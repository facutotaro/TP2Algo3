#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <set>

using namespace std;

using Peso = int;  
struct Intervalo 
{
    Intervalo(){a = 0; b = 0; idx = -1;}
    ~Intervalo(){};

    int a;
    int b; 
    int idx;

    Intervalo(int limiteInferior, int limiteSuperior, int idx){
        a = limiteInferior;
        b = limiteSuperior;
        idx = idx;  
    }
    bool operator==(Intervalo i){
        bool igual_a = this->a == i.a; 
        bool igual_b = this->b == i.b; 
        bool igual_idx = this->idx == i.idx; 

        return igual_a && igual_b && igual_idx; 
    }
};
using Edge = pair<Intervalo, Peso>;
struct Arista
{
    Arista(){u = Intervalo(); v = Intervalo(); w = 0;}
    ~Arista(){};

    Intervalo u; 
    Intervalo v; 
    Peso w; 

    Arista(Intervalo cola, Intervalo cabeza, Peso peso){
        u = cola; 
        v = cabeza;
        w = peso; 
    }
};
using Grafo = vector<vector<Edge>>;

int n; 
int K; 
vector<Intervalo> intervalos, intervaloAsociado, N; 
vector<Arista> B, C; 
Grafo D; 

vector<Intervalo> Dijkstra(Grafo G, Intervalo v0){
    const int INFTY = std::numeric_limits<int>::max();
    vector<Peso> dist(G.size(), INFTY); 
    set<Intervalo> pendientes; 
    vector<Intervalo> padre(G.size(), Intervalo());
    vector<bool> sptSet(G.size(), false);

    for(int i = 0; i < N.size(); i++){ pendientes.insert(N[i]);}
    dist[v0.idx] = 0; 
    while (pendientes.size() > 0){
        Intervalo Ii = *pendientes.begin();
        sptSet[Ii.idx] = true; 
        for(Intervalo Ij : pendientes){
            if(dist[Ij.idx] < dist[Ii.idx]){ Ii = Ij;}
        }
        pendientes.erase(Ii);
        for(auto const& [Ih, w] : G[Ii.idx]){
            dist[Ih.idx] = min(dist[Ih.idx], dist[Ii.idx] + w);
        }
    }
    return dist; 
}


int main(){
    cin >> n;
    int a, b;
    for(int i = 0; i < n; i++){
        cin >> a;
        cin >> b; 
        intervalos.push_back(Intervalo(a, b, i + 1));
    }

    sort(intervalos.begin(), intervalos.end(), [](Intervalo v, Intervalo u) { 
            return v.a < u.a;
        });

    Intervalo inicio = Intervalo(-2, -1, 0); 
    N.push_back(inicio);  

    for(int i = 0; i < intervalos.size() - 1; i++){
        Intervalo Ii = intervalos[i]; 
        bool estaIncluido = false;
        for(int j = i + 1; j < intervalos.size(); j++){
            Intervalo Ij = intervalos[j];
            if (Ij.a < Ii.a < Ii.b < Ij.b){
                estaIncluido = true; 
                break;
            }
        }
        if (!estaIncluido){
            N.push_back(Ii); 
            K++;
        }
    }

    Intervalo fin = Intervalo(2*n + 1, 2*n + 2, 2*K + 1); 
    N.push_back(fin);

    for(int i = 0; i < N.size() - 1; i++){
        Intervalo Ii = N[i];
        Intervalo iAsociado = fin;  
        for (int j = i + 1; j < intervalos.size(); j++){
            Intervalo Ij = intervalos[j];
            if (Ii.b < Ij.a && Ij.b < iAsociado.b) iAsociado = Ij;
        }
        intervaloAsociado.push_back(iAsociado); 
    }

    for(int i = 0; i < N.size() - 1; i++){
        Intervalo Ii = N[i];
        Intervalo iEsimoAsociado = intervaloAsociado[i];
        for(int j = i + 1; j < N.size(); j++){
            Intervalo Ij = N[j];
            if (Ii.a < Ij.a < Ii.b < Ij.b) B.push_back(Arista(Ii, Ij, 1));
            if (Ii.b < Ij.a && !(Ii.b < iEsimoAsociado.a < iEsimoAsociado.b < Ij.a)) C.push_back(Arista(Ii, Ij, Ii.idx == 0 ? 0 : 1));
        }
    }

    for(int i = 0; i < K; i++){
        Intervalo Iin = N[i];
        Intervalo Iout = Intervalo(Iin.a, Iin.b, Iin.idx + K);
        N.push_back(Iout);
        Arista e = Arista(Iin, Iout, 0); 
        D[Iin.idx].push_back(Edge(e.v, e.w));
    }
    N.push_back(fin); 

    D.resize(2*(K + 1));
    for(Arista e : B){ D[e.u.idx + K].push_back(Edge(e.v, e.w));}
    for(Arista e : C){ D[e.u.idx].push_back(Edge(N[e.v.idx == fin.idx ? fin.idx : e.v.idx + K], e.w));}
    
    vector<Intervalo> conjuntoDominanteTotal = Dijkstra(D, inicio);


    



    








    return 0; 
}












// Sea un Intervalo I = [a, b].
/*
GrafoIntervalo::GrafoIntervalo()
{
    cin >> _n;
    int a, b;
    for(int i = 0; i < _n; i++)
    {
        cin >> a;
        cin >> b; 
        _intervalos.push_back(Intervalo(a, b, i + 1));
    }

    // Ordeno segun a creciente, O(nlog(n)).
    sort(_intervalos.begin(), _intervalos.end(), [](Intervalo v, Intervalo u) { 
            return v.a < u.a;
        });

    // Inicializo conjunto de nodos del Grafo Intervalo. 
    vector<NodoInt> _N;
    
    // Inicializo lista de adyacencia del Grafo Intervalo.
    vector<vector<CabezaInt>> iEsimoNodo(2);
    vector<vector<vector<CabezaInt>>> _adylst(_n+1, iEsimoNodo);

    // Construyo N, O(n²).

    // Vector auxiliar que guarda los intervalos que forman parte del Grafo Intervalo 
    // sin la distincion del In y el Out. 
    vector<Intervalo> intervalosEnN; 

    // Creo intervalo de "mentria" I_0.
    Intervalo intInicio = Intervalo(_intervalos.front().a - 2, _intervalos.front().b - 1, 0);
    NodoInt nodoInicio = NodoInt(intInicio, 0);
    intervalosEnN.push_back(intInicio); 
    _N.push_back(nodoInicio);
    
    for (Intervalo iInt : _intervalos) 
    {
        bool estaIncluido = false;
        for (Intervalo jInt : _intervalos)
        {
            if (jInt.a < iInt.a < iInt.b < jInt.b)
            {
                estaIncluido = true; 
                break;
            }
        }
        if (!estaIncluido)         
        {   
            intervalosEnN.push_back(iInt);
            NodoInt iNodoIn = NodoInt(iInt, 0); NodoInt iNodoOut = NodoInt(iInt, 1);
            _N.push_back(iNodoIn); _N.push_back(iNodoOut);
            _adylst[iInt.idx][0].push_back(CabezaInt(iNodoOut, 0));
        } 
    }

    // Creo intervalo de "mentira" I_n+1.
    Intervalo intFin = Intervalo(_intervalos.back().a + 1, _intervalos.back().b + 1, 0);
    NodoInt nodoFin = NodoInt(intFin, 1); 
    intervalosEnN.push_back(intFin);
    _N.push_back(nodoFin);

    // Construyo B, O(n²).
    

    // Luego voy iterando sobre los intervalos que son nodos viendo si su asociado esta entre ellos, 
    // en caso negativo los agrego como aristas del grafo, O(n²).
    for (Intervalo iInt : intervalosEnN)
    {
        Intervalo iEsimoAsociado = intervaloAsociado[iInt.idx];
        for (Intervalo jInt : intervalosEnN)
        {
            if (iInt.b < jInt.a && !(iInt.b < iEsimoAsociado.a < iEsimoAsociado.b < jInt.a))
            {
                NodoInt jNodoOut = NodoInt(jInt, 1);
                int peso = (iInt == intInicio) ? 0 : 1;
                _adylst[iInt.idx][0].push_back(CabezaInt(jNodoOut, peso));
            }
        }
    }

    
}

GrafoIntervalo::~GrafoIntervalo(){}

void GrafoIntervalo::solver()
{

}

*/