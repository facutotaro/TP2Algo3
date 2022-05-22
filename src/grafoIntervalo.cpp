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
        _intervalos.push_back(make_pair(Intervalo(a, b), make_pair(i, false)));
    }

    sort(_intervalos.begin(), _intervalos.end(), [](Intervalo v, Intervalo u) { // Ordeno segun a creciente. 
            return v.a < u.a;
        });

    Intervalo primerInt = _intervalos[0].first;
    Intervalo ultimoInt = _intervalos[_n-1].first;
    
    int aInicio = primerInt.a - 2; 
    int bInicio = primerInt.a - 1; 

    int aFin = ultimoInt.a + 1; 
    int bFin = ultimoInt.a + 2;

    _inicio = Intervalo(aInicio, bInicio); // _inicio es menor a cualquier otro intervalo. 
    _fin = Intervalo(aFin, bFin);   // _fin es mayor a cualquier otro intervalo. 

    _adylstIn = vector<vector<Cabeza>>(_n, vector<Cabeza>());
    _adylstOut = vector<vector<Cabeza>>(_n, vector<Cabeza>());

    for (int i = 0; i < _n; i ++) // Construyo N'. 
    {
        bool estaIncluido = false;
        Intervalo iInt = _intervalos[i].first;
        for(auto const& j : _intervalos)
        {
            Intervalo jInt = j.first; 
            if (jInt.a < iInt.a < iInt.b < jInt.b)
            {
                estaIncluido = true; 
                break;
            }
        }
        if (!estaIncluido)          
        {

            _intervalos[i].push_back(make_pair(iInt, iIndex));
            _adylstIn[iIndex].push_back(Cabeza(iInt, 0));
        }
    }

    for (auto const& [iInt, iIndex] : _N)  // Construyo B. 
    {
        for(auto const& [jInt, jIndex] : _N)
        {
            if(iInt.a < jInt.a < iInt.b < jInt.b) 
                _adylstOut[iIndex].push_back(Cabeza(jInt, 1));
        }
    }

    // Construyo C: 
    for (int i = 0; i < _n-1; i++) // Caso Ih intermedios. 
    {
        Intervalo iEsimo = _N[i].first;
        bool seIntersecan = false;
        for (int j = i+1; j < _n && !seIntersecan; j++)
        {
            Intervalo jEsimo = _N[j].first;
            if(iEsimo.b < jEsimo.a)
            {

            } 
            else 
            {
                seIntersecan = true; 
            }
        }
    }
    
}

GrafoIntervalo::~GrafoIntervalo(){}

void GrafoIntervalo::mostrar()
{

}
