#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

//Ejemplo suponiendo creada la tuberia llamada "tuberia"
int main(int argc, char **argv){

    if (argc < 2) {
        printf("ERROR: Falta el mensaje para enviar por argumento.\n");
        return -1;
    }

    int fd = open("tuberia", O_WRONLY);

    argv[1] = strcat(argv[1], "\n");  //Para poner el salto de linea

    write(fd, argv[1], strlen(argv[1]));

    close(fd);

    return 0;
}


/*
//Ejemplo sin haber creado previamente la tuberia
int main(int argc, char **argv){

    if (argc < 2) {
        printf("ERROR: Falta el mensaje para enviar por argumento.\n");
        return -1;
    }

    char *tuberia = "tuberia";
    mkfifo(tuberia, 0777);

    int fd = open(tuberia, O_WRONLY);

    write(fd, argv[1], strlen(argv[1]));

    close(fd);

    return 0;
}
*/