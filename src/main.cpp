#include <iostream>
#include "ej1.h"
#include<chrono>

using namespace std;
using namespace std::chrono;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

int main(int argc, char *argv[])
{
    switch (stoi(argv[1]))
    {
        case 1: {
            cout << "Hola Juli" << endl;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = chrono::system_clock::now();

            grafo g = grafo();

            solverEj1(g);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> duracion = end - start;

            std::cout << "Tiempo de ejecucion: " << fixed << duracion.count() << "s\n";

            break;
        }
        case 2:
            cout << "Hola Tomi" << endl;
            break;
        case 3:
        {
            cout << "Hola Facu" << endl;
            /*Digrafo g = Digrafo();
            johnson(g);*/
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