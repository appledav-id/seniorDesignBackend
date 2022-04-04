#ifndef SERVER_LISTENER_H
#define SERVER_LISTENER_H

#define MAX_BUFFER_LENGTH 256

char* readFromSocket(int connfd);

char* initServerListener(int portNum);


#endif