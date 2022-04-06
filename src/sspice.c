#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/serverListener.h"
#include "../inc/ngspiceSim.h"

int portNum;

int main(int argc, char** argv)
{
    if(argc > 1)
        portNum = atoi(argv[1]);
    else
        portNum = 8080;
    
    char* clientIP = malloc(sizeof(char) * 16);
    int* clientPort;
    int* connfd = malloc(sizeof(int));
    
    //printf("PortNum: %d\n", portNum);
    /* begin with setting up the socket and returning the filename to be passed to ngspice */
    char* netlistString = initServerListener(portNum, &clientIP, clientPort, connfd);

    /* init the simulation engine */
    initNgspice();

    /* after init, we are free to simulate */
    simNetlistFromSocket(netlistString);
    
    if(returnResults("results.raw", clientIP, *clientPort, *connfd) == 0)
        return 0;
    else
    {
        close(*connfd);
        printf("Failed to return results to user...\nExiting");
        exit(-1);
    }
}