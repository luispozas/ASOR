#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int showProcessInfo(char *id) {
	if (id == NULL)
		return -1;

	pid_t pid = getpid();
	gid_t gid = getgid();
	pid_t sid = getsid(pid);

	struct rlimit lim;
	int rc = getrlimit(RLIMIT_NOFILE, &lim);

	char *path = malloc(sizeof(char)*(4096 + 1));
	getcwd(path, 4096 + 1);

	printf("[%s] PID: %i\n", id, pid);
	printf("[%s] GID: %i\n", id, gid);
	printf("[%s] SID: %i\n", id, sid);
	printf("[%s] Max num of files: %li\n", id, lim.rlim_max);
	printf("[%s] Directorio trabajo: %s\n", id, path);
		
	free (path);
	return 0;
}

int main() {
    pid_t pid = fork();
   
    if(pid == -1){
        printf("Error en fork\n");
    }
    if(pid == 0){ //Proceso Hijo
        pid_t nsid = setsid();
        chdir("/tmp");
        printf("[Hijo] Proceso %i (Padre: %i)\n",getpid(),getppid());

        showProcessInfo("Hijo"); 
    }
    else{ //Proceso padre
    	printf("[Padre] Proceso %i (Padre: %i)\n",getpid(),getppid());

        showProcessInfo("Padre");
        sleep(2);  
    }
    return 0;
}
