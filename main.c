#include<stdio.h>
#include <stdlib.h>
#include "declaraciones.h"

int main(){
  GList ListaDePersonas=lectura_archivo();
  for (size_t i = 0; i< 5; i++) {
    printf("%s %d %s\n", ListaDePersonas->dato->nombre, ListaDePersonas->dato->edad,ListaDePersonas->dato->lugarDeNacimiento);
  }
  return 1;
}