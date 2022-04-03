#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/ngspiceSim.h"

/* we only care about the string in this case, the id and retPtr are nothing useful*/
static void printFunction(char *string, int id, void *retPtr)
{
    printf("%s\n", string);
    /* do some file stuff here */
}

/* maybe look at controlled exit to see when ngspice is done, to send the message back? */
SendChar* func;
int initNgspice()
{
    /* bind printFunction to the function pointer ngspice_init expects */
    func = (SendChar*)&printFunction;
    ngSpice_Init(func, NULL, NULL, NULL, NULL, NULL, NULL);

    printf("[DEBUG]: Init OK\n");
    return 0;
}

int simNetlistFromSocket(char *netlistFileName, char *outputChoice)
{
    if (!netlistFileName || !outputChoice)
        return -1;
    
    /* sourcing the file (loading it) */
    char* sourceCommand = malloc(sizeof(char) * 256); 
    snprintf(sourceCommand, 256, "source %s", netlistFileName);
    printf("[DEBUG]: Source Command: %s\n", sourceCommand);
    ngSpice_Command(sourceCommand);
    
    /* run the simulation */
    ngSpice_Command("op");

    /* building print string with user input*/
    char* printCommand = malloc(sizeof(char) * 256);
    snprintf(printCommand, 256, "print %s", outputChoice);
    printf("[DEBUG]: Print Command: %s\n", printCommand);
    ngSpice_Command(printCommand);
    
    return 0;
}