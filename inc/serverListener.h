#ifndef SERVER_LISTENER_H
#define SERVER_LISTENER_H

#define MAX_BUFFER_LENGTH 256

#include <unistd.h>

char* readFromSocket(int connfd);

char* initServerListener(int portNum, int* connfd);

int returnResults(const char* fileName, int connfd);

#endif