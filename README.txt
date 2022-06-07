Instrucciones de compilacion y ejecucion en Linux:
1) Ubicarse en el directorio src
2) Crear un directorio donde se quieran generar el ejecutable
En linea de comando
3) En ese directorio ejecutar el comando cmake ..
4) Ejecutar el comando make
5) Ejecutar el ./tp2 <numero de ejercio> < <nombre del test con su ruta> para correr los ejercicios y el archivo por std Instrucciones

Ejemplo de comandos:
cd src
mkdir build
cd build 
cmake ..
make
./tp2 1 < ../../tests/ej1/pentatopeG.txt

En la carpeta src se encuentra el codigo
En la carpeta tests se encuentran algunos tests y instructivos de como replicar el experimento.