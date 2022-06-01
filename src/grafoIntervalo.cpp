#include "grafoIntervalo.h"

// Sea I un intervalo [a,b] con indice i.

// Cantidad de intervalos pasados como input.
int n;
// Cantidad de intervalos que no estan completamente contenidos dentro de otros y voy a considerar como
// nodos de D.
int K;

// Vector que indica si el nodo i fue visitado en DFS.
vector<bool> visitado;
// P: Vector de posicion que relaciona al iesimo nodo con su posicion original pasada como input.
// distancia: La distancia del nodo i al nodo source.
vector<int> P, distancia;
// Orden establecido por el Topological Sort para los nodos de D.
list<Intervalo> orden;
// Conjunto de intervalos pasados como input.
vector<Intervalo> intervalos;
// N: Nodos de D
// padre: nodo previo
// intervaloAsociado:
vector<Intervalo> N, padre, intervaloAsociado;
// B: representan el conjunto de aristas en el que dos intervalo en N se intersecan.
// C: representa el conjunto de aristas en el que dos intervalos en N no se intesecan y no hay
//    intervalo entre todos los pasados por parametro que este entre estos dos.
//    ]    [    ]    [
//    Ii.b Ih.a Ih.b Ij.a
vector<Arista> B, C;
// D: es un vector de vectores de vecinos tq' G[i] tiene los vecinos del intervalo con idx igual a i.
Grafo D;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sea n la cantidad de nodos en D y m la cantidad de aristas en D.

// Dado una arista (u, v) con un costo asociado w, Relax actualiza la distancia de v en caso que
// sea mayor a la distancia actual de u sumado a w. Ademas u es ahora padre de v ya que es el nodo
// inmediatamente detras de v. Complejidad: O(1).
void relax(Intervalo u, Intervalo v, int w){
    if (distancia[u.idx] != INFTY && distancia[v.idx] > distancia[u.idx] + w ){
        distancia[v.idx] = distancia[u.idx] + w;
        padre[v.idx] = u;
    }
}

// Inicializa los vectores visitado, distancia y padre que van a ser usados para calcular el camino
// minimo. Complejidad: O(n).
void inicializarVisitados(Grafo& G){
    visitado.resize(G.size(), false);
    distancia.resize(G.size(), INFTY);
    padre.resize(G.size(), Intervalo());
}

// Complejidad: O(m).
void DFS(Grafo& G, Intervalo s){
    visitado[s.idx] = true;
    for(Vecino v : G[s.idx]){
        if(!visitado[v.first.idx])
            DFS(G, v.first);
    }
    orden.push_front(s);
}

// Complejidad: O(n + m).
void topologicalSort(Grafo& G){
    for(Intervalo I : N){
        if(!visitado[I.idx])
            DFS(D, I);
    }
}

// Complejidad: O(n + m).
void DAGShortestPath(Grafo& G, Intervalo s){
    inicializarVisitados(G);
    topologicalSort(G);
    distancia[s.idx] = 0;
    for (Intervalo I : orden){
        for (Vecino v : G[I.idx]){ relax(I, v.first, v.second);}
    }
}

// complejidad: O(n).
void armarCaminoMinimo(Intervalo& s, Intervalo& d, vector<Intervalo>& padres, vector<Intervalo>& camino){
    if(padre[d.idx] == s){
        camino.push_back(s);
    } else if(padres[d.idx] == Intervalo()){
        camino.push_back(Intervalo());
    } else {
        Intervalo p = padres[d.idx];
        camino.push_back(p);
        armarCaminoMinimo(s, p, padres, camino);
    }
}

void grafoIntervalo(){
    cin >> n;
    int a, b;
    int minA = 2*n - 1;
    int maxB = 0;
    for(int i = 0; i < n; i++){
        cin >> a;
        cin >> b;
        minA = min(a, minA);
        maxB = max(b, maxB);
        intervalos.push_back(Intervalo(a, b, i));
    }

    for(Intervalo Ii : intervalos){
        if (Ii.a == minA && Ii.b == maxB) {
            Intervalo Ij = intervalos[Ii.idx + 1 % n];
            cout << 2 << endl;
            cout << Ii.idx << " " << Ij.idx << endl;
            return;
        }
    }
    // Ordeno los intervalos pasados por parametro segun su a. Complejidad: O(nlog(n)).
    sort(intervalos.begin(), intervalos.end());

    // Agrego al conjunto de nodos de mi grafo los intervalos que no estan completamente contendios en
    // otros. Ademas agrego los intervalos "de mentira" inicio y fin. Complejidad: O(n²).
    Intervalo inicio = Intervalo(-2, -1, 0);
    N.push_back(inicio);
    for(auto Ii : intervalos){
        bool estaIncluido = false;
        for(auto Ij : intervalos){
            if (Ij.a < Ii.a && Ii.b < Ij.b){
                estaIncluido = true;
                break;
            }
        }
        if (!estaIncluido){
            P.push_back(Ii.idx);
            K++;
            Ii.idx = K;
            N.push_back(Ii);
        }
    }
    Intervalo fin = Intervalo(2*n, 2*n + 1, 2*K + 1);
    N.push_back(fin);

    // Sea I un intervalo en N - {fin} tq N[i] = I, su asociado va a ser el elemento en la posicion intervaloAsociado[i].
    // El intervalo asociado se define como el primer intervalo en intervalos que termina luego del fin
    // de un intervalo I en N - {fin}. Esto me va a servir para armar el conjunto de aristas C en tiempo O(n²).
    // Complejidad: O(n²).
    for(int i = 0; i < N.size() - 1; i++){
        Intervalo Ii = N[i];
        Intervalo iAsociado = fin;
        for(int j = 0; j < intervalos.size(); j++){
            Intervalo Ij = intervalos[j];
            if (Ii.b < Ij.a && Ij.b < iAsociado.b)
                iAsociado = Ij;
        }
        intervaloAsociado.push_back(iAsociado);
    }

    // Armo ambos conjuntos de aristas B y C. Complejidad: O(n²).
    for(int i = 0; i < N.size() - 1; i++){
        Intervalo Ii = N[i];
        Intervalo iEsimoAsociado = intervaloAsociado[i];
        for(int j = i + 1; j < N.size(); j++){
            Intervalo Ij = N[j];
            if (Ii.a < Ij.a && Ii.b < Ij.b && Ij.a < Ii.b) B.push_back(Arista(Ii, Ij, 1));
            if (Ii.b < Ij.a && !(Ii.b < iEsimoAsociado.a && iEsimoAsociado.b < Ij.a)) C.push_back(Arista(Ii, Ij, Ii.idx == 0 ? 0 : 1));
        }
    }

    // Aumento el tamaño del conjunto de nodos como del grafo para poder incluir a los nodos
    // I_in e I_out. Complejidad: O(K) = O(n) ya que a lo sumo en N tendria a todos
    // los intervalos que me pasan por parametro. Luego aumentaria al doble de intervalos
    // en mi grafo y eso es O(2n) = O(n).
    N.resize(2*(K + 1));
    D.resize(2*(K + 1));

    // Agrego propiamente a los Iout en N en la posicion I_in.idx + K. Ademas incluyo en G
    // a la arista (I_in, I_out, 0). Complejidad: O(K) = O(n).
    for(int i = 1; i <= K; i++){
        Intervalo Iin = N[i];
        Intervalo Iout = Intervalo(Iin.a, Iin.b, Iin.idx + K);
        N[i + K] = Iout;
        Arista e = Arista(Iin, Iout, 0);
        D[Iin.idx].push_back(Vecino(e.v, e.w));
    }
    N[2*K + 1] = fin;

    // Aumento el tamaño de P para incluir en P[K] el mismo indice que hay en P[i-K] (su equivalente I_in).
    // Complejidad: O(K) = O(n).
    P.resize(2*K);
    for(int i = K; i < P.size(); i++){P[i] = P[i - K];}

    // Agrego al Grafo las aristas en B y en C teniendo en cuenta a las I_out.
    // Complejidad: O(|B| + |C|) = O(m) = O(n²).
    for(Arista e: B){D[e.u.idx + K].push_back(Vecino(e.v, e.w));}
    for(Arista e : C){D[e.u.idx].push_back(Vecino((e.v.idx == fin.idx) ? fin : N[e.v.idx + K], e.w));}

    // Complejidad: O(m + n) = O(n²).
    DAGShortestPath(D, inicio);
    vector<Intervalo> caminoMin{fin};
    // Complejidad: O(n)
    armarCaminoMinimo(inicio, fin, padre, caminoMin);
    // Invierto el orden del camino ya que me lo da al reves. Complejidad: O(n).
    reverse(caminoMin.begin(), caminoMin.end());

    // Guardo en CDT los indices de los nodos por los que pasa el
    // caminoMin sin contar al inicio y fin. Los indices guardados van a representar al
    // iesimo intervalo pasado originalmente por parametro. Complejidad: O(nlog(n)).
    set<int> CDT;
    for(Intervalo I : caminoMin){ if(0 < I.idx  && I.idx < 2*K + 1) CDT.insert(P[I.idx - 1]);}

    // Escribo por consola el cardinal del CDT y cada elemento de este. Complejidad: O(n).
    cout << CDT.size() << endl;
    for(int e : CDT){ cout << e << " ";}
}

/*
    int minA = 2*n - 1;
    int maxB = 0;
    for(Intervalo Ii : intervalos){
        minA = min(Ii.a, minA);
        maxB = max(Ii.b, maxB);
    }
*/

/*
    for (int i = 0; i < D.size(); i++) {
        for (const auto& [v, w] : D[i]) {
            cout << i << " " << v.idx << " " << w << endl;
        }
*/

