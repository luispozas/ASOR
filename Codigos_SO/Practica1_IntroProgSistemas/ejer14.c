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
	struct tm *info = localtime(&t);

	printf("El año actual es: %i\n", 1900 + info->tm_year);

	return 0;
}
