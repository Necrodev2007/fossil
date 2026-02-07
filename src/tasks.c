#include "tasks.h"
#include <stdio.h>
#include <string.h>

// Adds a new task to the storage file and assigns a unique ID
void add_task(char *desc) {

  int count = 0;
  char buffer[256];
  FILE *f_read = fopen(DB_PATH, "r");

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

  FILE *f_write = fopen(DB_PATH, "a");
  if (f_write != NULL) {
    fprintf(f_write, "%d|%s|%d\n", new.id, new.description, new.status);
    fclose(f_write);
    printf("Task [%d] added successfully!\n", new.id);
  }
}

// Reads all tasks from the file and displays them in a formatted table
void list_tasks() {
  int count = 0;
  char buffer[256];

  FILE *f_read = fopen(DB_PATH, "r");

  if (f_read == NULL) {

    printf("\n[ FOSSIL TASK LIST ]\n");
    printf("---------------------------------------------------------\n");
    printf("   Notice: No database found yet.\n");
    printf("   Run 'add' to create your first task and start your list!\n");
    printf("---------------------------------------------------------\n");
    return;
  }

  printf("\n[ FOSSIL TASK LIST ]\n");
  printf("---------------------------------------------------------------------"
         "--\n");

  while (fgets(buffer, sizeof(buffer), f_read)) {

    Task temp = {0};

    if (sscanf(buffer, "%d|%[^|]|%d", &temp.id, temp.description,
               &temp.status) == 3) {
      printf(" ID %-4d | %-40.40s | status [%-8s]\n", temp.id, temp.description,
             temp.status == 0 ? "PENDING" : "COMPLETE");
      count++;
    }
  }

  if (count == 0) {
    printf("        ( Your task list is currently empty ) \n");
  }

  printf("---------------------------------------------------------------------"
         "--\n");

  fclose(f_read);
}

void mark_done(int target_id) {

  FILE *f_src = fopen(DB_PATH, "r");
  FILE *f_tmp = fopen(DB_TEMP_PATH, "w");

  if (f_src == NULL || f_tmp == NULL) {
    perror("Error opening database");
    if (f_src)
      fclose(f_src);
    if (f_tmp)
      fclose(f_tmp);
    return;
  }

  Task task;
  int task_found = 0;

  while (fscanf(f_src, "%d|%99[^|]|%d\n", &task.id, task.description,
                &task.status) != EOF) {

    if (task.id == target_id) {

      task.status = 1;
      task_found = 1;
    }

    fprintf(f_tmp, "%d|%s|%d\n", task.id, task.description, task.status);
  }

  fclose(f_src);
  fclose(f_tmp);

  if (task_found) {
    remove(DB_PATH);
    rename(DB_TEMP_PATH, DB_PATH);
    printf("Success: Task %d marked as completed.\n", target_id);
  } else {
    remove(DB_TEMP_PATH);
    printf("Error: Task with ID %d not found.\n", target_id);
  }
}

void delete_task(int target_id) {

  FILE *f_src = fopen(DB_PATH, "r");
  FILE *f_tmp = fopen(DB_TEMP_PATH, "w");

  if (f_src == NULL || f_tmp == NULL) {
    perror("Error opening database");
    if (f_src)
      fclose(f_src);
    if (f_tmp)
      fclose(f_tmp);
    return;
  }

  Task task;
  int task_found = 0;
  int new_id = 1;

  while (fscanf(f_src, "%d|%99[^|]|%d\n", &task.id, task.description,
                &task.status) != EOF) {

    if (task.id != target_id) {

      fprintf(f_tmp, "%d|%s|%d\n", new_id, task.description, task.status);

      new_id++;

    } else {
      task_found = 1;
    }
  }

  fclose(f_src);
  fclose(f_tmp);

  if (task_found) {
    if (remove(DB_PATH) != 0) {
      perror("Error: Could not remove original file");
      remove(DB_TEMP_PATH);
      return;
    }

    if (rename(DB_TEMP_PATH, DB_PATH) != 0) {
      perror("Error: Could not rename temporary file");
      return;
    }

    printf("Success: Task %d deleted.\n", target_id);
  } else {
    remove(DB_TEMP_PATH);
    printf("Error: Task with ID %d not found.\n", target_id);
  }
}

void clear_tasks() {
  FILE *f_clear = fopen(DB_PATH, "w");

  if (f_clear == NULL) {
    perror("Error: Could not clear the task list");
    return;
  }

  fclose(f_clear);
  printf("Success: All tasks have been cleared.\n");
}

void fossil_help(char *argv0) {

  printf("\n[ FOSSIL - Task Manager Help ]\n");
  printf("------------------------------------------------------------\n");
  printf("Usage: %s <command> [arguments]\n\n", argv0);
  printf("Available Commands:\n");
  printf("  %-20s %s\n", "add <description>", "Add a new task to the list");
  printf("  %-20s %s\n", "list", "Show all your tasks");
  printf("  %-20s %s\n", "done <id>", "Mark a task as completed");
  printf("  %-20s %s\n", "delete <id>", "Remove a task (aliases: del, rm)");
  printf("  %-20s %s\n", "clear", "Delete all tasks from the list");
  printf("  %-20s %s\n", "help", "Display this help message");

  printf("------------------------------------------------------------\n");
}

void show_stats() {
  FILE *f = fopen(DB_PATH, "r");
  if (!f) {
    printf("Database not found. Add some tasks first!\n");
    return;
  }

  Task task;
  int total = 0, completed = 0, pending = 0;
  char buffer[256];

  while (fgets(buffer, sizeof(buffer), f)) {
    if (sscanf(buffer, "%d|%99[^|]|%d", &task.id, task.description,
               &task.status) == 3) {
      total++;
      if (task.status == 1)
        completed++;
      else
        pending++;
    }
  }
  fclose(f);

  if (total == 0) {
    printf("The task list is currently empty. Nothing to report.\n");
    return;
  }

  float progress = ((float)completed / (float)total) * 100.0f;

  printf("\n--- FOSSIL STATS ---\n");
  printf("Tasks: %d | Done: %d | Pending: %d\n", total, completed, pending);
  printf("Overall Progress: %.1f%%\n", progress);
}
