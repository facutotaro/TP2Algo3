# CMakeList.txt: proyecto de CMake para tp2, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Agregue un origen al ejecutable de este proyecto.
add_executable (tp2 "tp2.cpp" "johnson.cpp" "johnson.h" "bellmanFord.cpp" "bellmanFord.h" "dijkstra.cpp" "dijkstra.h" "digrafo.cpp" "digrafo.h" "grafoIntervalo.cpp" "grafoIntervalo.h")

# TODO: Agregue pruebas y destinos de instalación si es necesario.
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")