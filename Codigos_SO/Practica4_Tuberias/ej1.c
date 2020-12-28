#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
    
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    pipe(pipefd);
    pid_t pid = fork();

    if(pid == -1){
        printf("fork\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){ //Hijo
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        execlp(argv[3], argv[3], argv[4], NULL);
    }
    else{ // Padre
        close(pipefd[0]);
        dup2(pipefd[1],1);
        execlp(argv[1], argv[1], argv[2], NULL);
    }

    return 0;
}