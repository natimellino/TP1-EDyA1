#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>

#define MIN_PERSONAS 2000
#define MAX_PERSONAS 3000

//Declaracion de funciones
char ** archivoEntrada( char **array,  char *nombreArchivo, int *cant);
void archivoSalida(char **nombres, char **paises, int *cantNombres, int *cantPaises);
int elegir_numero(int min, int max);

int main(){
	srand(time(NULL));
	int *cantNombres=malloc(sizeof(int)), *cantPaises=malloc(sizeof(int));
	char **nombres=NULL, **paises=NULL;
	//nombres= malloc(sizeof(char*)*3000);
	//paises= malloc(sizeof(char*)*3000);
	nombres=archivoEntrada(nombres,"nombres.txt",cantNombres);
	paises=archivoEntrada(paises, "paises.txt",cantPaises);
	for (int i = 0; i < (*cantNombres); ++i)
	{
		printf("entra for\n");
		printf("%s\n", nombres[i] );
	}

	archivoSalida(nombres, paises, cantNombres, cantPaises);

	return 1;
}

char** archivoEntrada(char **array,  char* nombreArchivo, int *cant){
	int lineas=0;
	char linea[50];
	FILE * fp;
	fp = fopen(nombreArchivo, "r");

	while (!feof(fp)){
    	fgets(linea, 50, fp);
    	array=realloc(array, sizeof(char*)*(lineas+1)); //reservamos memoria de esta manera para que el largo del archivo sea irrelevante
		int i,len = strlen(linea);
		for (i = len; !isalpha(linea[i]) ; i--);
		linea[i+1] = '\0';
		array[lineas] = malloc(sizeof(char) * (len+1));
		strcpy(array[lineas],linea);
		lineas++;
	}
	

	fclose(fp);
	(*cant)=lineas;
	return array;
}

void archivoSalida(char **nombres, char **paises, int *cantNombres, int *cantPaises){
	int cantPersonas, n, p, edad;
	cantPersonas=elegir_numero(MIN_PERSONAS, MAX_PERSONAS);  
	FILE * fp;
	fp=fopen("personas.txt", "w+");
	for(int i = 0; i < cantPersonas; i++){
		n=elegir_numero(0, *(cantNombres)-1);
		p=elegir_numero(0, *(cantPaises)-1);
		edad=elegir_numero(0, 100);
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