cmake_minimum_required(VERSION 3.22)
project(unaVezMas)

set(CMAKE_CXX_STANDARD 14)

# Leemos todos los archivos fuentes en ./src
file(GLOB SOURCE_FILES *.cpp *.h *.hpp)

add_executable(unaVezMas main.cpp
        ej1.cpp

        grafo.cpp

        )
