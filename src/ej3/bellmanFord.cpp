#include "bellmanFord.h"
const int INF = std::numeric_limits<int>::max();

//Para evitar el overflow, defino la función suma para sumar infinitos
dist suma(int a, int b)
{
    if (a == INF || b == INF)
        return INF;
    else
        return a + b;
}

bool bellmanFord(Digrafo &g, Nodo &n, vector<dist> &res)
{
    //Defino un vector de parentescos
    vector<Nodo> parents = vector<int>(g._nodos, -1); //O(n) tiempo, O(n) espacio. Como es conexo, O(m) espacio
    res[n] = 0; //La distancia del nodo a si mismo es 0
    parents[n] = n; //Y es su propio padre
    //Relajo todas las aristas n-1 veces
    for (int i = 0; i < g._adylst.size() - 1; i++)
    {
        for (int j = 0; j < g._adylst.size(); j++)
        {
            for (int k = 0; k < g._adylst[j].size(); k++)
            {
                dist aux = suma(res[j], g._adylst[j][k].w);
                if (res[g._adylst[j][k].t] > aux)
                {
                    res[g._adylst[j][k].t] = aux;
                    parents[g._adylst[j][k].t] = j;
                }
            }
        }
    } //O(nm)

    //Encontrado y primero del ciclo son variables que usaremos para encontrar
    //Un ciclo negativo si es que lo hay
    bool encontrado = false;
    Nodo primeroDelCiclo;
    //Relajo todas las aristas una vez más
    for (int j = 0; j < g._adylst.size(); j++)
    {
        for (int k = 0; k < g._adylst[j].size(); k++)
        {
            dist aux = suma(res[j], g._adylst[j][k].w);
            //Si encuentro alguna que puedo seguir relajando actualizo su peso y su parent
            if (res[g._adylst[j][k].t] > aux)
            {
                res[g._adylst[j][k].t] = aux;
                parents[g._adylst[j][k].t] = j;
                //Si es el la primera arista que puedo relajar me guardo el nodo de salida de la arista
                if (!encontrado)
                {
                    primeroDelCiclo = j;
                    encontrado = true;
                }
            }
        }
    }//O(m)

    if (!encontrado) return true; //Si no se encontró ninguna arista que se pueda relajar, devuelvo true
    else {
        //Si se encontró imprimo 0
        cout << 0 << endl;
        //Creo un vector de nodos para guardar el necorrido
        vector<Nodo> ciclo;
        //Creo un vector de enteros visitados para guardarme el momento en el que se visito
        //Cada posicion del vector ciclo corrresponde a un momento en el que se visito el nodo
        //Inicializamos en -1 a todos los valores a modo tal de decir que no se visitaron
        vector<int> visitados =vector<int>(g._nodos,-1);
        /*Pusheo el nodo que me habia guardado a ciclo. 
        Sabiendo que este pertenece a una arista que pertenece a un ciclo de peso negativo, ya que
        la habia podido relajar*/
        ciclo.push_back(primeroDelCiclo);
        //Defino que en el momento en el que fue visitado por primera vez fue en el instante 0
        visitados[primeroDelCiclo] = 0;
        int actual = parents[primeroDelCiclo];
        int counter = 1;
        //El padre, es un nodo por el cual al relajarse las aristas se encontró una distancia menor.
        //Sabemos que el nodo que teniamos pertenecia a un ciclo de longitud negativa. El nodo del padre
        //puede tanto pertenecer a un ciclo de longitud negativa o venir desde una arista la cual
        //paso por un camino que al relajarse se habian relajado las aristas de un camino desde la fuente a ella
        //que pasaban por un ciclo de longitud negativa
        //Dicho todo esto, nos podemos encontrar en situaciones donde siguiendo los padres, no vamos a volver
        //a el primer nodo del primer ciclo de longitud negativa que nos encontramos al relajar, pero sabemos que
        //eventualmente pasaremos dos veces por el mismo nodo si empezamos a subir por los padres. Para ello esta
        //el vector de visitados.
        //Iremos subiendo por los padres hasta encontrar qye recorrimos dos veces el mismo nodo
        while (visitados[actual] == -1)
        {
            visitados[actual] = counter;
            counter++;
            ciclo.push_back(actual);
            actual = parents[actual];
        } //O(n) tiempo y espacio
        ciclo.push_back(actual);
        //Una vez encontrado el vertice por el que pasamos dos veces, sabemos el recorrido de los nodos que tenemos
        //en ciclo. Lo imprimimos desde el ultimo elemento hasta el primero. Ciclo tiene a lo sumo n elementos porque puede pasar
        //a lo sumo dos veces por cada vertice.
        for (int i = ciclo.size()-1; i >= visitados[actual]; i--)
        {
            cout << ciclo[i] << " ";
        } //O(n)
        cout << endl;
        return false;
    }
} //Peor caso: O(nm+m+2*n) = O(nm) tiempo y O(2n) = O(n) = O(m) espacio 
