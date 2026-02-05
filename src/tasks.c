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

  FILE *f_write = fopen("tasks.txt", "a");
  if (f_write != NULL) {
    fprintf(f_write, "%d|%s|%d\n", nueva.id, nueva.description, nueva.status);
    fclose(f_write);
    printf("Tarea #%d añadida.\n", nueva.id);
  }
}

void list_tasks() {

  char buffer[256];

  FILE *f_read = fopen("tasks.txt", "r");

  if (f_read == NULL) {
    printf("Aún no tienes tareas guardadas. Usa 'add' para crear una.\n");
    return;
  }

  printf("\n[ FOSSIL TASK LIST ]\n");
  printf("---------------------------------------------------------\n");

  while (fgets(buffer, sizeof(buffer), f_read)) {

    Task temp = {0};

    sscanf(buffer, "%d|%[^|]|%d", &temp.id, temp.description, &temp.status);

    printf("ID %d | %-30s | status [%s]\n", temp.id, temp.description,
           temp.status == 0 ? "PENDING" : "COMPLETE");
  }
  printf("---------------------------------------------------------\n");

  fclose(f_read);
}
