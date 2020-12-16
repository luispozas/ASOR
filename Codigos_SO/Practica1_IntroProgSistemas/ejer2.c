#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[]){

	if(setuid(0) == -1){ /*Compruebo si existe un error.*/
		/*Distingo el tipo de error con variable "errno".*/
		if(errno == EAGAIN){
			perror("Error tipo -> EAGAIN");
			exit -1;
		}
		if(errno == EINVAL){
			perror("Error tipo -> EINVAL");
			exit -1;
		}
		if(errno == EPERM){
			perror("Error tipo -> EPERM");
			exit -1;
		}

		printf("ERROR(%d): %s\n", errno, strerror(errno));
	}

	return 0;
}
