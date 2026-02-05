#ifndef TASKS_H
#define TASKS_H

typedef struct {         // estructura de una tarea
  int id;                // para identificar cada tarea
  char description[100]; // el nombre o descripcion de la tarea
  int status;            // 0 no completada, 1 completada
} Task;

void list_tasks();
void add_task(char *desc);

#endif
