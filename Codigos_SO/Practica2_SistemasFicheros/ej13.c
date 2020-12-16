#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {

	if (argc < 2) {
		printf("ERROR: Se debe especificar la ruta.\n");
		return -1;
	}

    int fd = open(argv[1], O_CREAT | O_RDWR, 0777);

    if (fd == -1) {
        printf("ERROR: No se ha podido abrir/crear el fichero.\n");
        return -1;
    }

    if(dup2(fd, 1) == -1 && dup2(fd, 2) == -1){
        printf("ERROR: Fallo en dup2.");
    }

    printf("Esto se ha redirigido de la salida estandar.\n");

    fprintf(stderr, "Esto se ha redirigido de la salida estandar de error.\n");

    return 1;
}