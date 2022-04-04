#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../inc/serverListener.h"

#define SA struct sockaddr

/* convenience function to cleanup server init */
static void die(const char* errorString, int errNo)
{
    printf("[DIE]: %s\n", errorString);
    exit(errNo);
}

char* readFromSocket(int connfd)
{
    char* buffer = malloc(sizeof(char) * MAX_BUFFER_LENGTH);

    if(read(connfd, buffer, MAX_BUFFER_LENGTH) == -1)
        die("Read from connfd failed", -1);

    printf("%s\n", buffer);
    return buffer;
}

// Driver function
char* initServerListener(int portNum)
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) 
        die("Socked creation failed", -1);
        
    printf("Socket successfully created..\n");

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, portNum
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(portNum);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
        die("Socket bind failed", -1);
    
    printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
        die("Listen failed", -1);
    
    printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA *)&cli, (socklen_t*)&len);
    if (connfd < 0)
        die("Server accept failed", -1);
        
    printf("server accept the client...\n");


    char* buffer = readFromSocket(connfd);
    if(!buffer)
        die("Buffer returned NULL", -1);

    close(sockfd);

    return buffer; 
}
