#include "tasks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  if (argc < 2) {

    printf("\nError: No command provided.\n");
    printf("Type '%s help' to see available commands.\n", argv[0]);

    return 1;
  }

  if (strcmp(argv[1], "help") == 0) {

    fossil_help(argv[0]);

    return 0;
  }

  else if (strcmp(argv[1], "add") == 0) {

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

  else if (strcmp(argv[1], "done") == 0) {
    if (argc < 3) {
      printf("Error: Missing task ID.\n");
      printf("Usage: %s done <id>\n", argv[0]);
      return 1;
    }

    int target_id = atoi(argv[2]);

    if (target_id == 0 && strcmp(argv[2], "0") != 0) {
      printf("Error: '%s' is not a valid ID number.\n", argv[2]);
      return 1;
    }

    mark_done(target_id);
  }

  else if (strcmp(argv[1], "delete") == 0 || strcmp(argv[1], "del") == 0 ||
           strcmp(argv[1], "rm") == 0) {
    if (argc < 3) {
      printf("Error: Missing task ID.\n");
      printf("Usage: %s delete <id>\n", argv[0]);
      return 1;
    }

    int target_id = atoi(argv[2]);

    if (target_id == 0 && strcmp(argv[2], "0") != 0) {
      printf("Error: '%s' is not a valid ID number.\n", argv[2]);
      return 1;
    }

    delete_task(target_id);
  }

  else if (strcmp(argv[1], "clear") == 0) {

    if (argc > 2) {
      printf("Error: unexpected argument(s)\n");
      printf("Usage: %s clear\n", argv[0]);
      return 1;
    }

    char choice[10];
    printf("\nWARNING: This will permanently delete ALL tasks.\n");
    printf("Are you sure you want to continue? [y/N]: ");

    if (fgets(choice, sizeof(choice), stdin) != NULL) {
      choice[strcspn(choice, "\n")] = 0;
      if (strcmp(choice, "y") == 0 || strcmp(choice, "Y") == 0) {
        clear_tasks();
      } else {
        printf("Action cancelled.\n");
      }
    }
  }

  else if (strcmp(argv[1], "stats") == 0) {

    if (argc > 2) {
      printf("Warning: 'stats' doesn't take additional arguments. Ignoring "
             "'%s'...\n",
             argv[2]);
    }

    show_stats();
  }

  else if (strcmp(argv[1], "edit") == 0) {
    if (argc < 4) {
      printf("Usage: %s edit <id> <new_description>\n", argv[0]);
      return 1;
    }
    edit_task(atoi(argv[2]), argv[3]);
  }

  else {

    printf("Error: Unknown command '%s'\n", argv[1]);
    printf("Type '%s help' for a list of commands.\n", argv[0]);

    return 1;
  }

  return 0;
}
