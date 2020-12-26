#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]){

	if(argc != 1){
		printf("ERROR en los parametros del programa.\n");
	}
	printf("Pid del proceso: %d.\n", getpid());

	char *sleep_c = getenv("SLEEP_SECS");
	int  sleep_i = 15;
	if(sleep_c != NULL)
		sleep_i = atoi(sleep_c);

	printf("Se va a dormir el proceso durante %d seg.\n", sleep_i);

	//Inicializamos un conjunto de señales y añadimos senales SIGINT y SIGTSTP
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTSTP);

	//Protegemos la region de codigo contra la recepcion de las senales.
	sigprocmask(SIG_BLOCK, &set, NULL);

	sleep(sleep_i);

	//Comprobamos las señales pendientes
	sigset_t set_pending;
	sigpending(&set_pending);

	if(sigismember(&set_pending, SIGINT) == 1){
		printf("Se ha recibido la señal SIGINT\n");
	}
	else{ printf("No se ha recibido la señal SIGINT\n");}

	if(sigismember(&set_pending, SIGTSTP) == 1){
		printf("Se ha recibido la señal SIGTSTP\n");
		sigprocmask(SIG_UNBLOCK, &set, NULL);
	}
	else{ printf("No se ha recibido la señal SIGTSTP\n");}

	return 0;
}