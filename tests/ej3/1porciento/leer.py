#Lee los resultados y los transforma en un csv para despues usarlo en Excel para importar la 
#tabla y graficar
diccionario = {}
route = ""

with open(route + "por2.csv") as f:
    lines = f.readlines()


for i in lines:
    k = int(i[:2])
    k = k - 1
    diccionario.update({k:0})

for i in lines:
    diccionario.update({int(i[:2])-1:int(diccionario[int(i[:2])-1])+int(i[3:-1])})

print(diccionario)


f = open("./results.csv", "w")
for i in diccionario:
    f.write(str(i) + ";" + str(diccionario[i])+"\n")
f.close