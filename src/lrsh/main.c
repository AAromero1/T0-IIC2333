
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../input_manager/manager.h"

int main(int argc, char const *argv[])
{
  char** input;

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
      printf("My Arch ;)\n");
    }
    else if(strcmp(input[0], "pwd") == 0)
    {
      char cwd[1024];
      getcwd(cwd, sizeof(cwd));
      printf("Current working dir: %s\n", cwd);
    }
    else if(strcmp(input[0], "ls") == 0)
    {
      system("ls");
    }
    else
    {
      printf("Command not found\n");
    }
  }
  
  free_user_input(input);


}

