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
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;

    getaddrinfo(argv[1], argv[2], &hints, &result);

    int s = socket(result->ai_family, result->ai_socktype, 0);

    bind(s, result->ai_addr, result->ai_addrlen);

    char buf[2];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    struct sockaddr_storage client_addr;
    socklen_t client_addrlen = sizeof(client_addr);

    while(1){
        int bytes = recvfrom(s, buf, 2, 0, (struct sockaddr *) &client_addr, &client_addrlen);
        buf[1] = '\0';

        getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

        printf("%i bytes de %s   -   %s\n", bytes, host, serv);

        time_t t = time(NULL);
        struct tm *info = localtime(&t);
        char str[50];

        if(buf[0] == 't'){
            int bytesT = strftime(str, sizeof(str), "%T", info);
            
            sendto(s, str, bytesT, 0 ,(struct sockaddr *)&client_addr, client_addrlen);
        }
        else if(buf[0] == 'd'){
            int bytesT = strftime(str, sizeof(str), "%A, %d %B %Y", info);
            
            sendto(s, str, bytesT, 0 ,(struct sockaddr *)&client_addr, client_addrlen);
        }
        else if(buf[0] == 'q'){
            printf("Saliendo...\n");
            exit(0);
        }else{
            printf("Comando no valido -> Insertelo de nuevo.");
        }
    }
    return 0;
}