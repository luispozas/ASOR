/*
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]){

	if(argc != 2){
		printf("ERROR en los parametros del programa.\n");
		return -1;
	}
	printf("Pid del proceso: %d.\n", getpid());


	int  sleep_i = atoi(argv[1]);
	printf("Se va a dormir el proceso durante %d seg.\n", sleep_i);

	//Inicializamos un conjunto de señales y añadimos senales SIGINT y SIGTSTP
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);

	//Protegemos la region de codigo contra la recepcion de las senales.
	sigprocmask(SIG_BLOCK, &set, NULL);

	sleep(sleep_i);

	//Comprobamos las señales pendientes
	sigset_t set_pending;
	sigpending(&set_pending);

	if(sigismember(&set_pending, SIGUSR1) == 1){
		printf("Has tenido suerte, hemos recibido la señal SIGUSR1.\n");
		return 0;
	}
	else{
		printf("No se ha recibido la señal SIGUSR1 -> Se elimina este ejecutable.\n");
		unlink(argv[0]);
	}
	return 0;
}
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile int stop = 0;

void hler(int senial){
  if (senial == SIGUSR1) stop = 1;
}

int main(int argc, char* argv[]){

	if(argc != 2){
		printf("ERROR en los parametros del programa.\n");
		return -1;
	}
	printf("Pid del proceso: %d.\n", getpid());

	int  sec = atoi(argv[1]);
	printf("Se va a dormir el proceso durante %d seg.\n", sec);
  
	struct sigaction act;

	//SIGUSR1
	sigaction(SIGUSR1, NULL, &act); //Get handler
	act.sa_handler = hler;
  	sigaction(SIGUSR1, &act, NULL); //Set sa_handler

	sleep(sec);

	if(stop == 0){
		printf("No se ha recibido la señal SIGUSR1 -> Se elimina este ejecutable.\n");
		unlink(argv[0]);
	}
	else{
		printf("Has tenido suerte, hemos recibido la señal SIGUSR1.\n");
	}

 	return 0;
}