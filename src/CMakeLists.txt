# CMakeList.txt: proyecto de CMake para tp2, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Agregue un origen al ejecutable de este proyecto.
add_executable (tp2 "tp2.cpp" "ej1.cpp" "ej1.h" "Ej2Solver.cpp" "Ej2Solver.h" "grafo.cpp" "grafo.h" "UnionFind.cpp" "UnionFind.h" "johnson.cpp" "johnson.h" "bellmanFord.cpp" "bellmanFord.h" "dijkstra.cpp" "dijkstra.h" "digrafo.cpp" "digrafo.h" "grafoIntervalo.cpp" "grafoIntervalo.h")

# TODO: Agregue pruebas y destinos de instalación si es necesario.
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")