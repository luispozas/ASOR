
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

  if (argc < 2) {
    printf("ERROR: Introduce el comando.\n");
    return -1;
  }

  char cmd[1024] = "";
  for(int i = 1; i < argc; i++){
    strcat(cmd, argv[i]);
    strcat(cmd, " ");
  }

  system(cmd);

  // Como system hace un fork y ejecuta execl, siempre imprimira esta parte.
  printf("El comando terminó de ejecutarse.\n");

  return 0;
}