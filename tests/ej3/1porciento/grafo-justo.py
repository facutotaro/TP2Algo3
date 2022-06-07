from cmath import sqrt
import numpy as np
import random as random 
from copy import copy
import math
from tqdm import tqdm
import time
import cmath
import os







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
        

#Crea un grafo conexo con una cantidad de aristas similar a la justa
#Parametros:
#sign: probabilidad de que una arista sea negativa
#nombre: numero de experimento
#n: cantidad de nodos
#m: media para el peso de las aristas
#sd: distribución estandar para el peso de las aristas
#carpeta: por una cuestion de practicidad, ponemos las de la misma cantidad de nodos en una misma carpeta
#rutadeldirectorio: especificamos en que directorio queremos que se nos generen los archivos
def generarGrafoConexo2(sign,nombre,n,m,sd,carpeta,rutadeldirectorio):
    matrix = []
    aristas = 0
    fila = []
    columna = []
    conex = (n-2)*(n-1)/2
    for i in range(0,n):
        lst = []
        fila.append(0)
        columna.append(0)
        for j in range(0,n):
            lst.append(None)
        matrix.append(lst)
    #primera aproximacion a llenar una matriz
    for i in range(0,n):
        prob = random.randint(0,n-1) #probabilidad de menter un numero en una fila
        for j in range(0,n):
            put = random.randint(0,n-1) #probabilidad de que ese numero sea metido
            if(put <= prob):
              a = setear(matrix,i,j,sign,fila,columna,m,sd)
              aristas += a

    
    #para que sea conexo todo vertice tiene que tener una entrada o una salida
    for i in range(0,n):
        if(fila[i]==0 and columna[i] == 0): 
            #si no tengo ninguna, pongo un vertice en una fila o columna aleatoria
            #para tratar de ser lo mas arbitrario posible
            filOcol = random.randint(0,1)
            k = random.randint(0,n-1)
            if(filOcol == 0):
                a = setear(matrix,i,k,sign,fila,columna,m,sd)
                aristas += a
            else:
                a = setear(matrix,k,i,sign,fila,columna,m,sd)
                aristas += a

    #si tengo que completar con aristas
    #en grafos chicos quizas agrego varias aristas demas
    #no es muy aleatorio ya que verifica si puede agregar en orden, pero si fuese
    #totalmente aleatorio en tests grandes tardaria bastante ya que se encontraria
    #con muchos lugares ocupados
    while(aristas < conex):
        for col in range(0,n):
            fil = random.randint(0,n-1)
            prob = random.randint(0,n-1)
            put = random.randint(0,n-1)
            if(put > prob):
                a = setear(matrix,fil,col,sign,fila,columna,m,sd)
                aristas += a

    name = str(n) + "n" + str(sign) + "per" + str(m) + "m" + str(sd) + "sd" + "-" + nombre +".in"
    #Los guardo en el archivo
    f = open(ruta + carpeta + "/" + name, "w")
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

#Aclarar ruta esta es la mia
ruta = ""


for i in range(100,2001,50):
    path = ruta + str(i)
    isExist = os.path.exists(path)
    if not isExist:
        os.makedirs(path)
    
#Generamos mil casos
for k in range(0,1000):
    #Para grafos con aristas entre 100 y 1150
    for i in tqdm(range(100,1551,50)):
        a = 1
        b = -3
        c = 2 - 2*i
        d = (b**2) - (4*a*c) 
        sol1 = int(((-b-cmath.sqrt(d))/(2*a)).real)  
        sol2 = int(((-b+cmath.sqrt(d))/(2*a)).real)
        nodes = max(sol1,sol2) + 1
        nombre = generarGrafoConexo2(1,str(k) + "nc" ,nodes,m,sd,str(i),ruta)
            



  

