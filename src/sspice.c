#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/serverListener.h"
#include "../inc/ngspiceSim.h"

int portNum;

int main(int argc, char** argv)
{

	portNum = 23000;

	int* connfd = malloc(sizeof(int));

	char* netlistString = initServerListener(portNum, connfd);

	/* init the simulation engine */
	initNgspice();

	/* after init, we are free to simulate */
	simNetlistFromSocket(netlistString);

	if(!returnResults("results.raw", *connfd) == 0)
	{
		close(*connfd);
		printf("Failed to return results to user...\nExiting");
		exit(-1);
	}

	close(*connfd);
}
