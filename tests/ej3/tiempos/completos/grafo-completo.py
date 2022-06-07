from cmath import sqrt
import numpy as np
import random as random 
from copy import copy
import math
from tqdm import tqdm
import time
import cmath


def setear(matriz,i,j,sign,arr1,arr2,media,sd):
    res = 0
    if(i != j and matriz[i][j] == None):
        num = int(abs(np.random.normal(media,sd)))
        matriz[i][j] = num
        rsign = random.randint(0,100)
        if(rsign<sign):
            matriz[i][j] *= -1
        arr1[i] += 1
        arr2[j] += 1
        res = 1
    return res
        

def generarGrafoConexo2(sign,nombre,n,m,sd,ruta):
    matrix = []
    aristas = 0
    fila = []
    columna = []
    for i in range(0,n):
        lst = []
        fila.append(0)
        columna.append(0)
        for j in range(0,n):
            lst.append(None)
        matrix.append(lst)
    #primera aproximacion a llenar una matriz
    for i in range(0,n):
        for j in range(0,n):
            a = setear(matrix,i,j,sign,fila,columna,m,sd)
            aristas += a

    name = ruta + str(n) + "n" + str(sign) + "per" + str(m) + "m" + str(sd) + "sd" + "-" + nombre +".in"
    #Los guardo en el archivo
    f = open(name, "w")
    f.write(str(n) + " " + str(aristas) + "\n")
    for i in range(0,n):
        for j in range(0,n):
            k = matrix[i][j]
            if(not (k == None)):
                f.write(str(i) + " " + str(j) + " " + str(k) + "\n")
    f.close()
    return name


m = 100
sd = 5

route = ""

#Genear casos de test para aristas entre 100 y 4500 de 200 en 200
for i in tqdm(range(100,4501,200)):
    generarGrafoConexo2(0,str(0) + "c" ,i,m,sd,route)

