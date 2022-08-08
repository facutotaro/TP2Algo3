#include "grafo.h"

int inf = numeric_limits<int>::max();

vertice::vertice(int numero) {
    _padre = -1;
    _numero = numero;
    _distancia = inf;
    _color = "blanco";
    _caminosMinimos = 0;
}

vertice::~vertice() {
    _padre = -1;
    _numero = -1;
    _distancia = inf;
    _color = "blanco";
    _caminosMinimos = 0;
}

/*void grafo::mostrar() {
    cout << "mostrar" << endl;
    cout << _nVertices
         << " " << _nAristas << endl;
    for (int i = 0; i < _adylst.size(); i++) {
        int distancia = _vertices[i]._distancia;

        cout << i << "(Dist:" << distancia << ") " << ": ";
        for (int j = 0; j < _adylst[i].size() - 1; j++) {
            cout << _adylst[i][j] << ", ";
        }
        cout << _adylst[i][_adylst[i].size() - 1] << endl;
    }
}*/

grafo::grafo() {
    cin >> _nVertices;
    cin >> _nAristas;
    _adylst = vector<vector<int>>(_nVertices, vector<int>());
    int actual, siguiente;

    _vertices = vector<vertice>(_nVertices, vertice(-1));

    //Itero sobre el input para crear el grafo
    for (int i = 0; i < _nAristas; i++) {
        cin >> actual;
        cin >> siguiente;
        if (_vertices[actual]._numero == -1) {
            _vertices[actual]._numero = actual;
        }
        if (_vertices[siguiente]._numero == -1) {
            _vertices[siguiente]._numero = siguiente;
        }
        _adylst[actual].push_back(siguiente);
        _adylst[siguiente].push_back(actual);
    }
}

grafo::~grafo() {
    _vertices.clear();
    _adylst.clear();
    _nVertices = 0;
    _nAristas = 0;
}

bool grafo::bfs(int s, vector<vector<int>> * pred, vector<vector<int>> * caminosMin) {
    bool esGeodesico = true;
    vector<int> queue;

    //Inicializo el grafo
    for (int i=0; i<_vertices.size(); i++) {
        _vertices[i]._color = "blanco";
        _vertices[i]._distancia = inf;
        _vertices[i]._padre = -1;
    }

    //Arranco desde s
    _vertices[s]._color = "gris";
    _vertices[s]._distancia = 0;
    _vertices[s]._padre = -1;
    _vertices[s]._caminosMinimos = 1;

    queue.push_back(s);
    while (!queue.empty()) {
        vertice* u = &(_vertices[queue.front()]);
        queue.erase(queue.begin());
        for (int j = 0; j < _adylst[u->_numero].size(); ++j) {
            int vecino = _adylst[u->_numero][j];
            if (_vertices[vecino]._color == "blanco") {
                _vertices[vecino]._color = "gris";
                _vertices[vecino]._padre = u->_numero;
                queue.push_back(vecino);
            }
            //Chequeo vertices que tengan distancia = infinito, es decir que no haya descubierto.
            if (_vertices[vecino]._distancia > u->_distancia + 1) {
                _vertices[vecino]._distancia = u->_distancia + 1;
                _vertices[vecino]._caminosMinimos = u->_caminosMinimos;
            } else {
                //Chequeo si tienen mas de un camino minimo
                if (_vertices[vecino]._distancia == u->_distancia + 1) {
                    _vertices[vecino]._caminosMinimos = _vertices[vecino]._caminosMinimos + u->_caminosMinimos;
                }
            }
            //Construyo los dos caminos minimos si no es geodesico (Si hay mas de un camino minimo al vertice)
            if (_vertices[vecino]._caminosMinimos > 1) {
                esGeodesico = false;
                if ((*caminosMin)[0].empty()){
                    (*caminosMin)[0].push_back(vecino);
                    (*caminosMin)[1].push_back(vecino);
                    int actualCamino1 = _vertices[vecino]._padre;
                    int actualCamino2 = u->_numero;
                    while(actualCamino1 != actualCamino2){
                        (*caminosMin)[0].push_back(actualCamino1);
                        (*caminosMin)[1].push_back(actualCamino2);
                        actualCamino1 = _vertices[actualCamino1]._padre;
                        actualCamino2 = _vertices[actualCamino2]._padre;
                    }
                    (*caminosMin)[0].push_back(actualCamino1);
                    (*caminosMin)[1].push_back(actualCamino2);
                }

            } else {
                //Si no tiene padre (es decir que es -1) significa que soy el vertice de origen.
                if(_vertices[u->_numero]._padre == -1){
                    (*pred)[s][u->_numero] = s;
                } else {
                    //Voy construyendo la salida por si es geodesico
                    (*pred)[s][u->_numero] = _vertices[u->_numero]._padre;
                }
            }
        }
        u->_color = "negro";
    }
    return esGeodesico;
}