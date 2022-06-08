El formato del nombre de todos los archivos de entrada va a ser el siguiente:
<nodos> + "n" + <probNeg> + "per" + <media> + "m" + <sd> + "sd" + "-" + <exp> +".in"
Donde 
<nodos> es la cantidad de nodos
<probNeg> es la probabilidad que tiene cada arista de ser negativa
<media> es la media para la generación de los pesos de las aristas
<sd> es la desviación estandar para la generación de los pesos de las aristas
<exp> es el numero de archivo seguido por el tipo de grafo (nc para los justos y c para los completos), 
ya que vamos a tener varios con el mismo nombre y asi diferenciarlos entre si

En la carpeta 1porciento se encuentran los archivos necesarios para replicar el experimento que se 
menciona en el informe de variar la cantidad de aristas para ver la aparición de ciclos negativos.
En la carpeta tiempos se encuentran 4 tests donde se puede testear el funcionamiento de los algoritmos y 
también los scripts usados para generar los casos de test que se usaron para medir los tiempos.
No se envian todos los archivos ya que los mismos son muy pesados y el mail no soporta el mismo.

Se recomienda empezar por la carpeta 1porciento. El formato de los scripts para generar los grafos es muy similar en todos los casos.

DISCLAIMER: Generar y ejecutar los casos de test puede llevar un tiempo extendido.

Tener instalados numpy y tqdm. Para instalarlos ejecutar: 

pip3 install numpy 
pip3 install tqdm 