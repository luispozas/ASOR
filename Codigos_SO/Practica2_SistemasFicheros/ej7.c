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
    
  	mode_t prev = umask(027); // 027

  	const char *path = argv[1];
  	int df = open(path, O_CREAT, 0777);

  	mode_t last = umask(prev);

  	printf("Mask = %i\n", last);
	return 0;
}
