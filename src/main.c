#include "../include/tasks.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  if (argc < 2) {

    printf("\n Este programa requiere argumentos. Use <help> para ver los "
           "comandos disponibles\n");

    return 1;
  }

  // si se quiere crear una tarea

  if (strcmp(argv[1], "add") == 0) {
    // Validar que no falte el argumento
    if (argc < 3) {
      printf("Error: Tienes que poner una descripción.\n");
      printf("Uso: %s add \"nombre de la tarea\"\n", argv[0]);
      return 1;
    }

    // Llamar a la función si todo esta correcto
    add_task(argv[2]);
  }

  else if (strcmp(argv[1], "list") == 0) {

    if (argc > 2) {

      printf("Error: tienes demasiados arguementos\n");
      printf("Uso de list: <fossil list>\n");

      return 1;
    }

    list_tasks();
  }

  return 0;
}
