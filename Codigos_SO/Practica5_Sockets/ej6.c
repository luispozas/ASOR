#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include <netdb.h>

int main(int argc, char **argv){
    
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    getaddrinfo(argv[1], argv[2], &hints, &result);

    int s = socket(result->ai_family, result->ai_socktype, 0);

    bind(s, result->ai_addr, result->ai_addrlen);

    listen(s, 5);


    char buf[500];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    struct sockaddr_storage client_addr;
    socklen_t client_addrlen = sizeof(client_addr);

    while(1){
        int f_cliente = accept(s, (struct sockaddr *) &client_addr, &client_addrlen);

         getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
        printf("Conexion desde Host: %s  Puerto: %s\n", host, serv);

        int c;
        while(c = recv(f_cliente, buf, sizeof(buf), 0)){
            buf[c] = '\0';
            printf("Mensaje: %s\n", buf);
            send(f_cliente, buf, c, 0);
        }
        close(f_cliente);
    }
    return 0;
}