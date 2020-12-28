#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>


int main(int argc, char **argv){

    char *tuberia1 = "tuberia1";
    if(mkfifo(tuberia1, 0777) == -1){
        printf("Error mkfifo primera tuberia.\n");
        exit(EXIT_FAILURE);
    }

    char *tuberia2 = "tuberia2";
    if(mkfifo(tuberia2, 0777) == -1){
        printf("Error mkfifo segunda tuberia.\n");
        exit(EXIT_FAILURE);
    }

    int fd1 = open(tuberia1, O_RDONLY | O_NONBLOCK);
    int fd2 = open(tuberia2, O_RDONLY | O_NONBLOCK);

    if(fd1 == -1 || fd2 == -1){
        printf("Error en la apertura de las tuberias.\n");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    char buffer[256]; //Buffer para los datos enviados
    int cambios = 0;
    fd_set set;
    int size_read = 0;

    while(cambios != -1){
        FD_ZERO(&set);
        FD_SET(fd1, &set);
        FD_SET(fd2, &set);

        cambios = select((fd1 > fd2)? fd1+1 : fd2+1, &set, NULL, NULL, NULL);

        if(cambios){
            if(FD_ISSET(fd1, &set)){
                size_read = read(fd1, buffer, sizeof(buffer));
                buffer[size_read] = '\0'; //Si el buffer anterior tiene mas tamaño relleno hay que despreciarlo
                
                if(size_read == 0){
                    close(fd1);
                    fd1 = open(tuberia1, O_RDONLY | O_NONBLOCK);
                }
                else printf("Tuberia 1: %s", buffer);
            }
            if(FD_ISSET(fd2, &set)){
                size_read = read(fd2, buffer, sizeof(buffer));
                buffer[size_read] = '\0';
                
                if(size_read == 0){
                    close(fd2);
                    fd2 = open(tuberia2, O_RDONLY | O_NONBLOCK);
                }
                else printf("Tuberia 2: %s", buffer);

            }
        }
        else{
            printf("Ningun dato nuevo.\n");
        }

    }

    close(fd1);
    close(fd2);
    return 0;
}