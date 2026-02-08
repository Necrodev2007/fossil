#ifndef TASKS_H
#define TASKS_H
#define DB_PATH "tasks.txt"
#define DB_TEMP_PATH "temp.tmp"

typedef struct {
  int id;                // Primary key for task identification
  char description[100]; // Character buffer for task details
  int status;            // Completion flag (0: Pending | 1: Done)

} Task;

void list_tasks(); /* Reads all tasks from the file and
                      displaythem in a formatted table */

void add_task(char *desc); /* Adds a new task to the storage file
                              and assign a unique ID */

void mark_done(int target_id); // Mark a task as completed by providing the ID

void delete_task(int target_id); // Remove a task from the list

void clear_tasks(); // Clear taks list

void fossil_help(char *argv0); // show command list

void show_stats(); // show status of all task

void edit_task(int target_id, const char *new_description);

#endif
