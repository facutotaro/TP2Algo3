#include "grafoIntervalo.hpp"

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

    _adylstIn = vector<vector<Cabeza>>(_n + 1, vector<Cabeza>());
    _adylstOut = vector<vector<Cabeza>>(_n + 1, vector<Cabeza>());

    // Construyo N', O(n²).
    // Creo intervalos "de mentira" inicio(I_0 en paper) e fin(I_n+1 en paper), O(n).
    Nodo inicio = Nodo(Intervalo(_intervalos.front().a - 2, _intervalos.front().b - 1, 0), NULL);
    _N.push_back(inicio);
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
            Nodo iIntIn = Nodo(iInt, "in"); 
            Nodo iIntOut = Nodo(iInt, "out");
            _N.push_back(iIntIn);
            _N.push_back(iIntOut); 
            _adylstIn[iInt.idx].push_back(Cabeza(iIntOut, 0));
        } 
    }
    Nodo fin = Nodo(Intervalo(_intervalos.back().a + 1, _intervalos.back().b + 2, _n), NULL);
    _N.push_back(fin);
   
    // Construyo B', O(n²).
    for (Nodo iNodo : _N)  
    {
        if (iNodo.type == "out")
        {
            for (Nodo jNodo : _N)
            {
                if (jNodo.type == "in")
                {
                    if (iNodo.I.a < jNodo.I.a< iNodo.I.b < jNodo.I.b) 
                        _adylstOut[iNodo.I.idx].push_back(Cabeza(jNodo, 1));
                }
            }
        }
    }

    // Construyo C'.  
    // Primer le asigno a cada intervalo en _N un intervalo asociado en _intervalos 
    // tq' sea el primer intervalo que finaliza dentro suyo, O(n²).
    _intervaloAsociado = vector<Intervalo>(_n + 1, Intervalo());
    for (int i = 0; i < _N.size() - 1; i++)
    {
        Nodo iNodo = _N[i];
        Intervalo iAsociado = fin.I;  
        for (int j = i + 1; j < _intervalos.size(); j++)
        {
            Intervalo jEsimo = _intervalos[j];
            if (iNodo.I.b < jEsimo.a && jEsimo.b < iAsociado.b) iAsociado = jEsimo;
        }
        _intervaloAsociado[iNodo.I.idx] = iAsociado; 
    }

    // Luego voy iterando sobre los intervalos que son nodos viendo si su asociado esta entre ellos, 
    // en caso negativo los agrego como aristas del grafo, O(n²).
    for (Nodo iNodo : _N)
    {
        Intervalo iEsimoAsociado = _intervaloAsociado[iNodo.I.idx];
        for (Nodo jNodo : _N)
        {
            if (iNodo.I.b < jNodo.I.a && !(iNodo.I.b < iEsimoAsociado.a < iEsimoAsociado.b < jNodo.I.a))
                if (iNodo == inicio)
                    _adylstIn[iNodo.I.idx].push_back(Cabeza(jNodo, 0));
                else 
                    _adylstIn[iNodo.I.idx].push_back(Cabeza(jNodo, 1));
        }
    }
}

GrafoIntervalo::~GrafoIntervalo(){}

