Para reeplicar los experimentos para la observación de ver como varía la aparición de ciclos negativos
según como cambia la cantidad de aristas hay que realizar lo siguiente:

en la linea 110 del arichivo grafo-justo.py reemplazamos por la ruta en la que queremos que se generen los archivos
y ejecutamos este archivo.

Luego, en la terminal ejecutamos
for i in <routa>/**/*.in
do
    base_name=$(basename $i)
    ./tp2 3 < $i >> por2.csv
done

Donde routa es la ruta que especificamos en la linea 110. Esto nos generará un archivo como por2.csv, que contiene 
el número de nodos y el resultado de si se detectó un ciclo negativo o no. 
Aclaración: Los archivos cpp que se deben usar son los que estan la carpeta src dento de esta carpeta, 
ya que fueron modificados para obtener un output conveniente.

Con leer.py, en la linea 4 especificamos la ruta donde se encuentra el archivo por2.csv y lo ejecutamos.
Obtenemos el archivo results.csv que nos dice para cada cantidad de nodos cuantos de los experimentos no encontraron
un ciclo negativo
