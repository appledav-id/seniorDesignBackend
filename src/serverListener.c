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

char* readFromSocket(int connfd)
{
    char* buffer = malloc(sizeof(char) * 256);
    if(read(connfd, buffer, sizeof(buffer)) == -1)
        exit(1);   

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
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, portNum
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(portNum);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA *)&cli, (socklen_t*)&len);
    if (connfd < 0)
    {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");


    char* buffer = readFromSocket(connfd);
    if(!buffer)
        return NULL;
    
    FILE* fp = fopen("Netlist.net", "w+");
    if(!fp)
        return NULL;
    
    /* write to the file to be used later*/
    if(fwrite(buffer, sizeof(char), strlen(buffer), fp) != strlen(buffer))
        return NULL;
    
    close(sockfd);

    /* I hate this but idk what else to put here */
    return "Netlist.net";
}
