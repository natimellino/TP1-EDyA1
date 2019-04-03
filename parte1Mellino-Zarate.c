#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>

#define MIN 400

//Declaracion de funciones
char** archivoEntrada( char **array,  char nombreArchivo[], int *cantidad);

int elegir_numero(int min, int max);


int main(){
	srand(time(NULL));

	//int cantNombres;//cantPaises;
	int *cantNombres;
	cantNombres=malloc(sizeof(int));
	int *cantPaises;
	cantPaises=malloc(sizeof(int));

	char archivo1[12]="nombres.txt";
	char **nombres;
    nombres=malloc(sizeof(char*)*MIN);

	char archivo2[11]="paises.txt";
	char **paises;
	paises=malloc(sizeof(char*)*MIN);


	nombres=archivoEntrada(nombres,archivo1, cantNombres);
	paises=archivoEntrada(paises, archivo2, cantPaises);
	//printf("%d\n", *(cantNombres));
	//printf("%d\n", *(cantPaises));

	/*for (int i = 0; i < 4; ++i)
	{
		printf("%s\n", nombres[i]);
	}*/

	int cantPersonas;
	cantPersonas=elegir_numero(2000, 3000); // (revisar cant maxima de personas a elegir)
	int n, p, edad; 
	FILE * fp;
	fp=fopen("personas.txt", "w+");
	for(int i = 0; i < cantPersonas; i++){
		n=elegir_numero(0, *(cantNombres)-1);
		p=elegir_numero(0, *(cantPaises)-1);
		edad=elegir_numero(0, 100);
		fprintf(fp, "%s,%d,%s\n", nombres[n], edad, paises[p]);
	}
	fclose(fp);

	return 1;
}

char** archivoEntrada(char **array,  char nombreArchivo[], int *cantidad){
	int lineas=0;
	char *linea;
	linea = malloc(sizeof(char)*50);
	FILE * fp;
	fp = fopen(nombreArchivo, "r");

	while (!feof(fp)){
    fgets(linea, 50, fp);
    if (lineas >= MIN){
    	array=realloc(array, sizeof(char*)*(lineas+1));
		}
		int i, len;
		len = strlen(linea);
    array[lineas] = malloc(sizeof(char) * len);
		for (i = len; !isalpha(linea[i]); i--);
		linea[i+1] = '\0';
		array[lineas] = malloc(sizeof(char) * len);
	  strcpy(array[lineas],linea);
		lineas++;
	}
	*(cantidad)=lineas;

	fclose(fp);
	return array;
}

// Devuelve un número aleatorio entre min y max (incluyendo a ambos).
int elegir_numero(int min, int max){
	int numero;
	numero = rand() % (max-min+1) + min;
	return numero;
}
