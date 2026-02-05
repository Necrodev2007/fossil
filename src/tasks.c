#include "tasks.h"
#include <stdio.h>
#include <string.h>

// Adds a new task to the storage file and assigns a unique ID
void add_task(char *desc) {

  int count = 0;
  char buffer[256];
  FILE *f_read = fopen("tasks.txt", "r");

  if (f_read != NULL) {
    while (fgets(buffer, sizeof(buffer), f_read)) {
      count++;
    }
    fclose(f_read);
  }

  Task new;
  new.id = count + 1;
  new.status = 0;
  strncpy(new.description, desc, 99);
  new.description[99] = '\0';

  FILE *f_write = fopen("tasks.txt", "a");
  if (f_write != NULL) {
    fprintf(f_write, "%d|%s|%d\n", new.id, new.description, new.status);
    fclose(f_write);
    printf("Task [%d] added successfully!\n", new.id);
  }
}

// Reads all tasks from the file and displays them in a formatted table
void list_tasks() {

  char buffer[256];

  FILE *f_read = fopen("tasks.txt", "r");

  if (f_read == NULL) {
    printf("No tasks found. Use 'add' to create a new one.\n");
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
