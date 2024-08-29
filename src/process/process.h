#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sched.h>

typedef struct process_t{
    char *name;
    pid_t pid;
    time_t start_time; 
    time_t end_time;   
    int exit_code;
    struct process_t *next;
    struct process_t *back;

} Process;

Process* create_process( char *name, pid_t pid);
void update_process_status(Process *head, pid_t pid, int exit_code);
void insert_process(Process **head, Process *new_process);
void free_processes(Process *head);
