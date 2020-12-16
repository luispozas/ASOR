#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int main (int argc, char *argv[]){
	
	printf("ID real: %d\n", getuid());
	printf("ID efectivo: %d\n", geteuid());

	return 0;
}

