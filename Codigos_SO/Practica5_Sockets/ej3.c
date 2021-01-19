#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints;
    struct addrinfo *result;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;

    getaddrinfo(argv[1], argv[2], &hints, &result);

    int socketUDP = socket(result->ai_family, result->ai_socktype, 0);

    freeaddrinfo(result);

    char buf[2];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    struct sockaddr_storage client_addr;
    socklen_t client_addrlen = sizeof(client_addr);

    sendto(socketUDP, argv[3], 2, 0, result->ai_addr, result->ai_addrlen);
    printf("Comando enviado: %s\n", argv[3]);

    if(*argv[3]=='t' || *argv[3] == 'd'){
        char s[50];
        int bytes = recvfrom(socketUDP, s, sizeof(s), 0, (struct sockaddr *) &client_addr, &client_addrlen);
        s[bytes] = '\0';

        printf("%s\n", s);
    }

    exit(EXIT_SUCCESS);
}