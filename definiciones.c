#include <stdio.h>
#include <stdlib.h>
#include "declaraciones.h"
#include <string.h>
#include <assert.h>

int glist_vacia(GList lista) {
  return lista == NULL;
}

GList glist_crear() {
  return NULL;
}

GList glist_agregar_final(GList lista, void* p){
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  assert(nuevoNodo!=NULL);
  nuevoNodo->dato = p;
  if(glist_vacia(lista)){
    nuevoNodo->sig=nuevoNodo->ant= nuevoNodo;
    return nuevoNodo;
  }
  else{
    GNodo *ultimo=lista->ant;

    nuevoNodo->sig=lista;
    lista->ant=nuevoNodo;
    nuevoNodo->ant=ultimo;
    ultimo->sig=nuevoNodo;

    return lista;
  }
}

void glist_destruir(GList lista, Eliminadora e){
  GNodo* nodoAEliminar;
  while(lista->sig != lista){
    nodoAEliminar = lista->sig;
    lista->sig = nodoAEliminar->sig;
    e(nodoAEliminar);
  }
  //borro el primer nodo
  e(lista);
}

void glist_recorrer(GList lista, FuncionRecorre mostrar){

  GList nodo = lista;
  for (; nodo->sig != lista; nodo = nodo->sig)
    mostrar(nodo->dato);

  mostrar(nodo->dato);
}

/*---------------------------------------------------------------*/

void eliminar_persona(GList nodoAEliminar){
  Persona* aux= nodoAEliminar->dato;
  free(aux->nombre);
  free(aux->lugarDeNacimiento);
  free(nodoAEliminar->dato);
  free(nodoAEliminar);
}

// Lee una lista de personas y la guarda en una lista enlazada.

GList lectura_archivo(LeeDato rec_dato){
  FILE * fp;
  fp = fopen("personas.txt", "r");
  assert(fp != NULL);
  GList ListaDePersonas=glist_crear();
  while (!feof(fp)){
  	char *linea = malloc(sizeof(char)*100);
  	assert(linea!=NULL);
  	void* punteroCorrecto=fgets(linea, 100, fp);
  	if(punteroCorrecto!=NULL){
    void* p=rec_dato(linea);
    ListaDePersonas=glist_agregar_final(ListaDePersonas,p);
	}
	free(linea);
  }
  fclose(fp);
  return ListaDePersonas;
}
void* leer_persona(char* linea){
    void* p = malloc(sizeof(Persona));

    ((Persona *)p)->nombre=malloc(sizeof(char)*strlen(linea));
    ((Persona *)p)->lugarDeNacimiento=malloc(sizeof(char)*strlen(linea));

    assert(((Persona *)p)->nombre!= NULL);
    assert(((Persona *)p)->lugarDeNacimiento!= NULL);


    sscanf(linea,"%[^,], %d, %[^\n]", ((Persona *)p)->nombre, &((Persona *)p)->edad, ((Persona *)p)->lugarDeNacimiento);

    ((Persona *)p)->nombre=realloc(((Persona *)p)->nombre,sizeof(char)*(strlen(((Persona *)p)->nombre)+1));
    ((Persona *)p)->lugarDeNacimiento=realloc(((Persona *)p)->lugarDeNacimiento,sizeof(char)*(strlen(((Persona *)p)->lugarDeNacimiento)+1));

    assert(((Persona *)p)->nombre!= NULL);
    assert(((Persona *)p)->lugarDeNacimiento!= NULL);

    return p;
}

// Función para map.

void* aumentar_edad(void* pers){
    ((Persona*)pers)->edad += 10;
    return pers;
}

// Función para map.

void* ocultar_nombre(void* persona){
  for (int i = 0; i < strlen(((Persona*)persona)->nombre); i++){
    ((Persona*)persona)->nombre[i] = 'x';
  }
  return persona;
}

// Funcion para filter
int mayor_de_edad(void *dato){
  return (((Persona *) dato)->edad >= 18);
}

//Funcion para filter
int empieza_con_a(void *dato){
  return (((Persona *) dato)->nombre[0]=='A');
}


void* copiar_nodo(void* p){
    void* nuevap = malloc(sizeof(Persona));

    assert(nuevap!=NULL);

    ((Persona*) nuevap)->nombre = malloc(sizeof(char)*(strlen(((Persona*) p)->nombre)+1));
    assert(((Persona *)nuevap)->nombre!= NULL);

    strcpy(((Persona*) nuevap)->nombre, ((Persona*) p)->nombre);

    ((Persona*) nuevap)->edad = ((Persona*) p)->edad;

    ((Persona*) nuevap)->lugarDeNacimiento = malloc(sizeof(char)*(strlen(((Persona*) p)->lugarDeNacimiento)+1));
    assert(((Persona *)nuevap)->lugarDeNacimiento!= NULL);
    
    strcpy(((Persona*) nuevap)->lugarDeNacimiento, ((Persona*) p)->lugarDeNacimiento);

    return nuevap;
}

GList map(GList lista, Funcion f, Copia c){
  GList nuevaLista = glist_crear();
  GList i = lista;
  for(; i->sig != lista; i = i->sig){
    void* copia = c((i->dato));
    nuevaLista = glist_agregar_final(nuevaLista, f(copia));
  }
  void* copia = c((i->dato));
  nuevaLista = glist_agregar_final(nuevaLista, f(copia));

  return nuevaLista;
}

GList filter(GList lista, Predicado f, Copia c){
  GList listaRetorno=glist_crear();
  GList i=lista;
  for(;i->sig != lista;i=i->sig){
    if(f(i->dato)){
      void *nuevoNodo=c(i->dato);
      listaRetorno=glist_agregar_final(listaRetorno,nuevoNodo);
    }
  }
  if(f(i->dato)){
    void *nuevoNodo=c(i->dato);
    listaRetorno=glist_agregar_final(listaRetorno,nuevoNodo);
  }

  return listaRetorno;
}


void escribir_lista(char* nombreArchivo, GList lista, Escritora escribir_dato){
  FILE* fp;
  fp = fopen(nombreArchivo, "w+");
  GList i = lista;
  for(; i->sig != lista; i = i->sig){
  	escribir_dato(fp,i);
  }
  escribir_dato(fp,i);
  fclose(fp);
}

void escribir_persona(FILE* fp, GList i){

	fprintf(fp, "%s, %d, %s\n", ((Persona*) i->dato)->nombre, ((Persona*) i->dato)->edad, ((Persona*) i->dato)->lugarDeNacimiento);
}

void mapear_lista(GList lista, Funcion f, Copia c, char* nombreArchivo, Escritora escribir_dato){

    GList nuevaLista = map(lista, f, c);

    assert(!glist_vacia(nuevaLista));

    escribir_lista(nombreArchivo, nuevaLista, escribir_dato);

    glist_destruir(nuevaLista,eliminar_persona);
}

void filtrar_lista(GList ListaDePersonas, Predicado f, Copia c, char* nombreArchivo, Escritora escribir_dato){
  GList lista1=filter(ListaDePersonas,f,c);
  assert(!glist_vacia(lista1));
  escribir_lista(nombreArchivo,lista1, escribir_dato);
  glist_destruir(lista1,eliminar_persona);
}

void mostrar_persona(void *dato){
  printf("%s %d %s\n", ((Persona *) dato)->nombre, ((Persona *) dato)->edad, ((Persona *) dato)->lugarDeNacimiento);
}

/*-------------------------------*/
/*void test_mayor_de_edad(){
	void* pers1 = malloc(sizeof(Persona*));
	((Persona*) pers1)->edad = 21;

	void* pers2 = malloc(sizeof(Persona*));
	((Persona*) pers2)->edad = 13;

	assert(mayor_de_edad(pers1) == 1);
	assert(mayor_de_edad(pers2) == 0);

	free(pers1);
	free(pers2);

}

void test_empieza_con_a(){
	void* pers1 = malloc(sizeof(Persona*));
	((Persona*) pers1)->nombre = malloc(sizeof(char)*50);
	((Persona*) pers1)->nombre = "Agustina";

	void* pers2 = malloc(sizeof(Persona*));
	((Persona*) pers2)->nombre = malloc(sizeof(char)*50);
	((Persona*) pers2)->nombre = "Camila";

	assert(empieza_con_a(pers1) == 1);
	assert(empieza_con_a(pers2) == 0);

	free(((Persona*) pers1)->nombre);
	free(((Persona*) pers2)->nombre);
	free(pers1);
	free(pers2);

}*/
