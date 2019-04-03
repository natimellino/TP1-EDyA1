#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN 2

typedef struct {
	char *nombre, *lugarDeNacimiento;
	int edad;
}Persona;

//Declaracion de funciones
int archivoEntrada( char **array,  char nombreArchivo[]);

int main(){
	int cantNombres;//cantPaises;
	char archivo1[12]="a.txt";
	char **nombres;
    nombres=malloc(sizeof(char*)*MIN);
	//char archivo2[11]="paises.txt";
	cantNombres=archivoEntrada(nombres,archivo1);
	printf("%d\n", cantNombres);
	/*for (int i = 0; i < 9; ++i)
	{
		printf("%s\n", nombres[i]);
	}*/
	return 1;
}

int archivoEntrada( char **array,  char nombreArchivo[]){
	int lineas=0;
	char *linea;
	linea = malloc(sizeof(char)*50);
	FILE * fp;
	fp = fopen(nombreArchivo, "r");
	
	while (!feof(fp)){
    	fscanf(fp, "%s", linea);
    	if(lineas>=MIN)
    		array=realloc(array, sizeof(char*)*(lineas+1));

    	array[lineas] = malloc(sizeof(char)*strlen(linea));
		strcpy(array[lineas],linea);
		lineas++;
	}

	fclose(fp);

	for (int i = 0; i < 9; ++i)
	{
		printf("%s\n", array[i]);
	}

	return lineas;
}