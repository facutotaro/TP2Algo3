#include "johnson.h"
void johnson(Digrafo &g)
{
    //Agregamos un nodo la lista de adyacencias O(1)
    g._adylst.push_back(vector<Cabeza>());
    //Este nodo apunta hacia todos los los nodos previos del grafo O(n)
    for (int i = 0; i < g._nodos; i++)
    {
        g._adylst[g._nodos].push_back(Cabeza(i, 0));
    } //O(n) espacio. Como es convezo m > n por lo que O(m) espacio
    //Modificamos la cantidad de aristas y nodos O(1)
    g._aristas += g._nodos;
    g._nodos++;
    //Creamos un vector de distancias desde el nodo agregado a todos los otros O(n)
    vector<dist> res = vector<int>(g._nodos, INF); //O(n) espacio. Como es convezo m > n por lo que O(m) espacio
    /*Aplicamos el algoritmo de BellMan-Ford desde el nodo agregado y obtenemos las 
    distancias desde este nodo a todos los otros.
    Bellman-Ford devuelve false e imprime un ciclo de longitud negativa si existen ciclos de
    longitud negativa. Si no los encuentra devuelve true
    */
    Nodo source = g._nodos - 1;
    if (bellmanFord(g, source, res)) //O(nm)
    {
        //Si no se encontraron ciclos de longitud negativa imprime 1, ya que vamos a poder 
        //aplicar Dijkstra
        cout << 1 << endl;
        //Modifico el peso w(u,v) de todas las aristas u->v por ŵ(u,v)
        //tal que ŵ(u,v) = w(u,v) + dist(s,u) - dist(s,v) siendo s el nodo que agregamos
        //De esta manera no se tienen aristas de longitud negativa
        for (int i = 0; i < g._adylst.size()-1; i++)
        {
            for (int j = 0; j < g._adylst[i].size(); j++)
            {
                g._adylst[i][j].w = g._adylst[i][j].w + res[i]-res[g._adylst[i][j].t];
            }
            
        } //O(m)
        //Eliminamos el nodo y todas las aristas que habiamos agregado
        g._adylst.pop_back();
        g._aristas = g._aristas - g._nodos + 1;
        g._nodos--;
        //Para todos los nodos del grafo, aplico Dijkstra
        for (int i = 0; i < g._nodos; i++)
        {
            dijkstra(g,i,res);
        } //O(n*m*log n)   
    }
} //Peor caso O(nm+nmlogn) tiempo, O(3m) = O(m) espacio