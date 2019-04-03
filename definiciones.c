#include <stdio.h>
#include <stdlib.h>
#include "declaraciones.h"

int glist_vacia(GList lista) {
  return lista == NULL;
}

GList glist_crear() {
  return NULL;
}

/*GList map(GList lista, Funcion f, Copia c){

}*/
GList glist_agregar_inicio(GList lista, Persona p) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = p;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

GList lectura_archivo(){
  FILE * fp;
	fp = fopen("personas.txt", "r");
  GList ListaDePersonas=glist_crear();
  while (!feof(fp)){
    Persona p=malloc(sizeof(Persona));
    fscanf(fp,"%s,%d,%s",p.nombre,p.edad,p.lugarDeNacimiento);
    ListaDePersonas=glist_agregar_inicio(ListaDePersonas,p);
  }

  return ListaDePersonas;
}
