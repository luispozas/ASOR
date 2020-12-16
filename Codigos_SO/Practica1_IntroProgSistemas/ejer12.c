#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>

int main (int argc, char *argv[]){
	
	time_t t = time(NULL);	

	/*char *ctime(const time_t *timep);*/
	char *date = ctime(&t);

	printf("La hora desde el Epoch: %s\n", date);

	return 0;
}


