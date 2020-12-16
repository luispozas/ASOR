#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
	
	printf("Longitud maxima de Argumentos: %d\n", sysconf(_SC_ARG_MAX));
	printf("Numero maximo de hijos: %d\n", sysconf(_SC_CHILD_MAX));
	printf("Numero maximo de ficheros: %d\n", sysconf(_SC_OPEN_MAX));

	return 0;
}
