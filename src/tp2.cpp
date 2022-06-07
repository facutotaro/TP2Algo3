#include <iostream>
#include "dijkstra.h"
#include "bellmanFord.h"
#include "digrafo.h"
#include "johnson.h"
#include "grafoIntervalo.h"
#include "Ej2Solver.h"

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
   switch (stoi(argv[1]))
   {
   case 1:
        cout << "Hola Juli" << endl;
       break;
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
        grafoIntervalo();
        break;
   default:
        cout << "No master ese ej no lo tengo" << endl;
       break;
   }  
}
