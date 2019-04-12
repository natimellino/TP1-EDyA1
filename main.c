#include <stdio.h>
#include <stdlib.h>
#include "declaraciones.h"

int main(){
  GList ListaDePersonas=lectura_archivo(leer_persona);

  filtrar_lista(ListaDePersonas, mayor_de_edad,copiar_nodo,"mayores_de_edad.txt", escribir_persona);
  filtrar_lista(ListaDePersonas, empieza_con_a,copiar_nodo,"nombrescona.txt", escribir_persona);

  mapear_lista(ListaDePersonas, ocultar_nombre, copiar_nodo, "ocultanombre.txt", escribir_persona);
  mapear_lista(ListaDePersonas, aumentar_edad, copiar_nodo, "aumentaedad.txt", escribir_persona);

  glist_destruir(ListaDePersonas,eliminar_persona);

  return 1;
}
