#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

const int MAX_ERRORES=255;

int main (int argc, char *argv[]){

	for(int i = 0; i < MAX_ERRORES; i++){
		printf("ERROR(%d): %s\n", i, strerror(i));
	}
	return 0;
}

