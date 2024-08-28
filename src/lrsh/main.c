
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../input_manager/manager.h"
#include "../process/process.h"
#include <sys/types.h>
#include <sched.h>


void suma(float first, float second, pid_t asdas, Process **head);

int main(int argc, char const *argv[])
{
  char** input;
  pid_t head_pid;

  Process* head = create_process("head", getpid());
  

  while (true)
  {
    printf("Enter a command: ");
    input = read_user_input();
    printf("%s\n", input[0]);

    if (strcmp(input[0], "exit") == 0)
    {
      free_processes(head);
      break;
    }

    else if (strcmp(input[0], "hello") == 0)
    {
      hellowolrd(head_pid, &head);
    }

    else if(strcmp(input[0], "sum") == 0)
    {
      float first = atof(input[1]);
      float second = atof(input[2]);

      suma(first, second, head_pid, &head);
    }

    else if(strcmp(input[0], "is_prime") == 0)
    {
      long long number = strtoll(input[1],NULL,10);
      isPrime(number, head_pid, &head);
    }

    else if(strcmp(input[0], "lrexec") == 0)
    {
      lrexec(input, head_pid, &head);
    }

    else if(strcmp(input[0], "lrlist") == 0)
    {
      print_processes(head);
    }

    else
    {
      printf("Command not found\n");
    }

    free_user_input(input);
  }
  free_user_input(input);
}

void hellowolrd(pid_t child, Process **head)
{
  child = fork(); 
  if(child == 0)
  {
    printf("Hello World\n");
    printf("Im the child\n");
    exit(0);
  }
  else
  {
    Process* new_process = create_process("hello", child);
    insert_process(head, new_process);
    int status;
    waitpid(child, &status, 0);
    update_process_status(*head, child, WEXITSTATUS(status));

  }
}

void suma(float first, float second, pid_t child, Process **head)
{
  child = fork();

  float total = 0;

   if(child == 0)
  {
    total = first + second;
    printf(" Child The sum is: %f\n", total);
    exit(0);
  }

  else
  {
    Process* new_process = create_process("sum", child);
    insert_process(head, new_process);
    int status;
    waitpid(child, &status, 0);
    update_process_status(*head, child, WEXITSTATUS(status));
  }
}

void isPrime(long long number, pid_t child, Process **head)
{
  child = fork();

  if(child == 0)
  {
    long long i;
    bool isPrime = true;

    for(i = 2; i <= number / 2; ++i)
    {
      if(number % i == 0)
      {
        isPrime = false;
        break;
      }
    }
    if (isPrime)
      printf("%lld is a prime number.\n", number);
    else
      printf("%lld is not a prime number.\n", number);
    exit(0);
  }
  else
  {
    Process* new_process = create_process("sum", child);
    insert_process(head, new_process);
    int status;
    waitpid(child, &status, 0);
    update_process_status(*head, child, WEXITSTATUS(status));
  }
}

void lrexec(char **input, pid_t child, Process **head)
{
  child = fork();

  if(child == 0)
  {
    char **copy;
    int i;
    int count = 0;
    for (i = 1; input[i] != NULL; i++) {
        count++;
    }

    copy = (char**)calloc((count + 1), sizeof(char*));
    for (i = 1; input[i] != NULL; i++) {
        copy[i - 1] = strdup(input[i]);
    }
    copy[count] = NULL; 

    execvp(input[1], copy);

    perror("execvp failed");
    for (i = 0; i < count; i++) {
        free(copy[i]);
    }
    free(copy);

    exit(1);  
  }
  else
  {
    Process* new_process = create_process(input[1], child);
    insert_process(head, new_process);
    int status;
    waitpid(child, &status, 0);
    update_process_status(*head, child, WEXITSTATUS(status));
  }
}

void print_processes(Process *head) {
  Process *current = head;
  while(current != NULL) {
    if (current->name != NULL) {
      printf("Name: %s\n", current->name);
    } else {
      printf("Unnamed process\n");
    }
    printf("PID: %d\n", current->pid);

    
    if (current->end_time >= 0 && current->start_time >= 0) {

      double elapsed_time = difftime(current->end_time, current->start_time);
      printf("Time: %.0f seconds\n", elapsed_time);

    } else if (current->exit_code == -1) {
      printf("Time: Not finished\n");
    }
    printf("Exit Code: %d\n", current->exit_code);

    current = current->next;
  }
}