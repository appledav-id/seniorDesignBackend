#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/ngspiceSim.h"

char* gOutput = NULL;

/* we only care about the string in this case, the id and retPtr are nothing useful*/
static void printFunction(char *string, int id, void *retPtr)
{
    printf("%s\n", string);
    /* do some file stuff here */
    if(gOutput)
    {
        if(strstr(string, gOutput))
        {
            printf("Found %s\n", gOutput);

            FILE* fp = fopen("results.raw", "w+");
            fwrite(string, sizeof(char), strlen(string), fp);
            fclose(fp);
        }
    }
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

int simNetlistFromSocket(char *netlistString)
{
    if (!netlistString)
        return -1;

    char* outputChoice = malloc(sizeof(char) * 32);
    char* loadCircuitCommand = malloc(sizeof(char) * 256);
    char* token;
    const char* delim = "\n";

    /* I am thinking of using a comment inside the netlist as the way of choosing 
        what output we want, but we don't care about the title comment line */
    bool titleLineRead = false;

    token = strtok(netlistString, delim);
    while(token != NULL)
    {   
        /* titleLineRead references the beginning comment line */
        if(token[0] == '*' && titleLineRead)
        {
            /* NOTE we cannot have a printf token++ since it messes with the pointer arithmetic
                so we have to delete it, or not use it */
            gOutput = malloc(sizeof(char) * 32);

            token++;
            snprintf(outputChoice, 32, "%s", token);
            gOutput = outputChoice;
            
            token = strtok(NULL, delim);
            continue;
        }
        
        /* building strings one at a time to load the circuit */
        snprintf(loadCircuitCommand, 256, "circbyline %s", token);
        printf("[DEBUG]: loadCircuitCommand: %s\n", loadCircuitCommand);
        ngSpice_Command(loadCircuitCommand);

        token = strtok(NULL, delim);

        titleLineRead = true;
    }

    printf("[DEBUG]: Output Command: %s\n", outputChoice);
    
    /* run the simulation */
    ngSpice_Command("op");

    /* building print string with user input*/
    char* printCommand = malloc(sizeof(char) * 256);
    snprintf(printCommand, 256, "print %s", outputChoice);
    printf("[DEBUG]: Print Command: %s\n", printCommand);

    ngSpice_Command(printCommand);
    
    return 0;
}