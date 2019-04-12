Trabajo práctico 1: observaciones sobre el código.

1) Para la primer parte del trabajo práctico: selección aleatoria de personas.

Compilación:

El programa que realiza la selección aleatoria de personas es 'parte1Mellino-Zarate.c'.
Para compilar basta con poner en la consola: gcc -std=c99 -Wall -pedantic parte1Mellino-Zarate.c

Estructura de datos elegida:

Para almacenar los datos de las personas y los países se hace uso de dos matrices bidimensionales,
en una guardamos los nombres y en la otra los países. Estos son leídos desde los archivos 
'nombres.txt' y 'paises.txt', que fueron dados por la cátedra.

Caracteres especiales: 

Para evitar que haya caracteres especiales tales como '*', '@', etc. 
creamos una función 'es_simbolo' que toma un char y compara su valor ASCII con los valores 
ASCII que poseen los caracteres especiales. 
Observación: para el programa asumimos que dichos caracteres especiales, en caso de encontrarse,
están al final de la palabra, ya que al hacer la lectura del archivo leemos una línea y luego
al encontrarse un caracter especial se coloca un '\0' en dicha posición, dando por terminada la palabra.

Idea general del programa: 

Mediante la función 'archivo_entrada', leemos los países y las personas, verificando allí
mismo que las palabras con contengan caracteres especiales, los guardamos en sus respectivas matrices y las retornamos.
Una vez que tenemos ambas listas de palabras, llamamos a la función archivo_salida que toma a las dos listas como
parámetro y primeramente elige una cantidad aleatoria de personas a generar; luego, elige aleatoriamente un índice de cada lista y una edad entre 1 y 100 (haciendo uso de una funcion que realiza elige un número aleatorio entre cierto rango). 
Una vez que tenemos los 3 datos, los escribimos en un archivo en forma 'nombre, edad, país'. Este proceso se repite 
de acuerdo a la cantidad de personas que fue elegida. 

2) Para la segunda parte del programa: funciones map y filter.

Compilación del programa:

Para compilar esta parte del trabajo debemos hacerlo mediante los archivos 'definiciones.c' y 'main.c',
debiendo poner en consola el siguiente comando: gcc -std=c99 -Wall -pedantic main.c definiciones.c
tanto en el archivo 'main.c' como en 'definiciones.c' está incluida la cabecera 'declaraciones.h'
que es donde están declaradas todas la funciones que usamos a lo largo del programa.

Estructura elegida para almacenar los datos:

La segunda parte del trabajo recibe como entrada la lista de personas generada por la parte anterior. Para guardar
estos datos utilizamos una lista circular doblemente enlazada, donde mediante el uso de una estructura 'Persona', guardamos
el nombre, edad y país de cada persona.
