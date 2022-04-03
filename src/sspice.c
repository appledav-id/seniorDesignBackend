#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/serverListener.h"
#include "../inc/ngspiceSim.h"

#include </usr/local/include/ngspice/sharedspice.h>

#define PORT 8080

int main(int argc, char** argv)
{
    /* begin with setting up the socket and returning the filename to be passed to ngspice */
    char* fileName = initServerListener(PORT);

    /* init the simulation engine */
    initNgspice();

    /* after init, we are free to simulate */
    // TODO: find a way to get back the output choice 
    simNetlistFromSocket(fileName, "node 2");
}