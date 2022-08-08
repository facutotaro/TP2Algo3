#include "dijkstra.h"
#include <iostream>
#include <limits>
#include <set>
using namespace std;
const int INF = std::numeric_limits<int>::max();
typedef int dist;
typedef pair<int,Nodo> Pendiente;

void dijkstra(Digrafo &g, Nodo n, vector<int> &pesos)
{
    //Armo un vector de distancia para tener la distancia desde mi nodo a todos los otros
    vector<dist> res = vector<dist>(g._nodos,INF); //O(n) tiempo y espacio
    res[n] = 0; //La distancia de un nodo a si mismo es 0
    //Defino un set de nodos para que la complejidad de modificado y borrado de estos sea log n
    set<Pendiente> cola;
    //Inserto todos los nodos en el conjunto    
    for (int i = 0; i < g._nodos; i++)
    {
        cola.insert(Pendiente(res[i],i));
    } //O(n log n) tiempo. O(n) espacio
    while (cola.size() > 0) //Hasta que no se vacie la cola
    {
        //Tomo el elemento de mayor prioridad, es decir el que tiene la menor distancia y lo elimino de la cola
        Pendiente p = *cola.begin();
        cola.erase(p);
        Nodo n = p.second;
        //Verifico para cada nodo desde el que este exita una arista que sale de este si
        //si se puede encontrar un camino más corto 
        for (int i = 0; i < g._adylst[n].size(); i++)
        {
            int aux = INF;
            Nodo prox = g._adylst[n][i].t;
            //Si la distancia(res[n]) es distinta de infinito, significa que se pudo llegar de otros de 
            //los vertices hasta el que se está evaluando. Si al momento de tomar al vertice n como el 
            //vertice a evaluar, significa que desde el vertice origen no hay forma de llegar a este. 
            //De ser ese el caso las siguientes dos comparaciones no se ejecutarán las condiciones ya que 
            //al ser infinita la distancia, no hay una distancia menor a los otros de los vecinos
            //Verifica si la distancia es distinta de infinito para evitar el overflow
            if(res[n] != INF)
            {
                //Sea s el nodo del que queremos ver la distancia hasta los otros,
                //aux = dist(s,n) + w(n,i) 
                aux = res[n] + g._adylst[n][i].w;
            }
            //En caso de que aux sea infinito, es decir no se entró a la guarda anterior, esto no se ejecuta
            if (res[prox] > aux)
            {
                //Si aux es distito de infinito, y es menor a dist(s,i), entonces existe un camino más corto
                //hasta el nodo i pasando por n, por lo que se actualiza en el conjunto y en el array de distancias
                cola.erase(Pendiente(res[prox],prox));
                res[prox] = aux;
                cola.insert(Pendiente(res[prox],prox));
            }
        }//O(ds(V_i)*log(n))
    } //O(n log(n)+ m log(n)) => O(m log n) ya que los grafos son conexos

    //Como los pesos fueron modificados, hay que operar sobre ellos para obtener la distancia original
    for (int i = 0; i < res.size(); i++)
    {
        if (res[i] == INF)
        {
            cout << "INF ";
        }
        else cout << res[i] + pesos[i] - pesos[n]<< " ";
    }
    cout << endl;
}