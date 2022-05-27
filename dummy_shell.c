#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include "leercadena.h"
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100

int len_cmds(char **chains) {
  for(int i = 0; 1; i++) {
     if(chains[i]==NULL) {
	return i;     
     }
  }
}

void init_shell() {
  system("clear");	
  printf("*****************************************************************************\n");
  printf("*                    WELCOME TO UNIXVALLE'S COMMAND PROMPT                  *\n");
  printf("*    AUTHORS:                                                               *\n");
  printf("*    <>Diego Fernando Chaverra                                              *\n");
  printf("*    <>David Alberto Guzman                                                 *\n");
  printf("*    <>Juan Camilo Santa                                                    *\n");
  printf("*                                                                           *\n");
  printf("*                      RUN IT ONLY UNDER YOUR OWN RISK!                     *\n");
  printf("*                                 ENJOY IT!                                 *\n");
  printf("*                                                                           *\n");
  printf("*****************************************************************************\n");
  sleep(5);
  system("clear");
}

typedef struct
{
  int pid;
  char **command;
} process;

int main(int argc, char* argv[]) {
  char **vector_cadenas;
  process background[MAX];
  char cadena[MAX];
  int nElemBg = 0;
  int commands_len = 0;
  bool notIgnoreWait = true;
  
  init_shell();  

  void delete_from_bg(int pid) {
    for (int c = 0; c < nElemBg; c++){
	if((int)background[c].pid==pid) {
	  for(int k = c; k < nElemBg; k++) 
             background[k] = background[k+1];
	  kill(pid, SIGABRT);
	  --nElemBg;
	  break;
	}
	if(c == nElemBg - 1) {
	  printf("Error! element whose pid is: %d hasn't been found!\n", pid);
	}
    }
  }

  void send_to_bg(char **command, int pid) {
    command[commands_len-1] = NULL;
    notIgnoreWait = false;
    process p = {pid, command};
    background[nElemBg] = p; 
    ++nElemBg;
  }

  void read_cmd(char **command) {
    for(int i = 0; 1; i++) {
	if(command[i+1]==NULL){
	  printf("%s \n", command[i]);
	  break;
	}  
	printf("%s ", command[i]);
    }
  }

  while (1) {
      pid_t pid;
      printf( "(%d)username@host$ ", getpid());
      leer_de_teclado(MAX, cadena);
      vector_cadenas = de_cadena_a_vector(cadena);
      commands_len = len_cmds(vector_cadenas); 
      
      if (strcmp("salir",vector_cadenas[0]) == 0){	
	 printf("*****************************************************************************\n");
	 printf("******************** Gracias por usar mi dummy shell ;-) ********************\n");
	 printf("*****************************************************************************\n");
	 break;
      }
      
      if (strcmp("detener",vector_cadenas[0]) == 0){
	 if (commands_len == 1) {
	   printf("Error! missing argument PID\n");
	 }
	 else {
	   int kpid = atoi(vector_cadenas[1]);
  	   if (nElemBg == 0) {
	     printf("There're no arguments in background\n");
	   } 
	   else {
	     delete_from_bg(kpid);
	   }
	 }
      }

      if (strcmp("tareas",vector_cadenas[0]) == 0){
	for(int i = 0; i < nElemBg; i++) {
 	  printf(">> pid: %d --> ", background[i].pid);
	  read_cmd(background[i].command);
	}	      
      }

      pid = fork();
      assert(pid >= 0);
      if (pid == 0) { 
        if (strcmp("&", vector_cadenas[commands_len-1])==0){	
          //remove & from command
          vector_cadenas[commands_len-1] = NULL;
	}
	  execvp(vector_cadenas[0], vector_cadenas);
          exit(0);
      } else {
        if (strcmp("&", vector_cadenas[commands_len-1])==0){	
	  printf("command sent to background\n");
	  usleep(100*1000);
	  send_to_bg(vector_cadenas, pid);
        }
	if (notIgnoreWait) {
          wait(NULL);
	}
	else {
	  usleep(100*1000);
	}
      }
  }
  printf("*****************************************************************************\n");
  printf("The last command executed was:\n");
  read_cmd(vector_cadenas);
  printf("background's length: %d\n", nElemBg);
  printf("*****************************************************************************\n");
  return 0;
}
