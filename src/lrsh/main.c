
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../input_manager/manager.h"
#include <sys/types.h>
#include <sched.h>

void suma(float first, float second, pid_t asdas);

int main(int argc, char const *argv[])
{
  char** input;
  pid_t asdas;

  while (true)
  {
    printf("Enter a command: ");
    input = read_user_input();
    printf("%s\n", input[0]);
    if (strcmp(input[0], "exit") == 0)
    {
      break;
    }
    else if (strcmp(input[0], "hello") == 0)
    {
      hellowolrd(asdas);
    }
    else if(strcmp(input[0], "sum") == 0)
    {
      float first = atof(input[1]);
      float second = atof(input[2]);

      suma(first, second, asdas);
    }
    else if(strcmp(input[0], "is_prime") == 0)
    {
      long long number = strtoll(input[1],NULL,10);
      isPrime(number, asdas);
    }
    else if(strcmp(input[0], "lrexec") == 0)
    {
      lrexect(input, asdas);
    }
    else
    {
      printf("Command not found\n");
    }
    free_user_input(input);
  }
  
  
}

void hellowolrd(pid_t asdas)
{
  asdas = fork(); 
  if(asdas == 0)
  {
    printf("Hello World\n");
    printf("Im the child\n");
    exit(0);
  }
  else
  {
    wait(NULL);
  }
  
}

void suma(float first, float second, pid_t asdas)
{
  asdas = fork();

  float total = 0;

   if(asdas == 0)
  {
    total = first + second;
    printf(" Child The sum is: %f\n", total);
    exit(0);
  }

  else
  {
    wait(NULL);
  }
}

void isPrime(long long number, pid_t asdas)
{
  asdas = fork();

  if(asdas == 0)
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
    wait(NULL);
  }
}

void lrexect(char **input, pid_t asdas)
{
    asdas = fork();
    if(asdas == 0)
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

        for (i = 0; i <= count; i++) {
            printf("Argument %d: %s\n", i, copy[i]);
        }

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
        wait(NULL);
    }
}