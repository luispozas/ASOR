#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	if(argc!=2) {
        printf("Ha olvidado el nombre del fichero.\n");
        exit(1); 
    }
    
  	const char *path = argv[1];

  	int df = open(path, O_CREAT, 0645);

  	printf("Descriptor del fichero %s = %i\n", path, df);

	return 0;
}
