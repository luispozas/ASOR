#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){

  if (argc < 2) {
    printf("ERROR: Introduce el comando.\n");
    return -1;
  }

  //Ejecutamos el comando correspondiente a la entrada por argumentos
  execvp(argv[1], argv + 1);

  printf("El comando terminó de ejecutarse.\n");

  return 0;
}