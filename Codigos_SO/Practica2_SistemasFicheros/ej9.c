/*
Programa que emule el comportamiento del comando stat y muestre:
- El número major y minor asociado al dispositivo.
- El número de i-nodo del fichero.
- El tipo de fichero (directorio, enlace simbólico o fichero ordinario).
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/sysmacros.h>


int main(int argc, char *argv[]){

    if(argc != 2) {
        printf("ERROR: Ha olvidado la ruta del fichero.\n");
        return -1;
    }

    char *path = argv[1];
    struct stat buff;

    if(stat(path, &buff) == -1){
        printf("ERROR: stat().\n");
        return -1;
    }

    printf("Tipo fichero:  ");

    if (S_ISREG(buff.st_mode)) {
        printf("fichero ordinario.\n");
    }
    else if (S_ISLNK(buff.st_mode)) {
        printf("enlace simbolico.\n");
    }
    else if (S_ISDIR(buff.st_mode)) {
        printf("directorio.\n");  
    }
    else { 
        printf("otros...\n"); 
    }


    printf("I-node: %li\n", buff.st_ino);

    printf("MAJOR: %li\n", major(buff.st_dev));
    printf("MINOR: %li\n", minor(buff.st_dev));

    printf("Ultimo cambio de estado: %s", ctime(&buff.st_ctime));
    printf("Ultimo acceso:           %s", ctime(&buff.st_atime));
    printf("Ultima modificacion:     %s", ctime(&buff.st_mtime));

	return 0;
}