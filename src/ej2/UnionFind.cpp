#include "UnionFind.h"

using namespace std;

UnionFind::UnionFind(int n) {
    _parent = vector<vector<int>>(2, vector<int>(n, -1));
    _ranks = vector<int>(2*n, 0);
    /*
     * Tenemos 2 niveles de parent para poder distinguir entre los parents de la última fila procesada y la
     * que estoy procesando actualmente. Si tengo que redefinir el vértice "raiz" de una componente conexa
     * (es decir su "tag" o representante), no debería poder usar un indice que puede pertenecer a una componente
     * conexa preexistente (de la primera fila). Tengo 2*n posiciones de ranks por esto mismo, los "parents"
     * del nivel superior están en el rango [0, n) y los del nivel inferior entre [n, 2n).
     */
}

void UnionFind::makeSet(int n) {
    _parent[1][n] = n + _parent[0].size();
}

int UnionFind::findSet(int j) {
    int res = j;
    if(res != _parent[(j/_parent[0].size())][(j%_parent[0].size())]){
        _parent[(j/_parent[0].size())][(j%_parent[0].size())] = findSet(_parent[(j/_parent[0].size())][(j%_parent[0].size())]);
        res = _parent[(j/_parent[0].size())][(j%_parent[0].size())];
    }
    return res;
    /*
     * Como 0 <= j < 2n, entonces identifico en qué fila de parent está el tag mediante la división (si
     * 0 <= j < n, j / n = 0 y en caso contrario, j/n = 1) y su posición relativa con la operación módulo.
     * Notese además que se hacePath Compression, hago que todos los miembros de una compontente apunten a
     * su tag cuando llamamos a findSet(j). Esta propiedad hace que mediante el UnionFind se pueda computar
     * la cantidad de componentes conexas en O(mn*alpha(mn)), donde alpha es la función inversa de Ackermann.
     */
}

void UnionFind::unionLink(int j, int k) {
    int parJ = findSet(j);
    int parK = findSet(k);

    if(parJ == parK) return;

    if(_ranks[parJ] < _ranks[parK]){
        _parent[parJ/_parent[0].size()][parJ%_parent[0].size()] = parK;
    } else{
        if(_ranks[parJ] == _ranks[parK]){
            _ranks[parJ]++;
        }
        _parent[(parK/_parent[0].size())][(parK%_parent[0].size())] = parJ;
    }
    /*
     * Utilizamos Union By Rank ya que es la otra de las optimizaciones provistas por el Cormen para hacer
     * más eficiente el UnionFind.
     */
}

void UnionFind::cambiarRaiz(int j) {
    _ranks[j + _parent[0].size()] = _ranks[_parent[0][j]];
    _parent[0][_parent[0][j] % _parent[0].size()] = j + _parent[0].size();
    /*
     * Introducimos esta nueva función que justamente logra que se mantenga una componente conexa de una
     * fila a la siguiente. Mediante estas dos lineas, el parent de la componente conexa de la fila anterior
     * apunta a la posición tag de la nueva fila para que al hacer findSet se consiga que todo
     * vértice que continúa una componente conexa en la fila actual se represente por el mismo indice.
     * Para esto además se heredan los ranks del tag anterior.
     */
}

void UnionFind::reestablecer() {
    for(int i = 0; i < _parent[0].size(); i++){
        _parent[0][i] = (_parent[1][i] == -1) ? -1 : (_parent[1][i] % _parent[0].size());
        _parent[1][i] = -1;
        _ranks[i] = _ranks[i + _parent[0].size()];
        _ranks[i + _parent[0].size()] = 0;
    }
    /*
     * Preparamos los arreglos de parent y ranks para procesar la siguiente fila.
     */
}
