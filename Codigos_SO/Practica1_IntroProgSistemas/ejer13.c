#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>

const int MAX = 1000000;

int main (int argc, char *argv[]){

	long int i = 0;
	
	struct timeval t_ini, t_fin;
	gettimeofday(&t_ini, NULL);

	while(i < MAX){
		i++;
	}
	
	gettimeofday(&t_fin, NULL);

	printf("Lo que tarda un bucle que incrementa una\n");
	printf("variable %d veces: %d microsegundos\n", i, (t_fin.tv_usec - t_ini.tv_usec));

	return 0;
}
