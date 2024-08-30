#include "process.h"

Process* create_process( char *name, pid_t pid)
{
    Process *new_process = calloc(1, sizeof(Process));
    if (!new_process) {
        perror("Failed to allocate memory for new process");
        exit(EXIT_FAILURE);
    }
    new_process->name = strdup(name); 
    if (!new_process->name) {
        perror("Failed to allocate memory for process name");
        free(new_process);
        exit(EXIT_FAILURE);
    }
    new_process->start_time = time(NULL);
    new_process->end_time = 0;
    new_process->exit_code = -1;
    new_process->pid = pid;
    new_process->next = NULL;
    return new_process;
}

void update_process_status(Process *head, pid_t pid, int exit_code) {
    Process *current = head;
    while (current != NULL) {
        if (current->pid == pid && current->exit_code != -1) {
            current->end_time = time(NULL);  
            current->exit_code = exit_code;
            break;
        }
        else if(current->pid == pid && current->exit_code == -1) {
            current->exit_code = exit_code;
            break;
        }
        current = current->next;
    }
}

void insert_process(Process **head, Process *new_process)
{
    if (*head == NULL)
    {
        *head = new_process;
    }
    else
    {
        Process *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_process;
        new_process->back = current;
    }
}

void free_processes(Process *head)
{
    Process *current = head;
    Process *next;
    while (current != NULL)
    {
        next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
}