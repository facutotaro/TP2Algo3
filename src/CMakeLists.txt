# CMakeList.txt: proyecto de CMake para tp2, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Agregue un origen al ejecutable de este proyecto.
add_executable (tp2 "tp2.cpp" "ej1/ej1.cpp" "ej1/ej1.h" "ej2/Ej2Solver.cpp" "ej2/Ej2Solver.h" "ej1/grafo.cpp" "ej1/grafo.h" "ej2/UnionFind.cpp" "ej2/UnionFind.h" "ej3/johnson.cpp" "ej3/johnson.h" "ej3/bellmanFord.cpp" "ej3/bellmanFord.h" "ej3/dijkstra.cpp" "ej3/dijkstra.h" "ej3/digrafo.cpp" "ej3/digrafo.h" "ej4/grafoIntervalo.cpp" "ej4/grafoIntervalo.h")

# TODO: Agregue pruebas y destinos de instalación si es necesario.
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")