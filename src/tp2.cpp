#include <iostream>
#include "dijkstra.h"
#include "bellmanFord.h"
#include "digrafo.h"
#include "Ej2Solver.h"

using namespace std;

int main(int argc, char *argv[])
{
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
        cout << "Hola Facu" << endl;
        Digrafo g = Digrafo();
        g.mostrar();
        break;
    }
    case 4:
        cout << "Hola Fede" << endl;
        break;
   default:
        cout << "No master ese ej no lo tengo" << endl;
       break;
   }
    
}
