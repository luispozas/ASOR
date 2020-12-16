#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char **argv) {

	if (argc < 2) {
		printf("ERROR: Se debe especeficar la ruta.\n");
		return -1;
	}

    if (int fd = open(argv[1], O_CREAT | O_RDWR, 0777) == -1) {
        printf("ERROR: No se ha podido abrir/crear el fichero.\n");
        return -1;
    }
//MAL
    int fd2 = dup2(fd, newFile);

    printf("Esto se ha reedirigido a d\n", argv[1]);

    dup2(fd2, fd)

    return 1;
}