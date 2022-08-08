#include "UnionFind.h"
#include "Ej2Solver.h"

#include <vector>
#include <iostream>

using namespace std;

Ej2Solver::Ej2Solver() : _n(0), _m(0) {
    cin >> _m;
    cin >> _n;
}

int Ej2Solver::cantCompConexas() {
    int res = 0;
    UnionFind compConexas = UnionFind(_n);
    vector<bool> changeRoot(_n, false);

    /*
     * changeRoot nos sirve para determinar en qué columnas se encuentran las "raices" (o tags) redefinidas
     * de las componentes conexas de una fila a la siguiente. Cómo no quiero que dos componentes conexas
     * tengan la misma raiz, si un findSet de otra componente apunta a una posición que ya modifiqué,
     * eso significa que las dos componentes en realidad son la misma.
     */

    vector<vector<int>> dosFilas(2, vector<int>(_n, 0));

    /*
     * Vamos a procesar una fila a la vez pero siempre manteniendo constancia de la fila anterior.
     * Como 2*n pertenece a O(n) no nos vamos de la complejidad espacial requerida.
     */

    bool posAnteriorVert = false; //Va a ayudarnos a determinar si habrá que hacer un union entre j y j - 1.
    int prevParent;

    for(int i = 0; i < _m; i++){

        for(int j = 0; j < _n; j++){
            cin >> dosFilas[1][j]; //recibo por input si hay un vértice o no.
            if(dosFilas[1][j]){ //si hay
                compConexas.makeSet(j); //creo el set con tag j + n.
                res++; //Por ahora podría ser una componente conexa nueva, por lo que la contabilizo parcialmente.
                prevParent = (dosFilas[0][j]) ? compConexas.findSet(j) : -1;
                if(prevParent != -1 && !changeRoot[prevParent % _n]){
                    /*
                     * Si el vértice actual tiene precedencia de la fila anterior y aún no cambié la raiz
                     * de la componente a la que pertenece.
                     */
                    compConexas.cambiarRaiz(j);
                    changeRoot[j] = true;
                    res--; //Ya pertenece a una componente conexa predefinida.
                }
            }
            if(posAnteriorVert && dosFilas[1][j]){
                //Si hay un vértice en M[i][j - 1] y M[i][j] (donde M es la matriz pasada como input).
                res--; //Ya pertenece a una/otra componente conexa predefinida.
                compConexas.unionLink(j + _n, j - 1 + _n);
            }
            if(dosFilas[0][j] && dosFilas[1][j]){
                if(compConexas.findSet(j) != compConexas.findSet(j + _n)){
                    // Si hay un vértice en la fila actual y en la fila inmediatamente superior y hasta ahora
                    // no compartían representante de la componente conexa.
                    compConexas.unionLink(j, j + _n);
                    res--; //Ya pertenece a una/otra componente conexa predefinida.
                }
            }
            posAnteriorVert = dosFilas[1][j]; //Si en la fila actual hay un vértice, puedo hacer union con la siguiente.
        }

        for(int j = 0; j < _n; j++){
            dosFilas[0][j] = dosFilas[1][j];
            dosFilas[1][j] = 0;
            changeRoot[j] = false;
        }

        posAnteriorVert = false;
        compConexas.reestablecer();
        // Reestablezco todas las estructuras para que la "fila actual" sea la nueva "fila anterior".
    }

    return res; //Retorno cantidad de componentes conexas.
}
