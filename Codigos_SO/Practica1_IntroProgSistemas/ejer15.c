#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>


int main (int argc, char *argv[]){

	time_t t = time(NULL);
	struct tm *info = localtime(&t);

	char c[200];
	strftime(c, sizeof(c), "%A, %d %B %Y %T", info);

	/*OJO: tm_year   The number of years since 1900.*/
	printf("El año actual es: %s\n", c);

	return 0;
}
