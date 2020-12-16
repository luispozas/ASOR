#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
	
	printf("Numero máximo de enlaces: %ld\n", pathconf(".",_PC_LINK_MAX));
	printf("Tamaño máximo de ruta: %ld\n", pathconf(".",_PC_PATH_MAX));
	printf("Tamaño máximo de nombre de fichero: %ld\n", pathconf(".",_PC_NAME_MAX));

	return 0;
}
