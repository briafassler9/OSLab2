#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define   MAX_COUNT  200

void  ChildProcess(int pid);                /* child process prototype  */
void  ParentProcess(int child);               /* parent process prototype */

void  main(void)
{
  pid_t  pid;
  
  for(int i=0; i<2; i++) {
    pid = fork();
    if (pid == 0) 
        ChildProcess(i);
    else if (0 < pid) { 
      while(wait(NULL) != -1 || ECHILD != errno) {
        int j = wait(NULL);
        ParentProcess(j);
      }
    }
    else {
      printf("Error\n");
    }
  }
}

void  ChildProcess(int pid)
{
  int i;
  int num, timer;
  int parent_id = getppid();
  int pid_id = getpid();
  
  num = rand() % 31;
  timer = rand() % 11;
  srand(time(NULL));
  
  if (pid == 0) {
    printf("Child Process 1 \n");
    for (i=0; i<num; i++) {
      printf("Child process is sleeping: %d\n", pid_id);
      sleep(timer);
      printf("Child process is awake: %d\n", pid_id);
      printf("Parent process: %d\n", parent_id);
    }
    exit(0);
  }
  else if (pid == 1) {
    printf("Child Process 2 \n");
    for (i=0; i<num; i++) {
      printf("Child process is sleeping: %d\n", pid_id);
      sleep(timer);
      printf("Child process is awake: %d\n", pid_id);
      printf("Parent process: %d\n", parent_id);
    }
    exit(0);
  }
}

void  ParentProcess(int child)
{
  printf("Child process has terminated: %d\n", child);
}