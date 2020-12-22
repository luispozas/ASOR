#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(int argc, char **argv) {

	pid_t pid = getpid();
	pid_t pgid = getpgid(pid); 
	pid_t ses_id = getsid(pid);


	struct rlimit rlim;
	getrlimit(RLIMIT_NOFILE, &rlim);

	char dir[1024];
	getcwd(dir, sizeof(dir));

	printf("ID del proceso: %i \n", pid);
	printf("PGID del proceso: %i \n", pgid);
	printf("Identificador de sesión %i \n", ses_id);
	printf("Número máximo de ficheros que puede abrir: %lli\n", rlim.rlim_max);
	printf("Directorio de trabajo: %s \n", dir);
	
	return 0;
}