#include "grafoIntervalo.h"

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

    sort(_intervalos.begin(), _intervalos.end(), [](Intervalo v, Intervalo u) {
            return v.a < u.a;
        });

    Intervalo primerInt = _intervalos[0].first;
    Intervalo ultimoInt = _intervalos[_n-1].first;
    
    int aInicio = primerInt.a - 2;
    int bInicio = primerInt.a - 1; 

    int aFin = ultimoInt.a + 1; 
    int bFin = ultimoInt.a + 2;

    _inicio = Intervalo(aInicio, bInicio);
    _fin = Intervalo(aFin, bFin);

    _adylstIn = vector<vector<Cabeza>>(_n, vector<Cabeza>());
    _adylstOut = vector<vector<Cabeza>>(_n, vector<Cabeza>());

    for (auto const& [iInt, iIndex] : _intervalos) // Construyo N'. 
    {
        bool estaIncluido = false;
        for(auto const& [jInt, jIndex] : _intervalos)
        {
            if (jInt.a < iInt.a < iInt.b < jInt.b)
            {
                estaIncluido = true; 
                break;
            }
        }
        if (!estaIncluido)
        {
            _N.push_back(make_pair(iInt, iIndex));
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

    // Construyo C. 
    
}

GrafoIntervalo::~GrafoIntervalo(){}

void GrafoIntervalo::mostrar()
{

}
