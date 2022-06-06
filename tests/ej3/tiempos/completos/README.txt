En la linea 59 de grafo-justo.py especificar la ruta del archivo donde se quieren generar los archivos de prueba.
Correr el script grafo-justo.py

Nosotros para obtener los resultados utilizamos el siguente comando en la consola
echo "tiempos" > <archivoDeResultado>.output
echo "" >> <archivoDeResultado>.output
for i in <ruta donde estan los archivos>/*.in
do
    base_name=$(basename $i)
    echo ${basename} >> <archivoDeResultado>.output
    /usr/bin/time -f "Tardó: %e" -o <archivoDeResultado>.output -a timeout 3600 ./tp2 3 < $i >> <archivoDeResultado>.output
    echo "" >> <archivoDeResultado>.output
done

Y obtuvimos tanto los resultados como los tiempos en un mismo archivo