#include <stdlib.h>

// Estructura de la persona
typedef struct {
	char *nombre, *lugarDeNacimiento;
	int edad;
}Persona;


//Estructura elegida para la tarea presentada: lista circular doblemente enlazada
typedef struct _GNodo{
  void* dato;
  struct _GNodo *ant;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

typedef int (*Predicado) (void* dato);

typedef void* (*Funcion) (void* dato);

typedef void (*FuncionRecorre) (void* dato);

typedef void* (*Copia) (void*);

typedef void (*Eliminadora) (GList);

typedef void* (*LeeDato) (char* linea);

typedef void (*Escritora) (FILE* fp, GList i);

/*----------------Funciones vinculadas a las listas--------------------*/

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, Eliminadora e);

void eliminar_persona(GList nodoAEliminar);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al final de la lista.
 */
GList glist_agregar_final(GList lista, void* p);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void* dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionRecorre mostrar);

/*-------------------Otras funciones-------------------------*/

void* leer_persona(char* linea);

// Muestra los datos de una Persona por pantalla.

void mostrar_persona(void *dato);

// Lee una lista de personas y guarda los datos en una lista circular doblemente enlazada.

GList lectura_archivo();

// Dado un nombre de archivo, una lista y una funcion especifica para escribir un tipo de dato en un archivo,
// crea un archivo con 
// el nombre recibido y copia la lista allí.

void escribir_lista(char *nombreArchivo, GList lista, Escritora escribir_dato);

void escribir_persona(FILE* fp, GList i);

// Dado un dato, devuelve una copia del mismo.

void* copiar_nodo(void *dato);

/* Recibe una lista, una función f y una función c.
 Crea una copia de la lista dada haciendo uso de la
 funcion Copia c, y luego, con esa nueva lista creada,
 toma cada elemento y le aplica la función f; la nueva
 lista es retornada.*/

GList map(GList lista, Funcion f, Copia c);

// Recibe una lista, un Predicado f y una función Copia c.
// Crea una nueva lista y agrega a ella sólo los elementos
// para los que el predicado f retorne 1.

GList filter(GList lista, Predicado f, Copia c);

// Toma una lista, le aplica la función filter y vuelca la nueva
// lista en un archivo.

void filtrar_lista(GList ListaDePersonas, Predicado f, Copia c, char* nombreArchivo, Escritora escribir_dato);

// Toma una lista, le aplica la función map y vuelca la nueva
// lista en un archivo.

void mapear_lista(GList lista, Funcion f, Copia c, char* nombreArchivo, Escritora escribir_dato);

/*
Recibe una persona y devuelve 1 si la persona es mayor de 18 y 0 en caso contrario.
*/
int mayor_de_edad(void *dato);

// Determina si el nombre de una persona empieza con A.

int empieza_con_a(void *dato);

// Aumenta la edad de una persona en 10 años.

void* aumentar_edad(void* p);

// Oculta el nombre de una Persona poniendo 'x' en las letras de su nombre.

void* ocultar_nombre(void* persona);

/*----------------------testing----------------*/
