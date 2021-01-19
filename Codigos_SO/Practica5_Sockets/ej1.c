#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char **argv){
	struct addrinfo hints;
	struct addrinfo *result, *ptr;

	char host[NI_MAXHOST];
   	char serv[NI_MAXSERV];

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; //AF_INET para ipv4

	int rc = getaddrinfo(argv[1], NULL, &hints, &result);

	for(ptr = result; ptr != NULL; ptr = ptr->ai_next){
		getnameinfo(ptr->ai_addr, ptr->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		printf("%s -- %i -- %i\n", host, ptr->ai_family, ptr->ai_socktype);
	}
	return 0;
}
