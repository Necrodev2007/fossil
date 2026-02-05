#include "../include/tasks.h"
#include <stdio.h>
#include <string.h>

void add_task(char *desc) {

  int contador = 0;
  char buffer[256];
  FILE *f_leer = fopen("tasks.txt", "r");

  if (f_leer != NULL) {
    while (fgets(buffer, sizeof(buffer), f_leer)) {
      contador++;
    }
    fclose(f_leer);
  }

  // Preparar la estructura
  Task nueva;
  nueva.id = contador + 1;
  nueva.status = 0;
  strncpy(nueva.description, desc, 99);
  nueva.description[99] = '\0';

  FILE *f_escribir = fopen("tasks.txt", "a");
  if (f_escribir != NULL) {
    fprintf(f_escribir, "%d|%s|%d\n", nueva.id, nueva.description,
            nueva.status);
    fclose(f_escribir);
    printf("Tarea #%d añadida.\n", nueva.id);
  }
}
