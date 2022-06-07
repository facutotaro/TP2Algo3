#include "ej1.h"

void solverEj1(grafo g){
    vector<vector<int>> predecesores(g._nVertices, vector<int>(g._nVertices, -1));
    vector<vector<int>> caminosMinimos(2);
    bool esGeodesico = true;
    if (g._nVertices==1){
        cout << 1 << endl << 0 << endl;
    } else {
        for (int i = 0; i < g._nVertices; ++i) {
            esGeodesico = esGeodesico && g.bfs(i, &predecesores, &caminosMinimos);
        }

        if (esGeodesico) {
            cout << 1 << endl;
            for (int i = 0; i < predecesores.size(); ++i) {
                for (int j = 0; j < predecesores[i].size(); ++j) {
                    cout << predecesores[i][j] << "  ";
                }
                cout << endl;
            }
        } else {
            cout << 0 << endl;
            for (int i = 0; i < caminosMinimos.size(); ++i) {
                for (int j = 0; j < caminosMinimos[i].size(); ++j) {
                    cout << caminosMinimos[i][j] << "  ";
                }
                cout << endl;
            }
        }
    }
}

