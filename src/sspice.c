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
    
    //printf("PortNum: %d\n", portNum);
    /* begin with setting up the socket and returning the filename to be passed to ngspice */
    char* netlistString = initServerListener(portNum);

    /* init the simulation engine */
    initNgspice();

    /* after init, we are free to simulate */
    // TODO: find a way to get back the output choice 
    simNetlistFromSocket(netlistString);
}