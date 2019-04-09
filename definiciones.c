#include <stdio.h>
#include <stdlib.h>
#include "declaraciones.h"
#include <string.h>

int glist_vacia(GList lista) {
  return lista == NULL;
}

GList glist_crear() {
  return NULL;
}

/*GList map(GList lista, Funcion f, Copia c){

}*/
GList glist_agregar_inicio(GList lista, Persona* p) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = p;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

char* reconocer_cadena(int *i, char* linea){
  char* cadena=malloc(sizeof(char)*50);
  for(; linea[*i]!= ','&& linea[*i]!= '\0' ; (*i)++){
    char *ptr=malloc(sizeof(char));
    (*ptr)=linea[(*i)];
    strcat(cadena, ptr);
  }
  return cadena;
}


GList lectura_archivo(){
  FILE * fp;
	fp = fopen("personas.txt", "r");
  GList ListaDePersonas=glist_crear();
  char *linea = malloc(sizeof(char)*100);
  while (!feof(fp)){
    int *i=malloc(sizeof(int));
    *(i)=0;
    //printf("valor de i: %d\n", *i);
    Persona* p = malloc(sizeof(Persona*));
    fgets(linea, 100, fp);
    //printf("linea completa: %s\n", linea);
    p->nombre = reconocer_cadena(i, linea);
    //printf("nombre de la persona %s\n",p->nombre );
    //printf("valor de i luego 1 llamada: %d\n", *i);
    *(i)+=2;
    //printf("valor de i+2: %d\n", *i);
    //printf("linea completa: %s\n", linea);
    p->edad = atoi(reconocer_cadena(i, linea));
    //printf("valor de i luego 2 llamadas: %d\n", *i);
    //printf("edad de la persona %d\n",p->edad );
    *(i)+=2;
    //printf("valor de i+2: %d\n", *i);
    //printf("linea completa: %s\n", linea);
    p->lugarDeNacimiento = reconocer_cadena(i, linea);
    //printf("linea completa: %s\n", linea);
    //printf("valor de i luego 3 llamadas: %d\n", *i);
    //printf("pais de la persona %s\n",p->lugarDeNacimiento );
    //printf("%d\n", strlen(p->lugarDeNacimiento));

    ListaDePersonas = glist_agregar_inicio(ListaDePersonas,p);
  }

  return ListaDePersonas;
}
