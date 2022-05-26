#include "grafoIntervalo.h"

// Sea un Intervalo I = [a, b].

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
    for (Intervalo iInt : intervalosEnN)  
    {
        for (Intervalo jInt : intervalosEnN)
        {
            if (iInt.a < jInt.a < iInt.b < jInt.b) 
            {
                NodoInt jNodoIn = NodoInt(jInt, 1);
                _adylst[iInt.idx][1].push_back(CabezaInt(jNodoIn, 1));
            }
        }
    }

    // Construyo C.  
    // Primer le asigno a cada intervalo en _N un intervalo asociado en _intervalos 
    // tq' sea el primer intervalo que finaliza dentro suyo, O(n²).

    // Para eso inicializo el vector auxiliar intervaloAsociado. 
    vector<Intervalo> intervaloAsociado(_n + 1, Intervalo());

    for (int i = 0; i < intervalosEnN.size() - 1; i++)
    {
        Intervalo iInt = intervalosEnN[i];
        Intervalo iAsociado = intFin;  
        for (int j = i + 1; j < _intervalos.size(); j++)
        {
            Intervalo jEsimo = _intervalos[j];
            if (iInt.b < jEsimo.a && jEsimo.b < iAsociado.b) iAsociado = jEsimo;
        }
        intervaloAsociado[iInt.idx] = iAsociado; 
    }

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

