#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
	struct utsname info;

	if(uname(&info) == -1){
		printf("ERROR(%d): %s\n", errno, strerror(errno));
	}
	else {
		printf("Sysname: %s\n", info.sysname);
		printf("Nodename: %s\n", info.nodename);
		printf("Release: %s\n", info.release);
		printf("Version: %s\n", info.version);
		printf("Machine: %s\n", info.machine);
	}

	return 0;
}
