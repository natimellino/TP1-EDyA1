#include <stdlib.h>

typedef struct {
	char *nombre, *lugarDeNacimiento;
	int edad;
}Persona;

//typedef Persona *PersonaList

typedef struct _GNodo{
  Persona* dato;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

//typedef int (*Predicado) (void* dato);

typedef void* (*Funcion) (void* dato);

typedef void* (*Copia) (void*);

GList map(GList lista, Funcion f, Copia c);

GList filter(GList lista, Funcion f, Copia c);

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al final de la lista.
 */
//glist glist_agregar_final(glist lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, Persona* dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
//void glist_recorrer(GList lista, FuncionVisitante visit);

GList lectura_archivo();