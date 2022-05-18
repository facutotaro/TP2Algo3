#include <iostream>
#include "dijkstra.h"
#include "bellmanFord.h"
#include "digrafo.h"

using namespace std;

int main(int argc, char *argv[])
{
   switch (stoi(argv[1]))
   {
   case 1:
        cout << "Hola Juli" << endl;
       break;
   case 2: 
        cout << "Hola Tomi" << endl;
        break;
    case 3:
    {
        cout << "Hola Facu" << endl;
        Digrafo g = Digrafo();
        dijkstra(g,2);
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