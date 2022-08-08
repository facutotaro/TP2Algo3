#include <iostream>
#include "ej3/dijkstra.h"
#include "ej3/bellmanFord.h"
#include "ej3/digrafo.h"
#include "ej3/johnson.h"
#include "ej4/grafoIntervalo.h"
#include "ej2/Ej2Solver.h"
#include "ej1/ej1.h"

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
   switch (stoi(argv[1]))
   {
   case 1:
    {
        grafo g = grafo();
        solverEj1(g);
        break;
    }
   case 2:
   { 
        Ej2Solver s = Ej2Solver();
        cout << s.cantCompConexas() << endl;
        break;
    }
    case 3:
    {
        Digrafo g = Digrafo();
        johnson(g);
        break;
    }
    case 4:
    {
        grafoIntervalo();
        break;
    }
   default:
    {
        cout << "Vuelva a ejecutar con un numero de ejercicio valido" << endl;
        break;
    }
   }  
}
