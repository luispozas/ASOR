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
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = 0;

    getaddrinfo(argv[1], argv[2], &hints, &result);

    int socketTCP = socket(result->ai_family, result->ai_socktype, 0);
    connect(socketTCP,(struct sockaddr *)result->ai_addr, result->ai_addrlen);


    char buf_out[256];
    char buf_in[256];
    int c;

    while(1){
        c = read(0, buf_out, sizeof(buf_out));
        buf_out[c] = '\0';

        send(socketTCP, buf_out, c, 0);

        if(buf_out[0] == 'q'){
            printf("conexion terminada.");
            break;
        }

        c = recv(socketTCP, buf_in, sizeof(buf_in), 0);
        buf_in[c] = '\0';
        printf("[OUT]: %s\n", buf_in);
    }

    close(socketTCP);

    exit(EXIT_SUCCESS);
}