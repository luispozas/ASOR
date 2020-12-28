#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
    
    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Creación de dos tuberias */
    int p_h[2];
    int h_p[2];
    pipe(p_h);
    pipe(h_p);

    pid_t pid = fork();

    if(pid == -1){
        printf("fork\n");
        exit(EXIT_FAILURE);
    }

    //Hijo
    else if(pid == 0){ 
        close(p_h[1]); 
        close(h_p[0]);

        char recibe_padre[256];
        char *senial_lq = "l";

        for(int i = 0; i < 10; i++){
            sleep(1);
            int size_r = read(p_h[0], recibe_padre, sizeof(recibe_padre));
            printf("[HIJO] Mensaje recibido: %s\n", recibe_padre);
            sleep(1);
            write(h_p[1], senial_lq, 1);
        }
        senial_lq = "q";
        write(h_p[1], senial_lq, 1);

        close(p_h[0]); 
        close(h_p[1]);
    }

    // Padre
    else{ 
        close(p_h[0]); 
        close(h_p[1]);

        char envia_padre[256];
        char *msg_hijo = "l";
        
        while(msg_hijo[0] != 'q'){
            printf("[PADRE] Escribe el mensaje: \n");
            int size_e = read(0, envia_padre, sizeof(envia_padre));
            write(p_h[1], envia_padre, size_e);

            while(msg_hijo[0] != 'l' && msg_hijo[0] != 'q'){
                read(h_p[0], msg_hijo, strlen(msg_hijo));
            }
            sleep(1);
        }

        close(p_h[1]); 
        close(h_p[0]);
    }

    return 0;
}