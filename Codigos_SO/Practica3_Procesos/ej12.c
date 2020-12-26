#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile int int_c = 0;
volatile int tstp_c = 0;

void hler(int senial){
  if (senial == SIGINT) int_c++;
  if (senial == SIGTSTP) tstp_c++;
}

int main(int argc, char* argv[]){

  printf("Pid del proceso: %d.\n", getpid());
  
  struct sigaction act;

  //SIGINT
  sigaction(SIGINT, NULL, &act); //Get handler
  act.sa_handler = hler;
  sigaction(SIGINT, &act, NULL); //Set sa_handler

  //SIGTSTP
  sigaction(SIGTSTP, NULL, &act); //Get handler
  act.sa_handler = hler;
  sigaction(SIGTSTP, &act, NULL); //Set sa_handler


	while (int_c + tstp_c < 10)
		pause();

	printf("Numero de señales SIGINT recibidas: %i\n", int_c);
	printf("Numero de señales SIGTSTP recibidas: %i\n", tstp_c);

  return 0;
}