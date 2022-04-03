#ifndef NGSPICE_SIM_H
#define NGSPICE_SIM_H

#include </usr/local/include/ngspice/sharedspice.h>

int initNgspice();

int simNetlistFromSocket(char *netlistFileName, char *outputChoice);

#endif