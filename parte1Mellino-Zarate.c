#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include <assert.h>

#define MIN_PERSONAS 2000
#define MAX_PERSONAS 3000
#define MIN_PAISES 400


//Declaracion de funciones

char ** archivoEntrada( char **array,  char *nombreArchivo, int *cant, int size);
void archivoSalida(char **nombres, char **paises, int *cantNombres, int *cantPaises);
int elegir_numero(int min, int max);
int es_simbolo(char c);
void destruir_array(char **array, int *cantidadElementos);
void test_es_simbolo();

int main(){
	setlocale(LC_CTYPE, "spanish"); 

	srand(time(NULL));

	int *cantNombres=malloc(sizeof(int)), *cantPaises=malloc(sizeof(int)), minN=2000,minP=400;
	char **nombres=NULL, **paises=NULL;

	assert(cantNombres != NULL);
	assert(cantPaises != NULL);

	nombres= malloc(sizeof(char*)*MIN_PERSONAS);
	paises= malloc(sizeof(char*)*MIN_PAISES);

	assert(nombres != NULL);
	assert(paises != NULL);

	nombres=archivoEntrada(nombres,"nombres.txt",cantNombres,minN);
	paises=archivoEntrada(paises, "paises.txt",cantPaises,minP);

	archivoSalida(nombres, paises, cantNombres, cantPaises);

	destruir_array(nombres, cantNombres);
	destruir_array(paises, cantPaises);
	free(cantNombres);
	free(cantPaises);


	test_es_simbolo();

	return 1;
}

// Recibe un char y lo compara con los valores ASCII para verificar que no sea
// un símbolo (*,/,#, etc...), si se trata de un símbolo la función retorna
// 1 y si no, retorna 0.

int es_simbolo(char c){
	return ((c >= 33 && c<=64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126));
}

// Toma como parámetros un array bidimensional de char que tiene un tamaño inicial 'size', 
// el nombre de un archivo y un puntero a un int que representa la cantidad 
// de palabras del archivo. La función abre el archivo 'nombreArchivo', lee las líneas
// del mismo guardandolas en el array, en caso de que las lineas leidas superen el size 
// que es pasado como parámetro, se pide más memoria para el array. Una vez leidas las 
// lineas del archivo, guardamos la cantidad de lineas en el puntero a int 'cant' y
// retornamos el puntero al array de char.

char** archivoEntrada(char **array,  char* nombreArchivo, int *cant, int size){
	int lineas=0;
	char linea[50];
	FILE * fp;
	fp = fopen(nombreArchivo, "r");

	assert(fp != NULL);
	
	while (fgets(linea, 50, fp) != NULL && !feof(fp)){
	
		if(lineas>=size){
			array=realloc(array, sizeof(char*)*(lineas+(size/2)));
			assert(array!=NULL);
			size+=size/2;		
		}
		int i, len;
		len = strlen(linea);
		for (i = 0; i < len && linea[i]!='\r' && linea[i]!='\n' && !es_simbolo(linea[i]); i++);
		linea[i] = '\0';
		array[lineas] = malloc(sizeof(char) * (i+1));
	  	strcpy(array[lineas],linea);
		lineas++;
    }
	*(cant)=lineas;
	fclose(fp);
	return array;
}

// Recibe la lista de nombres y países junto con su tamaño, elige una
// posición aleatoria de cada lista junto con un número aleatorio que
// representa una edad, y copia los elementos de las posiciones elegidas
// aleatoriamente en un archivo en formato: 'nombre, edad, país'.

void archivoSalida(char **nombres, char **paises, int *cantNombres, int *cantPaises){
	int cantPersonas, n, p, edad;
	cantPersonas=elegir_numero(MIN_PERSONAS, MAX_PERSONAS);
	FILE * fp;
	fp=fopen("personas.txt", "w+");
	for(int i = 0; i < cantPersonas; i++){
		n=elegir_numero(0, *(cantNombres)-1);
		p=elegir_numero(0, *(cantPaises)-1);
		edad=elegir_numero(1, 100);
		fprintf(fp, "%s, %d, %s\n", nombres[n], edad, paises[p]);
	}
	fclose(fp);

	return;
}
// Devuelve un número aleatorio entre min y max (incluyendo a ambos).

int elegir_numero(int min, int max){
	int numero;
	numero = rand() % (max-min+1) + min;
	return numero;
}
/* Toma un array y su cantidad de elementos y lo destruye*/

void destruir_array(char **array, int* cantidadElementos){
	for (int i = 0; i < (*cantidadElementos); ++i)
	{
		free(array[i]);
	}
}
void test_es_simbolo(){
	char c1 = '*';
	char c2 = 'a';
	assert(es_simbolo(c1));
	assert(es_simbolo(c2) == 0);
}
