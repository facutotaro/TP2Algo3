#include "grafoIntervalo.h"

GrafoIntervalo::GrafoIntervalo()
{
    cin >> _n;
    int a, b;
    for(int i = 0; i < _n; i++)
    {
        cin >> a;
        cin >> b; 
        _intervalos.push_back(Intervalo(a, b));
    }
    
    sort(_intervalos.begin(), _intervalos.end(), [](Intervalo v, Intervalo u) {
            return v.a < u.a;
        });
    
    int aInicio = _intervalos[0].a - 2;
    int bInicio = _intervalos[0].a - 1; 

    int aFin = _intervalos[_n-1].a + 1; 
    int bFin = _intervalos[_n-1].a + 2;

    _inicio = Intervalo(aInicio, bInicio);
    _fin = Intervalo(aFin, bFin);

    for(int i = 0; i < _n; i++) // Construyo N'. 
    {
        Intervalo actual =_intervalos[i];
        bool estaIncluido = false;
        for(Intervalo j: _intervalos)
        {
            if (j.a < actual.a < actual.b < j.b)
            {
                estaIncluido = true; 
                break;
            }
        }
        if (!estaIncluido)
        {
            _N.push_back(actual);
            _adylstIn[i].push_back(Cabeza(actual, 0));
        }
    }



}

GrafoIntervalo::~GrafoIntervalo(){}

void GrafoIntervalo::mostrar()
{

}
