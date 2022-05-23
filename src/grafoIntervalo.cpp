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
        _intervalos.push_back(make_pair(Intervalo(a, b), i));
    }

    // Ordeno segun a creciente, O(nlog(n)).
    sort(_intervalos.begin(), _intervalos.end(), [](Intervalo v, Intervalo u) { 
            return v.a < u.a;
        });

    // Creo intervalos "de mentira" _inicio(I_0 en paper) e _fin(I_n+1 en paper), O(n).
    Intervalo primerInt = _intervalos[0].first;
    int aInicio = primerInt.a - 2; 
    int bInicio = primerInt.a - 1; 
    Intervalo minB = min_element(_intervalos.begin(), _intervalos.end(), [](pair<Intervalo, indxOg> v, pair<Intervalo, indxOg> u) {
        return v.first.b < u.first.b;
    })->first;
    _inicio = make_pair(Intervalo(aInicio, bInicio), minB); 

    Intervalo ultimoInt = _intervalos[_n-1].first;
    int aFin = ultimoInt.a + 1; 
    int bFin = ultimoInt.a + 2;
    _fin = make_pair(Intervalo(aFin, bFin), Intervalo());

    _adylstIn = vector<vector<Cabeza>>(_n, vector<Cabeza>());
    _adylstOut = vector<vector<Cabeza>>(_n, vector<Cabeza>());

    // Construyo N', O(n²).
    for (auto const& [iInt, iIndx] : _intervalos) 
    {
        bool estaIncluido = false;
        for (auto const& [jInt, jIndx] : _intervalos)
        {
            if (jInt.a < iInt.a < iInt.b < jInt.b)
            {
                estaIncluido = true; 
                break;
            }
        }
        if (!estaIncluido)         
        {
            _N.push_back(make_pair(iInt, iIndx));
            _adylstIn[iIndx].push_back(Cabeza(iInt, 0));
        } 
    }

    // Construyo B', O(n²).
    for (auto const& [iInt, iIndex] : _N)  
    {
        for (auto const& [jInt, jIndex] : _N)
        {
            if (iInt.a < jInt.a < iInt.b < jInt.b) 
                _adylstOut[iIndex].push_back(Cabeza(jInt, 1));
        }
    }

    // Construyo C'.  
    // Primer le asigno a cada intervalo en _N un intervalo asociado en _intervalos 
    // tq' sea el primer intervalo que finaliza dentro suyo, O(n²).
    _intervaloAsociado = vector<Intervalo>(_n, Intervalo());
    for (int i = 0; i < _N.size(); i++)
    {
        Intervalo iNodo = _N[i].first;
        Intervalo iAsociado = _fin.first; 
        for(int j = i + 1; j < _intervalos.size(); j++)
        {
            Intervalo jEsimo = _intervalos[j].first;
            if (iNodo.b < jEsimo.a && jEsimo.b < iAsociado.b) iAsociado = jEsimo;
        }
        _intervaloAsociado[_N[i].second] = iAsociado; 
    }

    // Luego voy iterando sobre los intervalos que son nodos viendo si su asociado esta entre ellos, 
    // en caso negativo los agrego como aristas del grafo, O(n²).
    for (auto const& [iInt, iIndx] : _N)
    {
        Intervalo iEsimoAsociado = _intervaloAsociado[iIndx];
        for(auto const& [jInt, jIndx] : _N)
        {
            if (iInt.b < jInt.a && !(iInt.b < iEsimoAsociado.a < iEsimoAsociado.b < jInt.a))
                _adylstIn[iIndx].push_back(Cabeza(jInt, 1));
        }
        // Caso Int_0: 
        if(bInicio < iInt.a && !(bInicio < minB.a < minB.b < iInt.a))
            _adylstInicio.push_back(Cabeza(iInt, 0));

        // Caso Int_n+1
        if (iInt.b < _fin.first.a && !(iInt.b < iEsimoAsociado.a < iEsimoAsociado.b < _fin.first.a))
            _adylstIn[iIndx].push_back(Cabeza(_fin.first, 1));
    }
}

GrafoIntervalo::~GrafoIntervalo(){}

void GrafoIntervalo::mostrar()
{
    
}
