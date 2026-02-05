#include "tasks.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  if (argc < 2) {

    printf("\nError: No command provided.\n");
    printf("Type '%s help' to see available commands.\n", argv[0]);

    return 1;
  }

  if (strcmp(argv[1], "help") == 0) {
    printf("\n[ FOSSIL - Task Manager Help ]\n");
    printf("--------------------------------------------------\n");
    printf("Usage: %s <command> [arguments]\n\n", argv[0]);
    printf("Available Commands:\n");
    printf("  add \"description\"   Add a new task to the list\n");
    printf("  list                Show all your tasks\n");
    printf("  help                Display this help message\n");
    printf("--------------------------------------------------\n");
    return 0;
  }

  if (strcmp(argv[1], "add") == 0) {

    if (argc < 3) {

      printf("Error: Missing task description.\n");
      printf("Usage: %s add \"task description\"\n", argv[0]);

      return 1;
    }

    add_task(argv[2]);
  }

  else if (strcmp(argv[1], "list") == 0) {

    if (argc > 2) {

      printf("error: unexpected argument(s)\n");
      printf("usage: fossil list\n");

      return 1;
    }

    list_tasks();
  }

  else {

    printf("Error: Unknown command '%s'\n", argv[1]);
    printf("Type '%s help' for a list of commands.\n", argv[0]);

    return 1;
  }

  return 0;
}
