#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv){

  if (argc < 2) {
    printf("ERROR: Introduce el comando.\n");
    return -1;
  }

  pid_t pid = fork();

  switch (pid) {
    case -1:
      perror("fork");
      exit(-1);
    break;

    //Proceso hijo
    case 0:;
      pid_t mi_sid = setsid(); //Creamos una nueva sesión
      printf("[Hijo] Proceso %i (Padre: %i)\n",getpid(),getppid());

      int fdout = open("/tmp/daemon.out",O_CREAT | O_RDWR, 0777);
      int fderr = open("/tmp/daemon.err", O_CREAT | O_RDWR, 0777);
      int fdin = open("/dev/null", O_CREAT | O_RDWR, 0777);

      int fd2 = dup2(fdout,2);
      int fd3 = dup2(fderr, 1);
      int fd4 = dup2(fdin, 0);

      execvp(argv[1], argv + 1);
      break;

    //Proceso padre
    default:
        printf("[Padre] Proceso %i (Padre: %i)\n",getpid(),getppid());
        break;
  }

  return 0;
}