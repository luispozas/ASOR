#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <string.h>



int main(int argc, char *argv[]){

    if(argc != 2) {
        printf("ERROR: Ha olvidado la ruta del fichero.\n");
        return -1;
    }

    char *path = argv[1];
    struct stat buff;

    if(stat(path, &buff) == -1){
        printf("ERROR: funcion stat.\n");
        return -1;
    }

    char slink[255];
    char hlink[255];

    strcpy(slink, argv[1]);
    strcat(slink, ".sym");
    strcpy(hlink, argv[1]);
    strcat(hlink, ".hard");


    if (S_ISREG(buff.st_mode)) {
        if(symlink(argv[1], slink) == -1){ return -1; }
        printf("Enlace simbolico creado.\n");

        if(link(argv[1], hlink) == -1){ return -1;}
        printf("Enlace rigido creado.\n");
    }
    else{
        printf("ERROR. El archivo especificado no es regular.\n");
        return -1;
    }

	return 0;
}